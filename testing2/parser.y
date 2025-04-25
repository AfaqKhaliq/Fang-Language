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
    using namespace std;

    
    struct FunctionSignature {
        string return_type;
        vector<string> param_types;
        vector<string> param_id;
        int param_count;
    };

    class SymbolInfo {
    public:
        int size;
        string value;
        string type;
        bool isFunc;
        vector<string> param_types;
        vector<string> param_id;

        SymbolInfo() : size(0), value("NULL"), type("void"), isFunc(false) {}

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
    };
    extern FILE* yyin;
    int yylex(void);
    int yyerror(const char *s);

    int sig_index=0;
    string function_type="NULL";
    bool has_return_statement;
    SymbolTable GlobalTable; 
    FunctionSignature currentSignature;
    char* current_type;  // used for inherited attribute (type for IDLIST)
    bool parsing_arguments = false;
    int argument_index = 0;
    char current_function[64];
    string expected_types;


    int expected_count = 0;

 

    %}

    %union {
        char* strval;
        int intval;
    }
    %token <strval> ID INT_LITERAL STRINGLITERAL CHARLITERAL
    %token INT BOOL CHAR STRING VOID
    %token SEMICOLON COMMA LPAREN RPAREN ASSIGN LBRACE RBRACE
    %type <strval> BaseType  RETURNTYPE IDLIST 
    %token PRINT SCAN 
    %token IF ELSE WHILE RETURN MAIN
    
    %start Program
    %%

    Program: FUNCTIONDECLARATIONS MAINFUNCTION
    ;

    MAINFUNCTION:
        INT MAIN LPAREN RPAREN 

        {function_type="int"; 
        has_return_statement = false;
        }
        
        COMPOUNDSTMT
        
        {
            if (function_type != "void" && !has_return_statement) {
                    //yyerror("Non-void function must end with a return statement");
                }
        }
    ;

    FUNCTIONDECLARATIONS:
        FUNCTIONDECLARATIONS   FUNCTIONDEC {
        }
    | /* empty */
    ;

    FUNCTIONDEC:
        RETURNTYPE ID LPAREN PARAMETERS RPAREN LBRACE RBRACE {
            function_type=$1;
            has_return_statement = false;

        
            if (!has_return_statement) {
               //yyerror("func() must end with a return statement");
            }
            GlobalTable.AddFunctionToTable($2,currentSignature,function_type);
        }
    ;




    RETURNTYPE:VOID {$$=strdup("void");}
        | BaseType {$$=$1;}
    ;
    PARAMETERS:{sig_index=0;}PARAMETERLIST {sig_index=0;}
        | //ERMPTY
    ;
    PARAMETERLIST:PARAMETER
        | PARAMETERLIST COMMA PARAMETER;

    PARAMETER: BaseType ID {
        currentSignature.param_types.push_back($1);
        currentSignature.param_id.push_back($2);
        sig_index++;
    }

BaseType:
    INT    { $$ = strdup("int");  }
  | BOOL   { $$ = strdup("bool"); }
  | CHAR   { $$ = strdup("char"); }
  | STRING { $$ = strdup("string"); }
  ;

COMPOUNDSTMT:
            LBRACE LOCALDECLARATIONS  RBRACE ;
LOCALDECLARATIONS:
    /* empty */
  | VarDeclaration LOCALDECLARATIONS
;

VarDeclaration:
    BaseType { current_type = $1; } IDLIST SEMICOLON
;
IDLIST:
    ID { GlobalTable.AddId($1, current_type); }
  | ID COMMA IDLIST { GlobalTable.AddId($1, current_type); }
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