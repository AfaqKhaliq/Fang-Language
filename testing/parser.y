%{
#include <stdio.h>
#include "symbol_table.h"
int yylex(void);
int yyerror(const char *s);
char* current_type;

%}

%union {
    char* strval;
}

%token <strval> ID
%token INT
%token BOOL
%token CHAR
%token STRING
%token SEMICOLON
%token COMMA

%type <strval> BaseType
%type <strval> IDLIST
%%

VarDeclaration:
    BaseType{current_type=$1;} IDLIST SEMICOLON // inheritance
;

IDLIST:
    ID { insert_symbol($1, current_type); }
    | ID COMMA IDLIST { insert_symbol($1, current_type); }

BaseType:
    INT {
        $$ = "int";
    }
    | BOOL { $$ = "Bool"; }
    | CHAR { $$ = "char"; }
    | STRING { $$ = "string"; }
;

%%   // ← OPTIONAL: main, yyerror, etc.

int main() {
    return yyparse();
}

int yyerror(const char *s) {
    fprintf(stderr, "Parser Error: %s\n", s);
    return 0;
}