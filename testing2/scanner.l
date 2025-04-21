%{
#include "parser.tab.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: You can use this to log if needed
// FILE* outputFile = stdout;
%}

%option noyywrap

IDENTIFIER [a-zA-Z][a-zA-Z0-9_]*
NUMBER     [0-9]+
STRING     \"([^\\"]|\\.)*\"
CHAR       \'([^\\']|\\.)\'
ARITHMETICOPERATOR [\+\-\*/%]
ASSIGNMENT := 
COMPARISON (<=|>=|==|!=|<|>)
WHITESPACE [ \t\r\n]+

%%

"int"      { return INT; }
"bool"     { return BOOL; }
"string"   { return STRINGTYPE; }
"char"     { return CHAR; }
"main"     { return MAIN; }
"if"       { return IF; }
"else"     { return ELSE; }
"while"    { return WHILE; }
"return"   { return RETURN; }
"true"     { return TRUE; }
"false"    { return FALSE; }
"and"      { return AND; }
"or"       { return OR; }
"not"      { return NOT; }
"void"     { return VOID; }
"print"    { return PRINT; }
"scan"     { return SCAN; }

{NUMBER}       { yylval.strval = strdup(yytext); return INT_LITERAL; }
{IDENTIFIER}   { yylval.strval = strdup(yytext); return ID; }
{STRING}       { yylval.strval = strdup(yytext); return STRINGLITERAL; }
{CHAR}         { yylval.strval = strdup(yytext); return CHARLITERAL; }
{ASSIGNMENT}   { return ASSIGN; }
{ARITHMETICOPERATOR} { yylval.strval = strdup(yytext); return ARITHOP; }
{COMPARISON}   { yylval.strval = strdup(yytext); return COMPOP; }
";"            { return SEMICOLON; }
","            { return COMMA; }
"{"            { return LBRACE; }
"}"            { return RBRACE; }
"("            { return LPAREN; }
")"            { return RPAREN; }
{WHITESPACE}   { /* skip */ }
"//".*         { /* single-line comment */ }
"/*"([^*]|\*+[^*/])*\*+"/"    { /* multi-line comment */ }

.              {
                 fprintf(stderr, "Lexical Error: Unknown symbol '%s'\n", yytext);
                 exit(1);
              }

