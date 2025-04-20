%{
#include <stdio.h>
#include "symbol_table.h"
int yylex(void);
int yyerror(const char *s);
%}

%union {
    char* strval;
}

%token <strval> ID
%token INT
%token SEMICOLON

%type <strval> BaseType

%%

VarDeclaration:
    BaseType ID SEMICOLON {
        insert_symbol($2, $1);   // $1 = type ("int"), $2 = identifier ("x")
    }
;

BaseType:
    INT {
        $$ = "int";
    }
;

%%   // ← OPTIONAL: main, yyerror, etc.

int main() {
    return yyparse();
}

int yyerror(const char *s) {
    fprintf(stderr, "Parser Error: %s\n", s);
    return 0;
}