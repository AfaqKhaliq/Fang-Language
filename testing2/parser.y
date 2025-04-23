    %{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unordered_map>
    #include <iostream>
    #include <string>
    #include <vector>
    using namespace std;

    enum Type {
        TYPE_INT,
        TYPE_BOOL,
        TYPE_STRING,
        TYPE_CHAR,
        TYPE_VOID,
        TYPE_ERROR,
    };

    struct FunctionSignature {
        Type return_type;
        vector<Type> param_types;
        vector<string> param_id;
        int param_count;
    };

    class SymbolInfo {
    public:
        int size;
        string value;
        Type type;
        bool isFunc;
        vector<Type> param_types;
        vector<string> param_id;

        SymbolInfo() : size(0), value(""), type(TYPE_VOID), isFunc(false) {}

        ~SymbolInfo() {}

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

        ~SymbolTable() {}

        void SetParent(SymbolTable* P) {
            this->Parent = P;
        }

        void AddFunctionToTable(const char* id, FunctionSignature Sig, Type return_type) {
            SymbolInfo func;
            func.type = return_type;
            func.isFunc = true;
            func.param_types = Sig.param_types;
            func.param_id = Sig.param_id;
            string name(id);
            cout<<"function added"<<name;
            this->Table[name] = func;
        }
    };

    int yylex(void);
    int yyerror(const char *s);

    int sig_index=0;
    Type function_type;
    bool has_return_statement;
    SymbolTable GlobalTable; 
    FunctionSignature currentSignature;
    char* current_type;  // used for inherited attribute (type for IDLIST)
    bool parsing_arguments = false;
    int argument_index = 0;
    char current_function[64];
    Type* expected_types = NULL;


    int expected_count = 0;

    const char* type_name( Type t) {
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

    %}

    %union {
        char* strval;
        int intval;
        enum Type type;
    }
    %token <strval> ID INT_LITERAL STRINGLITERAL CHARLITERAL
    %token INT BOOL CHAR STRING VOID
    %token SEMICOLON COMMA LPAREN RPAREN ASSIGN LBRACE RBRACE
    %type <type> BaseType  RETURNTYPE
    %token PRINT SCAN 
    %token IF ELSE WHILE RETURN MAIN

    %language "c++"
    %%

    Program:
    FUNCTIONDECLARATIONS MAINFUNCTION
    ;

    MAINFUNCTION:
        INT MAIN LPAREN RPAREN{function_type=TYPE_INT; 
        has_return_statement = false;

            if (function_type != TYPE_VOID && !has_return_statement) {
                    yyerror("Non-void function must end with a return statement");
                }
        }
    ;

    FUNCTIONDECLARATIONS:
        FUNCTIONDECLARATIONS   FUNCTIONDEC
    | /* empty */
    ;

    FUNCTIONDEC:
        RETURNTYPE ID LPAREN PARAMETERS RPAREN{
            function_type=$1;
            has_return_statement = false;

        
            if (!has_return_statement) {
                yyerror("func() must end with a return statement");
            }
            GlobalTable.AddFunctionToTable($2,currentSignature,function_type);
        }
    ;




    RETURNTYPE:VOID {$$=TYPE_VOID;}
        | BaseType {$$=$1;}
    ;
    PARAMETERS:{sig_index=0;}PARAMETERLIST {sig_index=0;}
        | //ERMPTY
    ;
    PARAMETERLIST:PARAMETER
        | PARAMETERLIST COMMA PARAMETER;

    PARAMETER: BaseType ID {
        currentSignature.param_types.push_back( $1);
        currentSignature.param_id.push_back($2);
        sig_index++;
    }

    BaseType:
        INT    { $$ = TYPE_INT; }
    | BOOL   { $$ = TYPE_BOOL; }
    | CHAR   { $$ = TYPE_CHAR; }
    | STRING { $$ = TYPE_STRING; }
    ;



    %%

    int main() {
        return yyparse();
    }

    int yyerror(const char *s) {
        fprintf(stderr, "Parser Error: %s\n", s);
        return 0;
    }
