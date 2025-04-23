%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SymbolTable.h"
int yylex(void);
int yyerror(const char *s);



int sig_index=0

SymbolTable GlobalTable; 
FunctionSignature currentSignature;
char* current_type;  // used for inherited attribute (type for IDLIST)
bool parsing_arguments = false;
int argument_index = 0;
char current_function[64];
enum Type* expected_types = NULL;

int expected_count = 0;

const char* type_name(enum Type t) {
    switch (t) {
        case "int": return "int";
        case "bool": return "bool";
        case "string": return "string";
        case "char": return "char";
        case "void": return "void";
        case "error": return "error";
    }
    return "unknown";
}


%}


%union {
    char* strval;
    int intval;
    char* type;
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
    INT MAIN LPAREN RPAREN{function_type="int"; 
    has_return_statement = false;
} COMPOUNDSTMT {
        if (function_type != "void" && !has_return_statement) {
                yyerror("Non-void function must end with a return statement");
            }
        add_to_symbol_functions("main", "int", NULL); // assuming no params for main
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
        GlobalTable.AddFunctionToTable($2,currentSignature,function_type);
    }
;




RETURNTYPE:VOID {$$="void"}
    | BaseType {$$=$1}
;
PARAMETERS:{sig_index=0}PARAMETERLIST {sig_index=0;}
    | //ERMPTY
;
PARAMETERLIST:PARAMETER
    | PARAMETERLIST COMMA PARAMETER;

PARAMETER: BaseType ID {
    currentSignature.param_types[index] = $1;
    currentSignature.param_id[index] = $2;
    sig_index++;
}


VarDeclaration:
    BaseType { current_type = $1; } IDLIST SEMICOLON
;

IDLIST:
    ID { insert_symbol($1, current_type); }
  | ID COMMA IDLIST { insert_symbol($1, current_type); }
;

BaseType:
    INT    { $$ = "int"; }
  | BOOL   { $$ = "bool"; }
  | CHAR   { $$ = "char"; }
  | STRING { $$ = "string"; }
;






SELECTIONSTMT:IF LPAREN Expression RPAREN MATCHSTMT ELSE MATCHSTMT { 
    if ($3 != "bool" && $3 != "int")
        yyerror("Condition must be bool or int");
}
;
MATCHSTMT:EXPRSTMT
    |COMPOUNDSTMT
    | IF LPAREN Expression RPAREN MATCHSTMT ELSE MATCHSTMT { 
    if ($3!="bool" || $3!="int")
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
    if($3=="bool")
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
        if (function_type != "void")
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
            $$ = "error";
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
        if ($1 == "bool" && $3 == "bool")
            $$ = "bool";
        else {
            yyerror("OR operands must be bool");
            $$ = "error";
        }
    }
  | AndExpr { $$ = $1; }
;

AndExpr:
    AndExpr AND NotExpr {
        if ($1 == "bool" && $3 == "bool")
            $$ = "bool";
        else {
            yyerror("AND operands must be bool");
            $$ = "error";
        }
    }
  | NotExpr { $$ = $1; }
;

NotExpr:
    NOT NotExpr {
        if ($2 == "bool")
            $$ = "bool";
        else {
            yyerror("Operand of 'not' must be bool");
            $$ = "error";
        }
    }
  | RelationalExpr { $$ = $1; }
;

RelationalExpr:
    AdditiveExpr {
        $$ = $1;
    }
  | AdditiveExpr RELOP AdditiveExpr {
        if ($1 == "int" && $3 == "int")
            $$ = "bool";
        else {
            yyerror("Comparison operands must be int");
            $$ = "error";
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
        if ($1 == "int" && $3 == "int")
            $$ = "int";
        else {
            yyerror("Operands of '+' must be int");
            $$ = "error";
        }
    }

  | MultExpr { $$ = $1; }
;

ARTHOP: 
    PLUS
    | MINUS

MultExpr:
    MultExpr MULOP UnaryExpr {
        if ($1 == "int" && $3 == "int")
            $$ = "int";
        else {
            yyerror("Operands of '*' must be int");
            $$ = "error";
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
        if ($2 == "int")
            $$ = "int";
        else {
            yyerror("Unary minus only allowed on int");
            $$ = "error";
        }
    }
  | Factor { $$ = $1; }
;

Factor:
    INT_LITERAL       { $$ = "int"; }
  | STRINGLITERAL     { $$ = "string"; }
  | CHARLITERAL       { $$ = "char"; }
  | TRUE | FALSE      { $$ = "bool"; }
  | ID {
        $$ = lookup_type($1);  
        if ($$ == "error") {
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
