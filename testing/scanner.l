%{
#include "parser2.tab.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
%}

%option noyywrap 

IDENTIFIER [a-zA-Z][a-zA-Z0-9_]*
NUMBER     [0-9]+
STRING     \"([^\\"]|\\.)*\"
CHAR       \'([^\\']|\\.)\'
ASSIGNMENT := 
WHITESPACE [ \t\r\n]+

%%

"int"      { return INT; }
"bool"     { return BOOL; }
"string"   { return STRING; }
"char"     { return CHAR; }
"main"     { return MAIN; }
"if"       { return IF; }
"else"     { return ELSE; }
"while"    { return WHILE; }
"return"   { return RETURN; }
"void"     { return VOID; }
"print"    { return PRINT; }
"scan"     { return SCAN; }
"true"     { return TRUE; }
"false"     { return FALSE; }

{NUMBER}       { yylval.strval = strdup(yytext); return INT_LITERAL; }
{IDENTIFIER}   { yylval.strval = strdup(yytext); return ID; }
{STRING}       { yylval.strval = strdup(yytext); return STRINGLITERAL; }
{CHAR}         { yylval.strval = strdup(yytext); return CHARLITERAL; }
{ASSIGNMENT}   { return ASSIGN; }
";"            { return SEMICOLON; }
","            { return COMMA; }
"{"            { return LBRACE; }
"}"            { return RBRACE; }
"("            { return LPAREN; }
")"            { return RPAREN; }
">="            { return MOREANDEQUAL; }
"<="            { return LESSANDEQUAL; }
">"            { return MORETHAN; }
"<"            { return LESSTHAN; }
"=="            { return EQUAL; }
"!="            { return NOTEQUAL; }
"+"            { return PLUS; }
"-"            { return MINUS; }
"*"            { return MUL; }
"/"            { return DIV; }
"%"            { return MODULO; }
{WHITESPACE}   { /* skip */ }
"/*"([^*]|\*+[^*/])*\*+\/   { /* ignore multi-line comment */ }
"//".*         { /* single-line comment */ }

.              {
                 fprintf(stderr, "Lexical Error: Unknown symbol '%s'\n", yytext);
                 exit(1);
              }
%%