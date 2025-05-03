/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 2 "parser.y"

    #include <vector>
    using namespace std;
        struct Attr {
    char* type;           
    vector<int>* truelist; 
    vector<int>* falselist; 
    char* place;
    };



#line 62 "parser.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ID = 258,                      /* ID  */
    INT_LITERAL = 259,             /* INT_LITERAL  */
    STRINGLITERAL = 260,           /* STRINGLITERAL  */
    CHARLITERAL = 261,             /* CHARLITERAL  */
    INT = 262,                     /* INT  */
    BOOL = 263,                    /* BOOL  */
    CHAR = 264,                    /* CHAR  */
    STRING = 265,                  /* STRING  */
    VOID = 266,                    /* VOID  */
    SEMICOLON = 267,               /* SEMICOLON  */
    COMMA = 268,                   /* COMMA  */
    LPAREN = 269,                  /* LPAREN  */
    RPAREN = 270,                  /* RPAREN  */
    ASSIGN = 271,                  /* ASSIGN  */
    LBRACE = 272,                  /* LBRACE  */
    RBRACE = 273,                  /* RBRACE  */
    OR = 274,                      /* OR  */
    AND = 275,                     /* AND  */
    NOT = 276,                     /* NOT  */
    LESSTHAN = 277,                /* LESSTHAN  */
    MORETHAN = 278,                /* MORETHAN  */
    LESSANDEQUAL = 279,            /* LESSANDEQUAL  */
    MOREANDEQUAL = 280,            /* MOREANDEQUAL  */
    EQUAL = 281,                   /* EQUAL  */
    NOTEQUAL = 282,                /* NOTEQUAL  */
    PLUS = 283,                    /* PLUS  */
    MINUS = 284,                   /* MINUS  */
    MUL = 285,                     /* MUL  */
    DIV = 286,                     /* DIV  */
    MODULO = 287,                  /* MODULO  */
    TRUE = 288,                    /* TRUE  */
    FALSE = 289,                   /* FALSE  */
    PRINT = 290,                   /* PRINT  */
    SCAN = 291,                    /* SCAN  */
    IF = 292,                      /* IF  */
    ELSE = 293,                    /* ELSE  */
    WHILE = 294,                   /* WHILE  */
    RETURN = 295,                  /* RETURN  */
    MAIN = 296                     /* MAIN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 252 "parser.y"

        char* strval;
        int intval;
        Attr* attribute;
        char * type;
    

#line 128 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
