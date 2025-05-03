
%code requires{
    #include <vector>
    using namespace std;
        struct Attr {
    char* type;           
    vector<int>* truelist; 
    vector<int>* falselist; 
    char* place;
    };

    Attr* makeAttr(const char* type, const char* place) {
        Attr* a = new Attr();
        a->type = strdup(type);
        a->place = strdup(place);
        return a;
    }

}   

   
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
    #include<sstream>
    using namespace std;


    int currentCodeLine=0;
    vector<string> Code(1000);
    void backpatch(const vector<int>& PatchList,int target){
        for (auto i: PatchList){
            Code[i]+=" "+ to_string(target);
        }
    }
    vector<int>* MakeList(int x){
        vector<int>* ptr= new vector<int>;
        ptr->push_back(x);
        return ptr;
    }

    int tempcount=0;
    string genTemp(){
        ostringstream oss;
        oss<<"t"<<++tempcount;
        return oss.str();
    }


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
        void AddId(FunctionSignature& Sig) {
            for (int i = 0; i < Sig.param_id.size(); i++) {
                const string& id = Sig.param_id[i];
                const string& type = Sig.param_types[i];

                if (this->Table.count(id) == 0) {
                    SymbolInfo info;
                    info.type = type;
                    this->Table[id] = info;
                    cout << "Parameter '" << id << "' added with type " << type << endl;
                } else {
                    cout << "Error: parameter '" << id << "' already declared in this scope" << endl;
                    exit(1);
                }
            }
        }


        void AddId(const char* id,string type){
            string name(id);
            if (this->Table.find(id)==Table.end()){
                SymbolInfo ID;
                ID.type=type;
                this->Table[name]=ID;
                cout << "Parameter '" << name << "' added with type " << type << endl;
            }
            else{
                cout<< name << "Already decalred in thi scope"<<endl;
                exit(1);
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
            cout<<endl;
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
        Attr* attribute;
        char * type;
    }
    %define parse.error verbose
    %token <strval> ID INT_LITERAL STRINGLITERAL CHARLITERAL
    %token INT BOOL CHAR STRING VOID
    %token SEMICOLON COMMA LPAREN RPAREN ASSIGN LBRACE RBRACE
    %token OR AND NOT
    %token LESSTHAN MORETHAN LESSANDEQUAL MOREANDEQUAL EQUAL NOTEQUAL
    %token PLUS MINUS MUL DIV MODULO
    %token <attribute> TRUE FALSE
    %type <strval> MATCHSTMT 
    %type <strval> BaseType  RETURNTYPE IDLIST STATEMENT
    %type <strval> EXPRSTMT RETURNSTMT MULOP RELOP ARTHOP midMarker
    %type <attribute> Expression NotExpr RelationalExpr AdditiveExpr MultExpr UnaryExpr Factor 
    %token PRINT SCAN 
    %token IF ELSE WHILE RETURN MAIN
    %type <attribute> AndExpr FunctionCall 
    %start Program
    %%

    Program: FUNCTIONDECLARATIONS MAINFUNCTION
    ;

    MAINFUNCTION:
        INT MAIN LPAREN RPAREN 
        {
            function_type = "int"; 
            has_return_statement = false;
            createScope();
            Code[currentCodeLine++] = "func main:";
        }
        COMPOUNDSTMT
        {
            exitScope();
            if (!has_return_statement) {
                yyerror("Non-void function must end with a return statement");
            }
            Code[currentCodeLine++] = "endfunc";
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
            currentTable->AddId(currentSignature);
            function_type = $1;
            has_return_statement = false;
            Code[currentCodeLine++] = "func " + std::string($2) + ":";
        } 
        COMPOUNDSTMT 
        {
            exitScope();
            if (strcmp($1, "void") != 0 && !has_return_statement) {
                yyerror("func() must end with a return statement");
            }
            Code[currentCodeLine++] = "endfunc";
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
    LBRACE LOCALDECLARATIONS STMTLIST RBRACE
;


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




STATEMENT:midMarker EXPRSTMT {$$=$1;} 
    |midMarker {createScope();} COMPOUNDSTMT {exitScope(); $$=$1;}
    |midMarker SELECTIONSTMT {$$=$1;} 
    | midMarker ITERATIONSTMT {$$=$1;} 
    | midMarker RETURNSTMT {$$=$1;} 
    | midMarker IOSTMT {$$=$1;} 
;


ITERATIONSTMT:
    WHILE LPAREN {$<intval>$ = currentCodeLine; 
            // Save the line number where the condition starts
    } Expression RPAREN {
        if (std::string($4->type) != "bool") {
            yyerror("While condition must be bool");
        }

        
    }
    STATEMENT {
        // Backpatch truelist of the condition to start of body
        backpatch($4->truelist, $7);

        // Add jump back to condition after body
        Code[currentCodeLine++] = "goto " + std::to_string($<intval>5);

        // Mark falselist (loop exit) to next instruction
        backpatch($4->falselist, currentCodeLine); //next line
    }
;


SELECTIONSTMT:
    IF LPAREN{
        $<intval>$ = currentCodeLine; 
        // Save the line number where the condition starts
    } Expression RPAREN {
        if (std::string($4->type) != "bool") {
            yyerror("Condition must be bool");
        }
    }
    MATCHSTMT {
        int afterIf = currentCodeLine++;
        Code[afterIf] = "goto "; // Jump over ELSE
        $<intval>$ = afterIf;
        backpatch($4->truelist, $7);
    }
    ELSE {
        backpatch($4->falselist, currentCodeLine);
    }
    MATCHSTMT {
        backpatch(MakeList($<intval>8), currentCodeLine); // Fill jump over ELSE
    }
;

MATCHSTMT:midMarker EXPRSTMT {$$=$1;} 
    |midMarker {createScope();} COMPOUNDSTMT { exitScope(); $$=$1;}
    |midMarker IF LPAREN Expression RPAREN MATCHSTMT ELSE MATCHSTMT { 
    if (std::string($4->type) != "bool")
        yyerror("MUST GIVE BOOL EXPRESSION");
    }
    | midMarker ITERATIONSTMT  {$$=$1;} 
    | midMarker RETURNSTMT  {$$=$1;} 
    | midMarker IOSTMT {$$=$1;} 
;

midMarker:{$$ = strdup(std::to_string(currentCodeLine).c_str());}
;


RETURNSTMT:
    RETURN Expression SEMICOLON {
        if (function_type != std::string($2.type)) {
            printf("Return error: expected %s, got %s\n", function_type.c_str(), $2.type);
            fflush(stdout);
            yyerror("Return type does not match function return type");
        }
        Code[currentCodeLine++] = "return " + std::string($2->place);
        has_return_statement = true;
    }
  | RETURN SEMICOLON {
        if (function_type != "void") {
            printf("Return error: expected void, got empty return\n");
            fflush(stdout);
            yyerror("Non-void function must return a value");
        }
        Code[currentCodeLine++] = "return";  // For void return
        has_return_statement = true;
    }
;



IOSTMT:
    PRINTSTMT
  | SCANESTMT
;

PRINTSTMT:
    PRINT LPAREN Expression RPAREN SEMICOLON {
        Code[currentCodeLine++] = "print " + std::string($3->place);
    }
;

SCANESTMT:
    SCAN LPAREN ID {
        currentTable->IfExist($3);  
    } RPAREN SEMICOLON {
        Code[currentCodeLine++] = "scan " + std::string($3);
    }
;

EXPRSTMT:
    ID ASSIGN Expression SEMICOLON {
        string declared_type = currentTable->lookup($1);
        if (declared_type != std::string($3->type)) {
            yyerror("Type mismatch in assignment");
        }

        Code[currentCodeLine++] = std::string($1) + " = " + std::string($3->place);
    }
;




FunctionCall:
    ID {
        checkFunctionCall = currentTable->LookupFunction($1);
        if (!checkFunctionCall || !checkFunctionCall->isFunc) {
            yyerror(("Function '" + std::string($1) + "' not declared").c_str());
        } else {
            function_type = checkFunctionCall->type;  // Save return type
            argument_index = 0;
            parsing_arguments = true;
        }
    }
    LPAREN ARGUMENTS RPAREN {
        parsing_arguments = false;
        
        if (!checkFunctionCall) {
            yyerror("Function Doesn't Exist\n");
        } else if (argument_index != checkFunctionCall->param_types.size()) {
            yyerror("Incorrect number of arguments in function call\n");
    
        } else {
            $$ = new Attr();
            $$->type = strdup(function_type.c_str());
            std::string temp = genTemp();
            Code[currentCodeLine++] = temp + " = call " + std::string($1);
            $$->place = strdup(temp.c_str());
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
                yyerror("Too many arguments in function call");
            } else if (std::string($3->type) != checkFunctionCall->param_types[argument_index]) {
                char msg[256];
                sprintf(msg, "Argument %d: expected %s, got %s",
                        argument_index + 1,
                        checkFunctionCall->param_types[argument_index].c_str(),
                        $3->type);
                yyerror(msg);
            }
            // ✅ TAC generation
            Code[currentCodeLine++] = "param " + std::string($3->place);
            argument_index++;
        }
    }
  | Expression {
        if (parsing_arguments) {
            if (argument_index >= checkFunctionCall->param_types.size()) {
                yyerror("Too many arguments in function call");
            } else if (std::string($1->type) != checkFunctionCall->param_types[argument_index]) {
                char msg[256];
                sprintf(msg, "Argument %d: expected %s, got %s",
                        argument_index + 1,
                        checkFunctionCall->param_types[argument_index].c_str(),
                        $1->type);
                yyerror(msg);
            }
            // ✅ TAC generation
            Code[currentCodeLine++] = "param " + std::string($1->place);
            argument_index++;
        }
    }
;


Expression:
    Expression OR AndExpr {
        if (std::string($1->type) == "bool" && std::string($3->type) == "bool") {
            $$ = new Attr();
            $$->type = strdup("bool");
            $$->truelist = merge($1->truelist, $3->truelist);
            $$->falselist = $3->falselist;
            backpatch($1->falselist, currentCodeLine);  // evaluate second condition only if first is false
        } else {
            yyerror("OR operands must be bool");
        }
    }
  | AndExpr { $$ = $1; }
;

AndExpr:
    AndExpr AND NotExpr {
        if (std::string($1->type) == "bool" && std::string($3->type) == "bool") {
            $$ = new Attr();
            $$->type = strdup("bool");
            $$->truelist = $3->truelist;
            $$->falselist = merge($1->falselist, $3->falselist);
            backpatch($1->truelist, currentCodeLine);  // evaluate second condition only if first is true
        } else {
            yyerror("AND operands must be bool");
        }
    }
  | NotExpr { $$ = $1; }
;

NotExpr:
    NOT NotExpr {
        if (std::string($2->type) == "bool") {
            $$ = new Attr();
            $$->type = strdup("bool");
            $$->truelist = $2->falselist;
            $$->falselist = $2->truelist;
        } else {
            yyerror("Operand of 'not' must be bool");
        }
    }
  | RelationalExpr { $$ = $1; }
;

RelationalExpr:
    AdditiveExpr { $$ = $1; }
  | AdditiveExpr RELOP AdditiveExpr {
        if (std::string($1->type) == std::string($3->type)) {
            $$ = new Attr();
            $$->type = strdup("bool");
            string relop = $2;
            Code[currentCodeLine] = "if " + string($1->place) + " " + relop + " " + string($3->place) + " goto ";
            $$->truelist = MakeList(currentCodeLine++);
            Code[currentCodeLine] = "goto ";
            $$->falselist = MakeList(currentCodeLine++);
        } else {
            yyerror("Comparison operands must be of the same type");
        }
    }
;

RELOP:
    LESSTHAN     { $$ = strdup("<"); }
  | MORETHAN     { $$ = strdup(">"); }
  | LESSANDEQUAL { $$ = strdup("<="); }
  | MOREANDEQUAL { $$ = strdup(">="); }
  | EQUAL        { $$ = strdup("=="); }
  | NOTEQUAL     { $$ = strdup("!="); }
;

AdditiveExpr:
    AdditiveExpr ARTHOP MultExpr {
        if (std::string($1->type) == "int" && std::string($3->type) == "int") {
            $$ = new Attr();
            $$->type = strdup("int");
            string temp = genTemp();
            Code[currentCodeLine++] = temp + " = " + string($1->place) + " " + string($2) + " " + string($3->place);
            $$->place = strdup(temp.c_str());
        } else {
            yyerror("Operands of '+' or '-' must be int");
        }
    }
  | MultExpr { $$ = $1; }
;

ARTHOP:
    PLUS  { $$ = strdup("+"); }
  | MINUS { $$ = strdup("-"); }
;

MultExpr:
    MultExpr MULOP UnaryExpr {
        if (std::string($1->type) == "int" && std::string($3->type) == "int") {
            $$ = new Attr();
            $$->type = strdup("int");

            string temp = genTemp();
            string op = $2;  

            Code[currentCodeLine++] = temp + " = " + $1->place + " " + op + " " + $3->place;

            $$->place = strdup(temp.c_str());
        } else {
            yyerror("Operands of '*', '/', '%' must be int");
            $$ = new Attr();
            $$->type = strdup("error");
            $$->place = strdup("err");
        }
    }
  | UnaryExpr {
        $$ = $1;
    }
;


MULOP:
    DIV {$$=strdup("/");}
    | MUL {$$=strdup("*");}
    | MODULO {$$=strdup("%");}
;

UnaryExpr:
    MINUS Factor {
        if (std::string($2->type) == "int"){
            $$ = new Attr();
            $$->type = strdup("int");

            string temp = genTemp();
            Code[currentCodeLine++] = temp + " = -" + $2->place;

            $$->place = strdup(temp.c_str());
        }
        else
            yyerror("Unary minus only allowed on int");
    }
  | Factor {
        $$ = $1;
    }
;


Factor:
    INT_LITERAL       { $$ = makeAttr("int",$1); } 
  | STRINGLITERAL     { $$ = makeAttr("string",$1); } 
  | CHARLITERAL       { $$ = makeAttr("char",$1); } 
  | TRUE              { $$ = makeAttr("bool","true"); }
  | FALSE             { $$ = makeAttr("bool","false"); }
  | FunctionCall {$$= $1;}
  | ID {  
    char* var=currentTable->lookup($1);
        if (!var) {
            char msg[128];
            sprintf(msg, "Undeclared variable: %s", $1);
            yyerror(msg);
        }
        else{ $$=makeAttr(var,$1);}
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
        //exit(1);
        return 0;
    }