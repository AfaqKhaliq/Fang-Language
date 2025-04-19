%{
    #include "SymbolTable.h"
    #include <cstring>
    #include<string>
    using namespace std;
    SymbolTable GlobalTable;
    string current_type;
    int yylex();
    extern FILE* yyin;
    int yyerror(const char *msg);
%}

%union{
  int number;
  char * identifier;
  char * type;
}

%token <identifier> IDENTIFIER
%token <identifier> TYPE
%type <identifier> IdInit


%start VarDeclaration

%%
 
VarDeclaration : BaseType IdList ";" {current_type=""; cout<<"success";}

IdList: IdInit {GlobalTable.AddtoTable($1,SymbolInfo(0,0,current_type));}
        | IdInit { GlobalTable.AddtoTable($1,SymbolInfo(0,0,current_type));} "," IdList 

IdInit : IDENTIFIER {$$ = strdup(yylval.identifier);}    
 
BaseType : TYPE {current_type=strdup(yylval.type);}
%%

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <sourcefile>\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        perror("Failed to open input file");
        return 1;
    }

    FILE * outputFile = fopen("tokens.txt", "w"); // Optional, only if used
    if (!outputFile) {
        perror("Failed to create output file");
        return 1;
    }

    yyin = inputFile;
    yyparse();  // 👈 Bison drives everything, calls yylex()

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
int yyerror(const char *msg) {
  fprintf(stderr, "Error in parser yyerror: %s\n", msg);
  return 0;
}