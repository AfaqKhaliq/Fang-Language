%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

int yylex(void);
int yyerror(const char *s);
char* current_type;  // used for inherited attribute (type for IDLIST)
bool parsing_arguments = false;
int argument_index = 0;
char current_function[64];
enum Type* expected_types = NULL;
int expected_count = 0;
enum Type {
    TYPE_INT,
    TYPE_BOOL,
    TYPE_STRING,
    TYPE_CHAR,
    TYPE_VOID,
    TYPE_ERROR
};

const char* type_name(enum Type t) {
    switch (t) {
        case TYPE_INT: return "int";
        case TYPE_BOOL: return "bool";
        case TYPE_STRING: return "string";
        case TYPE_CHAR: return "char";
        case TYPE_VOID: return "void";
        case TYPE_ERROR: return "error";
    }
    return "unknown";
}







struct FunctionSignature { enum Type return_type;
 enum Type param_types[MAX]; 
 int param_count; }  //can implement using this for cleaner code






%}

%union {
    char* strval;
    int intval;
    enum Type type;
}

%token <strval> ID INT_LITERAL STRINGLITERAL CHARLITERAL
%token INT BOOL CHAR STRING VOID
%token SEMICOLON COMMA LPAREN RPAREN ASSIGN LBRACE RBRACE
%token OR AND NOT
%token PLUS MINUS MUL DIV MODULO
%token LESSTHAN MORETHAN LESSANDEQUAL MOREANDEQUAL EQUAL NOTEQUAL
%token <type> TRUE FALSE
%type <type> Expression AndExpr NotExpr RelationalExpr AdditiveExpr MultExpr UnaryExpr Factor
%type <strval> BaseType IDLIST RETURNTYPE
%type <type> FUNCTIONCALL
%token PRINT SCAN 
%token IF ELSE WHILE RETURN MAIN
%%

Program:
   FUNCTIONDECLARATIONS MAINFUNCTION
;

MAINFUNCTION:
    INT MAIN LPAREN RPAREN{function_type=TYPE_INT; 
    has_return_statement = false;
} COMPOUNDSTMT {
        if (function_type != TYPE_VOID && !has_return_statement) {
                yyerror("Non-void function must end with a return statement");
            }
        add_to_symbol_functions("main", TYPE_INT, NULL); // assuming no params for main
    }
;

FUNCTIONDECLARATIONS:
    FUNCTIONDECLARATIONS  {/* pass current symbol table*/ current_table[index++].passglobal} FUNCTIONDEC
  | /* empty */
;

FUNCTIONDEC:
    RETURNTYPE ID LPAREN PARAMETERS RPAREN{
        function_type=$1;
        has_return_statement = false;

    } COMPOUNDSTMT {
        if (!has_return_statement) {
            yyerror("main() must end with a return statement");
        }
        add_to_symbol_functions($2, $1, parameters_list); //add to the global_table not current
    }
;




RETURNTYPE:VOID {$$="void"}
    | BaseType {$$=$1}
;
PARAMETERS:PARAMETERLIST {index=0;}
    | //ERMPTY
;
PARAMETERLIST:PARAMETER
    | PARAMETERLIST COMMA PARAMETER;

PARAMETER: BaseType ID {
    parameters_list.type[index] = $1;
    parameters_list.id[index] = $2;
    index++;
}


VarDeclaration:
    BaseType { current_type = $1; } IDLIST SEMICOLON
;

IDLIST:
    ID { insert_symbol($1, current_type); }
  | ID COMMA IDLIST { insert_symbol($1, current_type); }
;

BaseType:
    INT    { $$ = TYPE_INT; }
  | BOOL   { $$ = TYPE_BOOL; }
  | CHAR   { $$ = TYPE_CHAR; }
  | STRING { $$ = TYPE_STRING; }
;






SELECTIONSTMT:IF LPAREN Expression RPAREN MATCHSTMT ELSE MATCHSTMT { 
    if ($3 != TYPE_BOOL && $3 != TYPE_INT)
        yyerror("Condition must be bool or int");
}
;
MATCHSTMT:EXPRSTMT
    |COMPOUNDSTMT
    | IF LPAREN Expression RPAREN MATCHSTMT ELSE MATCHSTMT { 
    if (type_name($3)!=TYPE_BOOL || type_name($3)!=TYPE_INT)
        yyerror("MUST GIVE BOOL EXPRESSION");
}
    | ITERATIONSTMT
    | RETURNSTMT
    | IOSTMT
    ;

    
COMPOUNDSTMT:LBRACE LOCALDECLARATIONS STMTLIST RBRACE;


LOCALDECLARATIONS:VarDeclaration LOCALDECLARATIONS
    | //EMPTY

;
STMTLIST:STATEMENT STMTLIST 
    | //EMPTY
;
STATEMENT: EXPRSTMT
    | COMPOUNDSTMT
    | SELECTIONSTMT
    | ITERATIONSTMT
    | RETURNSTMT
    | IOSTMT
;


EXPRSTMT:
    ID ASSIGN Expression SEMICOLON {
        enum Type declared_type = GetTypeFromSymbol($1);
        if (declared_type != $3)
            yyerror("Type mismatch in assignment");
    }
;

ITERATIONSTMT: WHILE LPAREN Expression RPAREN{
    if(type_name($3)==TYPE_BOOL)
        continue;
    else
        yyerror("MUST GIVE BOOL EXPRESSION");

} STATEMENT
;
RETURNSTMT:
    RETURN Expression SEMICOLON {
        if (function_type != $2)
            yyerror("Return type does not match function return type");
        has_return_statement = true;

    }
  | RETURN SEMICOLON {
        if (function_type != TYPE_VOID)
            yyerror("Non-void function must return a value");
        has_return_statement = true;

    }
;

IOSTMT:PRINTSTMT
    | SCANESTMT
;
PRINTSTMT:PRINT LPAREN Expression RPAREN SEMICOLON;
SCANESTMT:SCAN LPAREN ID RPAREN SEMICOLON;


///Below it is correct

FUNCTIONCALL:
    ID {
        if (!function_exists($1)) {
            yyerror("Function not declared");
            $$ = TYPE_ERROR;
        } else {
            strcpy(current_function, $1);
            expected_types = get_function_param_types($1); // e.g., [int, bool, string]
            expected_count = get_function_param_count($1); //to be implmented
            argument_index = 0;
            parsing_arguments = true;
        }
    }
    LPAREN ARGUMENTS RPAREN {
        parsing_arguments = false;
        if (argument_index != expected_count) {
            yyerror("Incorrect number of arguments in function call");
            $$ = TYPE_ERROR;
        } else {
            $$ = get_function_return_type(current_function);
        }
    }
;


ARGUMENTS:
    ARGUMENTSLIST { }
  | /* empty */   { }
;

ARGUMENTSLIST:
    ARGUMENTSLIST COMMA Expression {
        if (parsing_arguments) {
            if (argument_index >= expected_count) {
                yyerror("Too many arguments");
            } else if ($3 != expected_types[argument_index]) {
                char msg[128];
                sprintf(msg, "Argument %d: expected %s, got %s",
                    argument_index + 1,
                    type_name(expected_types[argument_index]),
                    type_name($3));
                yyerror(msg);
            }
            argument_index++;
        }
    }
  | Expression {
        if (parsing_arguments) {
            if (argument_index >= expected_count) {
                yyerror("Too many arguments");
            } else if ($1 != expected_types[argument_index]) {
                char msg[128];
                sprintf(msg, "Argument %d: expected %s, got %s",
                    argument_index + 1,
                    type_name(expected_types[argument_index]),
                    type_name($1));
                yyerror(msg);
            }
            argument_index++;
        }
    }
;





Expression:
    Expression OR AndExpr {
        if ($1 == TYPE_BOOL && $3 == TYPE_BOOL)
            $$ = TYPE_BOOL;
        else {
            yyerror("OR operands must be bool");
            $$ = TYPE_ERROR;
        }
    }
  | AndExpr { $$ = $1; }
;

AndExpr:
    AndExpr AND NotExpr {
        if ($1 == TYPE_BOOL && $3 == TYPE_BOOL)
            $$ = TYPE_BOOL;
        else {
            yyerror("AND operands must be bool");
            $$ = TYPE_ERROR;
        }
    }
  | NotExpr { $$ = $1; }
;

NotExpr:
    NOT NotExpr {
        if ($2 == TYPE_BOOL)
            $$ = TYPE_BOOL;
        else {
            yyerror("Operand of 'not' must be bool");
            $$ = TYPE_ERROR;
        }
    }
  | RelationalExpr { $$ = $1; }
;

RelationalExpr:
    AdditiveExpr {
        $$ = $1;
    }
  | AdditiveExpr RELOP AdditiveExpr {
        if ($1 == TYPE_INT && $3 == TYPE_INT)
            $$ = TYPE_BOOL;
        else {
            yyerror("Comparison operands must be int");
            $$ = TYPE_ERROR;
        }
    }
;

RELOP:
    LESSTHAN 
    | MORETHAN 
    | LESSANDEQUAL 
    | MOREANDEQUAL 
    | EQUAL 
    | NOTEQUAL


AdditiveExpr:
    AdditiveExpr ARTHOP MultExpr {
        if ($1 == TYPE_INT && $3 == TYPE_INT)
            $$ = TYPE_INT;
        else {
            yyerror("Operands of '+' must be int");
            $$ = TYPE_ERROR;
        }
    }

  | MultExpr { $$ = $1; }
;

ARTHOP: 
    PLUS
    | MINUS

MultExpr:
    MultExpr MULOP UnaryExpr {
        if ($1 == TYPE_INT && $3 == TYPE_INT)
            $$ = TYPE_INT;
        else {
            yyerror("Operands of '*' must be int");
            $$ = TYPE_ERROR;
        }
    }

  | UnaryExpr { $$ = $1; }
;

MULOP:
    DIV
    | MUL 
    | MODULO

UnaryExpr:
    MINUS Factor {
        if ($2 == TYPE_INT)
            $$ = TYPE_INT;
        else {
            yyerror("Unary minus only allowed on int");
            $$ = TYPE_ERROR;
        }
    }
  | Factor { $$ = $1; }
;

Factor:
    INT_LITERAL       { $$ = TYPE_INT; }
  | STRINGLITERAL     { $$ = TYPE_STRING; }
  | CHARLITERAL       { $$ = TYPE_CHAR; }
  | TRUE | FALSE      { $$ = TYPE_BOOL; }
  | ID {
        $$ = lookup_type($1);  
        if ($$ == TYPE_ERROR) {
            char msg[128];
            sprintf(msg, "Undeclared variable: %s", $1);
            yyerror(msg);
        }
    }
  | '(' Expression ')' { $$ = $2; }
;

%%

int main() {
    return yyparse();
}

int yyerror(const char *s) {
    fprintf(stderr, "Parser Error: %s\n", s);
    return 0;
}
