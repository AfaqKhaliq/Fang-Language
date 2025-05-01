    %{
    #ifdef _MSC_VER
#define strdup _strdup
#endif
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unordered_map>
    #include <iostream>
    #include <vector>
    #include<variant>
    using namespace std;

    
    struct FunctionSignature {
        string return_type;
        vector<string> param_types;
        vector<string> param_id;
    };

    class SymbolInfo {
    public:
        int size;
        variant<int, bool, char, string> value;;
        string type;
        bool isFunc;
        vector<string> param_types;
        vector<string> param_id;

        SymbolInfo() : size(0), value("NULL"), type("void"), isFunc(false) {}

        ~SymbolInfo() {}
        
          void setValue(const string& valStr) {
        if (type == "int") {
            value = stoi(valStr);
        } else if (type == "bool") {
            value = (valStr == "true");
        } else if (type == "char") {
            value = valStr[0];
        } else if (type == "string") {
            value = valStr;
        }
    }
        string getValueStr() const {
        if (type == "int") return to_string(get<int>(value));
        if (type == "bool") return get<bool>(value) ? "true" : "false";
        if (type == "char") return string(1, get<char>(value));
        if (type == "string") return get<string>(value);
        return "undefined";
                                         }
        SymbolInfo& operator=(const SymbolInfo& rhs) {
            if (this != &rhs) {
                this->size = rhs.size;
                this->value = rhs.value;
                this->type = rhs.type;
                this->isFunc = rhs.isFunc;
                this->param_types = rhs.param_types;
                this->param_id = rhs.param_id;
            }
            return *this;
        }
    };

    class SymbolTable {
    public:
        SymbolTable* Parent;
        unordered_map<string, SymbolInfo> Table;

        SymbolTable() {
            this->Parent = nullptr;
        }
       
        SymbolTable(SymbolTable* parentScope) {
            this->Parent = parentScope;
        }
   
        ~SymbolTable() {}

        void SetParent(SymbolTable* P) {
            this->Parent = P;
        }
        void AddId(const char* id,string type){
            string name(id);
            if (this->Table.find(id)==Table.end()){
                SymbolInfo ID;
                ID.type=type;
                this->Table[name]=ID;
                cout<<"\nadded" << name<<" to table";
            }
            else{
                cout<< name << "already decalred in thi scope";
            }
        }
        void AddFunctionToTable(const char* id, FunctionSignature Sig, string return_type) {
            SymbolInfo func;
            func.type = return_type;
            func.isFunc = true;
            func.param_types = Sig.param_types;
            func.param_id = Sig.param_id;
            string name(id);
            cout<<"function added "<<name<<" with parameters ";
            for (auto i:func.param_id){
                cout<<i<<" ";
            }
            cout<<"With types ";
            for (auto i:func.param_types){
                cout<<i<<" ";
            }
            this->Table[name] = func;

        }

        char* lookup(const string& name) {
            if (Table.count(name)) {
                return strdup(Table[name].type.c_str());  // always strdup because parser expects char*
            } else if (Parent) {
                return Parent->lookup(name);
            } else {
                return nullptr;  // not found
            }
        }

        void IfExist(const string& name) {
            if (Table.count(name)) {
                cout << "Identifier " << name << " exists in current scope" << endl;
            } else {
                cout << "Identifier " << name << " not declared in current scope" << endl;
               // yyerror(string("Identifier '" + name + "' not declared").c_str());
            }
        }

        SymbolInfo* LookupFunction(const string& name) {
            if (Table.count(name) && Table[name].isFunc) {
                return &Table[name];
            } else if (Parent) {
                return Parent->LookupFunction(name);
            } else {
                return nullptr;
            }
        }



    };

    SymbolInfo* checkFunctionCall;
    int argument_index=0;
    string function_type="NULL";
    FunctionSignature currentSignature;

    bool has_return_statement;
    SymbolTable* currentTable=new SymbolTable();
    
    void createScope() {
        SymbolTable* newTable = new SymbolTable(currentTable);
        currentTable = newTable;
    }


    void exitScope() {
        SymbolTable* old = currentTable;
        currentTable = currentTable->Parent;
        delete old; 
    }




    extern FILE* yyin;
    int yylex(void);
    int yyerror(const char *s);

    int sig_index=0;
    char* current_type;  // used for inherited attribute (type for IDLIST)
    bool parsing_arguments = false;



 

    %}

    %union {
        char* strval;
        int intval;
        char * type;
    }
    %define parse.error verbose
    %token <strval> ID INT_LITERAL STRINGLITERAL CHARLITERAL
    %token INT BOOL CHAR STRING VOID
    %token SEMICOLON COMMA LPAREN RPAREN ASSIGN LBRACE RBRACE
    %token OR AND NOT
    %token LESSTHAN MORETHAN LESSANDEQUAL MOREANDEQUAL EQUAL NOTEQUAL
    %token PLUS MINUS MUL DIV MODULO
    %token <strval> TRUE FALSE
    %type <strval> BaseType  RETURNTYPE IDLIST 
    %type <strval> EXPRSTMT
    %type <strval> Expression NotExpr RelationalExpr AdditiveExpr MultExpr UnaryExpr Factor 
    %token PRINT SCAN 
    %token IF ELSE WHILE RETURN MAIN
    %type <strval> AndExpr FunctionCall 
    %start Program
    %%

    Program: FUNCTIONDECLARATIONS MAINFUNCTION
    ;

    MAINFUNCTION:
        INT MAIN LPAREN RPAREN 
        {
            function_type="int"; 
            has_return_statement = false;
            createScope();
        }
        COMPOUNDSTMT
        {
            exitScope();
            if (!has_return_statement) {
                    yyerror("Non-void function must end with a return statement");
            }
        }
    ;

    FUNCTIONDECLARATIONS:
        FUNCTIONDECLARATIONS FUNCTIONDEC
        | //EMPTY
    ;

    FUNCTIONDEC:
        RETURNTYPE ID LPAREN
        {
            currentSignature.param_types.clear();
            currentSignature.param_id.clear();
        }
        PARAMETERS
        {
            currentTable->AddFunctionToTable($2,currentSignature,$1);
        } 
        RPAREN
        {
            createScope();
            function_type=$1;
            has_return_statement = false;
        } 
        COMPOUNDSTMT 
        {
            exitScope();
            if ( strcmp($1,"void")!=0 && !has_return_statement ) {
               yyerror("func() must end with a return statement");
            }
        }
    ;

    RETURNTYPE:VOID {$$=strdup("void");}
        | BaseType {$$=$1;}
    ;
    PARAMETERS:PARAMETERLIST
        | //ERMPTY
    ;
    PARAMETERLIST:PARAMETER
        | PARAMETERLIST COMMA PARAMETER;

    PARAMETER: BaseType ID {
        currentSignature.param_types.push_back($1);
        currentSignature.param_id.push_back($2);
    }

BaseType:
    INT    { $$ = strdup("int");  }
  | BOOL   { $$ = strdup("bool"); }
  | CHAR   { $$ = strdup("char"); }
  | STRING { $$ = strdup("string"); }
  ;

COMPOUNDSTMT:
    LBRACE LOCALDECLARATIONS STMTLIST RBRACE ;

LOCALDECLARATIONS:
    VarDeclaration LOCALDECLARATIONS
    | //EMPTY
;

VarDeclaration:
    BaseType
    { current_type = $1; } 
    IDLIST SEMICOLON
;
IDLIST:
    ID
    { 
        currentTable->AddId($1, current_type);
    }
  | ID
    {
        currentTable->AddId($1, current_type);
    } 
    COMMA IDLIST
;

STMTLIST:STATEMENT STMTLIST 
    | //EMPTY
;




STATEMENT: EXPRSTMT 
    |{createScope();} COMPOUNDSTMT {exitScope();}
    |// SELECTIONSTMT
    | //ITERATIONSTMT
    | RETURNSTMT
    |// IOSTMT
;

/*
ITERATIONSTMT: WHILE LPAREN Expression RPAREN
    {
        if(type_name($3)=="bool")
            continue;
        else
            yyerror("MUST GIVE BOOL EXPRESSION");

    }
STATEMENT ;

SELECTIONSTMT:IF LPAREN Expression RPAREN MATCHSTMT ELSE MATCHSTMT { 
    if ($3 != TYPE_BOOL && $3 != TYPE_INT)
        yyerror("Condition must be bool or int");
}
;
MATCHSTMT:EXPRSTMT
    |{ createScope(); } COMPOUNDSTMT { exitScope(); }
    | IF LPAREN Expression RPAREN MATCHSTMT ELSE MATCHSTMT { 
    if (type_name($3)!=TYPE_BOOL || type_name($3)!=TYPE_INT)
        yyerror("MUST GIVE BOOL EXPRESSION");
}
    | ITERATIONSTMT
    | RETURNSTMT
    | IOSTMT
;

*/
RETURNSTMT:
    RETURN Expression SEMICOLON 
    {
        if (function_type != $2)
            yyerror("Return type does not match function return type");
        has_return_statement = true;

    }
  | RETURN SEMICOLON 
  {
        if (function_type != TYPE_VOID)
            yyerror("Non-void function must return a value");
        has_return_statement = true;

    }
;

IOSTMT:PRINTSTMT
    | SCANESTMT
;
PRINTSTMT:PRINT LPAREN Expression RPAREN SEMICOLON;
SCANESTMT:SCAN LPAREN ID {currentTable->IfExist($3);} RPAREN SEMICOLON;


EXPRSTMT:
    ID ASSIGN Expression SEMICOLON{
        string declared_type =currentTable->lookup($1);
        cout<<"id assigned value";
        if (declared_type != string($3))
            yyerror("Type mismatch in assignment");
    }
;



FunctionCall:
    ID {
        checkFunctionCall = currentTable->LookupFunction($1);
        if (!checkFunctionCall || !checkFunctionCall->isFunc) {
            yyerror(("Function '" + string($1) + "' not declared").c_str());
        } else {

            function_type = checkFunctionCall->type;  // Save return type for $$ later
            argument_index = 0;
            parsing_arguments = true;
        }
    }
    LPAREN ARGUMENTS RPAREN {
        parsing_arguments = false;
        if (argument_index != checkFunctionCall->param_id.size()) {
            yyerror("Incorrect number of arguments in function call");
        } else {
            $$ = strdup(function_type.c_str());
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
            if (argument_index >= checkFunctionCall->param_types.size()) {
                yyerror("Too many arguments");
            } else if (strcmp($3, checkFunctionCall->param_types[argument_index].c_str()) != 0) {
                char msg[128];
                sprintf(msg, "Argument %d: expected %s, got %s",
                        argument_index + 1,
                        checkFunctionCall->param_types[argument_index].c_str(),
                        $3);
                yyerror(msg);
            }
            argument_index++;
        }
    }
  | Expression {
        if (parsing_arguments) {
            if (argument_index >= checkFunctionCall->param_types.size()) {
                yyerror("Too many arguments");
            } else if (strcmp($1, checkFunctionCall->param_types[argument_index].c_str()) != 0) {
                char msg[128];
                sprintf(msg, "Argument %d: expected %s, got %s",
                        argument_index + 1,
                        checkFunctionCall->param_types[argument_index].c_str(),
                        $1);
                yyerror(msg);
            }
            argument_index++;
        }
    }
;

Expression:
    Expression OR AndExpr {
        if (strcmp($1, "bool") == 0 && strcmp($3, "bool") == 0)
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
        if (strcmp($1, "bool") == 0 && strcmp($3, "bool") == 0)
            $$ = "bool";
        else {
            yyerror("AND operands must be bool");
            $$ = "error";
        }
    }
  | NotExpr { $$ = $1; }
;

NotExpr: NOT NotExpr
      {
        if (strcmp($2, "bool") == 0)
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
        if (strcmp($1, "int") == 0 && strcmp($3, "int") == 0)
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
;

AdditiveExpr:
    AdditiveExpr ARTHOP MultExpr {
        if (strcmp($1, "int") == 0 && strcmp($3, "int") == 0)
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
;

MultExpr:
    MultExpr MULOP UnaryExpr {
        if (strcmp($1, "int") == 0 && strcmp($3, "int") == 0)
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
;

UnaryExpr:
    MINUS Factor {
        if (strcmp($2, "int") == 0)
            $$ = "int";
        else {
            yyerror("Unary minus only allowed on int");
            $$ = "error";
        }
    }
  | Factor { $$ = $1; }
;

Factor:
    INT_LITERAL       { $$ = strdup("int"); } 
  | STRINGLITERAL     { $$ = strdup("string"); } 
  | CHARLITERAL       { $$ = strdup("char"); } 
  | TRUE | FALSE      { $$ = strdup("bool"); }
  | FunctionCall {$$ = strdup($1);}
  | ID {  
    char* var=currentTable->lookup($1);
        if (!var) {
            char msg[128];
            sprintf(msg, "Undeclared variable: %s", $1);
            yyerror(msg);
        }
        else{ $$=strdup(var);}
    }
  | LBRACE Expression RBRACE { $$ = $2; }
;



    %%

    int main() {
        FILE *fp;
char filename[50];
cout<<"Enter the filename:"<<endl;
cin>> filename;
fp = fopen(filename,"r");
yyin = fp;
        return yyparse();
    }

    int yyerror(const char *s) {
        fprintf(stderr, "Parser Error: %s\n", s);
        return 0;
    }