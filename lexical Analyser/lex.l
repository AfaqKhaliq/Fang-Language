%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

FILE *outputFile;

bool mainExists = false;

void addKeyword(const char *keyword) {
    if (strcmp(keyword, "main") == 0) {
        if (mainExists) {
            fprintf(stderr, "Error: multiple definitions of main function.\n");
            exit(1);
        } else {
            mainExists = true;
        }
    }
    fprintf(outputFile, "KEYWORD: %s\n", keyword);
}

void addIdentifier(const char *id) {
    fprintf(outputFile, "IDENTIFIER: %s\n", id);
}
void addType(const char *id) {
    fprintf(outputFile, "TYPE: %s\n", id);
}

void addInteger(const char *num) {
    fprintf(outputFile, "INT_LITERAL: %s\n", num);
}

void addBoolLiteral(const char *val) {
    fprintf(outputFile, "BOOL_LITERAL: %s\n", val);
}

void addLogical(const char *op) {
    fprintf(outputFile, "LOGICAL_OPERATOR: %s\n", op);
}

void addOperator(const char *op) {
    fprintf(outputFile, "OPERATOR: %s\n", op);
}

void addString(const char *str) {
    fprintf(outputFile, "STRING_LITERAL: %s\n", str);
}

void addChar(const char *ch) {
    fprintf(outputFile, "CHAR_LITERAL: %s\n", ch);
}
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

"int"      { addType("int"); }
"bool"     { addType("bool"); }
"string"   { addType("string"); }
"char"     { addType("char"); }
"main"     { addKeyword("main"); }
"if"       { addKeyword("if"); }
"else"     { addKeyword("else"); }
"while"    { addKeyword("while"); }
"return"   { addKeyword("return"); }
"true"     { addBoolLiteral("true"); }
"false"    { addBoolLiteral("false"); }
"and"      { addLogical("and"); }
"or"       { addLogical("or"); }
"not"      { addLogical("not"); }
"void"     { addType("void"); }
"print"    { addKeyword("print"); }
"scan"     { addKeyword("scan"); }

{NUMBER}   { addInteger(yytext); }
{IDENTIFIER} { addIdentifier(yytext); }
{STRING}   { addString(yytext); }
{CHAR}     { addChar(yytext); }
{ASSIGNMENT} { addOperator(yytext); }
{ARITHMETICOPERATOR} { addOperator(yytext); }
{COMPARISON} { addOperator(yytext); }
";"        { fprintf(outputFile, "SEMICOLON: ;\n"); }
","        { fprintf(outputFile, "COMMA: ,\n"); }
"{"        { fprintf(outputFile, "LBRACE: {\n"); }
"}"        { fprintf(outputFile, "RBRACE: }\n"); }
"("        { fprintf(outputFile, "LPAREN: (\n"); }
")"        { fprintf(outputFile, "RPAREN: )\n"); }
{WHITESPACE} { /* Ignore */ }
"//".*     { /* Single line comment - ignore */ }
"/*"([^*]|\*+[^*/])*\*+"/"    { /* Multi-line comment - ignore */ }
.          { fprintf(outputFile, "UNKNOWN: %s\n", yytext); }

%%

