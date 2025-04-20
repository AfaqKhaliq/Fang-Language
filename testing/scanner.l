%{
#include "parser.tab.h"   // Required for token enums and yylval
#include <string.h>
#include <stdlib.h>
%}

%option noyywrap

%%

"int"              { return INT; }
[a-zA-Z_][a-zA-Z0-9_]*   { yylval.strval = strdup(yytext); return ID; } // basically idar hum bejray hai wapis variable name copied to strval where it is accesed directly by parser
";"                { return SEMICOLON; }
","                { return COMMA; }
[ \t\n]+           { /* skip whitespace */ }

.                  { printf("Unknown: %s\n", yytext); }

