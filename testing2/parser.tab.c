/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SymbolTable.h"
int yylex(void);
int yyerror(const char *s);



intsig_index=0

SymbolTable GlobalTable; 
FunctionSignature currentSignature;
char* current_type;  // used for inherited attribute (type for IDLIST)
bool parsing_arguments = false;
int argument_index = 0;
char current_function[64];
enum Type* expected_types = NULL;

int expected_count = 0;

const char* type_name(enum Type t) {
    switch (t) {
        case "int": return "int";
        case "bool": return "bool";
        case "string": return "string";
        case "char": return "char";
        case "void": return "void";
        case "error": return "error";
    }
    return "unknown";
}



#line 108 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_INT_LITERAL = 4,                /* INT_LITERAL  */
  YYSYMBOL_STRINGLITERAL = 5,              /* STRINGLITERAL  */
  YYSYMBOL_CHARLITERAL = 6,                /* CHARLITERAL  */
  YYSYMBOL_INT = 7,                        /* INT  */
  YYSYMBOL_BOOL = 8,                       /* BOOL  */
  YYSYMBOL_CHAR = 9,                       /* CHAR  */
  YYSYMBOL_STRING = 10,                    /* STRING  */
  YYSYMBOL_VOID = 11,                      /* VOID  */
  YYSYMBOL_SEMICOLON = 12,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 13,                     /* COMMA  */
  YYSYMBOL_LPAREN = 14,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 15,                    /* RPAREN  */
  YYSYMBOL_ASSIGN = 16,                    /* ASSIGN  */
  YYSYMBOL_LBRACE = 17,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 18,                    /* RBRACE  */
  YYSYMBOL_OR = 19,                        /* OR  */
  YYSYMBOL_AND = 20,                       /* AND  */
  YYSYMBOL_NOT = 21,                       /* NOT  */
  YYSYMBOL_PLUS = 22,                      /* PLUS  */
  YYSYMBOL_MINUS = 23,                     /* MINUS  */
  YYSYMBOL_MUL = 24,                       /* MUL  */
  YYSYMBOL_DIV = 25,                       /* DIV  */
  YYSYMBOL_MODULO = 26,                    /* MODULO  */
  YYSYMBOL_LESSTHAN = 27,                  /* LESSTHAN  */
  YYSYMBOL_MORETHAN = 28,                  /* MORETHAN  */
  YYSYMBOL_LESSANDEQUAL = 29,              /* LESSANDEQUAL  */
  YYSYMBOL_MOREANDEQUAL = 30,              /* MOREANDEQUAL  */
  YYSYMBOL_EQUAL = 31,                     /* EQUAL  */
  YYSYMBOL_NOTEQUAL = 32,                  /* NOTEQUAL  */
  YYSYMBOL_TRUE = 33,                      /* TRUE  */
  YYSYMBOL_FALSE = 34,                     /* FALSE  */
  YYSYMBOL_PRINT = 35,                     /* PRINT  */
  YYSYMBOL_SCAN = 36,                      /* SCAN  */
  YYSYMBOL_IF = 37,                        /* IF  */
  YYSYMBOL_ELSE = 38,                      /* ELSE  */
  YYSYMBOL_WHILE = 39,                     /* WHILE  */
  YYSYMBOL_RETURN = 40,                    /* RETURN  */
  YYSYMBOL_MAIN = 41,                      /* MAIN  */
  YYSYMBOL_42_ = 42,                       /* '('  */
  YYSYMBOL_43_ = 43,                       /* ')'  */
  YYSYMBOL_YYACCEPT = 44,                  /* $accept  */
  YYSYMBOL_Program = 45,                   /* Program  */
  YYSYMBOL_MAINFUNCTION = 46,              /* MAINFUNCTION  */
  YYSYMBOL_47_1 = 47,                      /* $@1  */
  YYSYMBOL_FUNCTIONDECLARATIONS = 48,      /* FUNCTIONDECLARATIONS  */
  YYSYMBOL_49_2 = 49,                      /* $@2  */
  YYSYMBOL_FUNCTIONDEC = 50,               /* FUNCTIONDEC  */
  YYSYMBOL_51_3 = 51,                      /* $@3  */
  YYSYMBOL_RETURNTYPE = 52,                /* RETURNTYPE  */
  YYSYMBOL_PARAMETERS = 53,                /* PARAMETERS  */
  YYSYMBOL_54_4 = 54,                      /* $@4  */
  YYSYMBOL_PARAMETERLIST = 55,             /* PARAMETERLIST  */
  YYSYMBOL_PARAMETER = 56,                 /* PARAMETER  */
  YYSYMBOL_VarDeclaration = 57,            /* VarDeclaration  */
  YYSYMBOL_58_5 = 58,                      /* $@5  */
  YYSYMBOL_IDLIST = 59,                    /* IDLIST  */
  YYSYMBOL_BaseType = 60,                  /* BaseType  */
  YYSYMBOL_SELECTIONSTMT = 61,             /* SELECTIONSTMT  */
  YYSYMBOL_MATCHSTMT = 62,                 /* MATCHSTMT  */
  YYSYMBOL_COMPOUNDSTMT = 63,              /* COMPOUNDSTMT  */
  YYSYMBOL_LOCALDECLARATIONS = 64,         /* LOCALDECLARATIONS  */
  YYSYMBOL_STMTLIST = 65,                  /* STMTLIST  */
  YYSYMBOL_STATEMENT = 66,                 /* STATEMENT  */
  YYSYMBOL_EXPRSTMT = 67,                  /* EXPRSTMT  */
  YYSYMBOL_ITERATIONSTMT = 68,             /* ITERATIONSTMT  */
  YYSYMBOL_69_6 = 69,                      /* $@6  */
  YYSYMBOL_RETURNSTMT = 70,                /* RETURNSTMT  */
  YYSYMBOL_IOSTMT = 71,                    /* IOSTMT  */
  YYSYMBOL_PRINTSTMT = 72,                 /* PRINTSTMT  */
  YYSYMBOL_SCANESTMT = 73,                 /* SCANESTMT  */
  YYSYMBOL_Expression = 74,                /* Expression  */
  YYSYMBOL_AndExpr = 75,                   /* AndExpr  */
  YYSYMBOL_NotExpr = 76,                   /* NotExpr  */
  YYSYMBOL_RelationalExpr = 77,            /* RelationalExpr  */
  YYSYMBOL_RELOP = 78,                     /* RELOP  */
  YYSYMBOL_AdditiveExpr = 79,              /* AdditiveExpr  */
  YYSYMBOL_ARTHOP = 80,                    /* ARTHOP  */
  YYSYMBOL_MultExpr = 81,                  /* MultExpr  */
  YYSYMBOL_MULOP = 82,                     /* MULOP  */
  YYSYMBOL_UnaryExpr = 83,                 /* UnaryExpr  */
  YYSYMBOL_Factor = 84                     /* Factor  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   158

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  84
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  140

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   296


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      42,    43,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    60,    60,    64,    64,    75,    75,    76,    80,    80,
      95,    96,    98,    98,    99,   101,   102,   104,   112,   112,
     116,   117,   121,   122,   123,   124,   132,   137,   138,   139,
     143,   144,   145,   149,   152,   153,   156,   157,   159,   160,
     161,   162,   163,   164,   169,   176,   176,   185,   191,   199,
     200,   202,   203,   276,   284,   288,   296,   300,   308,   312,
     315,   326,   327,   328,   329,   330,   331,   335,   344,   348,
     349,   352,   361,   365,   366,   367,   370,   378,   382,   383,
     384,   385,   385,   386,   394
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID", "INT_LITERAL",
  "STRINGLITERAL", "CHARLITERAL", "INT", "BOOL", "CHAR", "STRING", "VOID",
  "SEMICOLON", "COMMA", "LPAREN", "RPAREN", "ASSIGN", "LBRACE", "RBRACE",
  "OR", "AND", "NOT", "PLUS", "MINUS", "MUL", "DIV", "MODULO", "LESSTHAN",
  "MORETHAN", "LESSANDEQUAL", "MOREANDEQUAL", "EQUAL", "NOTEQUAL", "TRUE",
  "FALSE", "PRINT", "SCAN", "IF", "ELSE", "WHILE", "RETURN", "MAIN", "'('",
  "')'", "$accept", "Program", "MAINFUNCTION", "$@1",
  "FUNCTIONDECLARATIONS", "$@2", "FUNCTIONDEC", "$@3", "RETURNTYPE",
  "PARAMETERS", "$@4", "PARAMETERLIST", "PARAMETER", "VarDeclaration",
  "$@5", "IDLIST", "BaseType", "SELECTIONSTMT", "MATCHSTMT",
  "COMPOUNDSTMT", "LOCALDECLARATIONS", "STMTLIST", "STATEMENT", "EXPRSTMT",
  "ITERATIONSTMT", "$@6", "RETURNSTMT", "IOSTMT", "PRINTSTMT", "SCANESTMT",
  "Expression", "AndExpr", "NotExpr", "RelationalExpr", "RELOP",
  "AdditiveExpr", "ARTHOP", "MultExpr", "MULOP", "UnaryExpr", "Factor", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-70)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-15)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -70,    40,    51,   -70,    27,   -70,    87,    45,   -70,   -70,
     -70,   -70,   -70,   -70,    75,   -70,    64,    77,   -70,   103,
      82,   104,   115,   115,   -70,   -70,   107,   -70,   123,   115,
     -70,    47,    82,   115,   -70,   -70,   124,   112,   116,   117,
     118,   119,    18,   -70,   -70,   111,    47,   -70,   -70,   -70,
     -70,   -70,   -70,   -70,   -70,   121,   125,    32,    32,   132,
      32,    32,   -70,   -70,   -70,   -70,   -70,    32,    43,   -70,
     -70,    32,    15,   120,   -70,   -70,    84,   -11,   -70,   -70,
     -70,   -70,   124,   -70,    42,    56,   126,    89,    90,   -70,
     -70,    14,   -70,    32,    32,   -70,   -70,   -70,   -70,   -70,
     -70,   -70,   -70,    39,    39,   -70,   -70,   -70,    39,   -70,
     -70,   127,   130,    53,   -70,   -70,   120,   -70,     6,   -11,
     -70,   -70,   -70,   122,   100,   -70,   -70,   -70,   -70,   -70,
      47,    32,    53,   -70,   102,   -70,    53,   105,    53,   -70
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       7,     0,     5,     1,     0,     2,     0,     0,    22,    23,
      24,    25,    10,     6,     0,    11,     0,     0,     3,    12,
       0,     0,     0,    35,     4,     8,    13,    15,     0,    35,
      18,    37,     0,     0,    17,    34,     0,     0,     0,     0,
       0,     0,     0,    40,    39,     0,    37,    38,    41,    42,
      43,    49,    50,     9,    16,    20,     0,     0,     0,     0,
       0,     0,    83,    78,    79,    80,    48,     0,     0,    81,
      82,     0,     0,    54,    56,    58,    59,    68,    72,    77,
      33,    36,     0,    19,     0,     0,     0,     0,     0,    57,
      76,     0,    47,     0,     0,    69,    70,    61,    62,    63,
      64,    65,    66,     0,     0,    74,    73,    75,     0,    21,
      44,     0,     0,     0,    45,    84,    53,    55,    60,    67,
      71,    51,    52,     0,     0,    28,    27,    30,    31,    32,
       0,     0,     0,    46,     0,    26,     0,     0,     0,    29
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -70,   -70,   -70,   -70,   -70,   -70,   -70,   -70,   -70,   -70,
     -70,   -70,   113,   -70,   -70,    62,     2,   -70,   -69,   -20,
     128,    99,    17,   -30,   -29,   -70,   -28,   -27,   -70,   -70,
     -51,    55,   -62,   -70,   -70,    46,   -70,    48,   -70,    50,
      83
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     5,    20,     2,     6,    13,    32,    14,    21,
      22,    26,    27,    29,    36,    56,    28,    43,   124,   125,
      31,    45,    46,   126,   127,   130,   128,   129,    51,    52,
      72,    73,    74,    75,   103,    76,   104,    77,   108,    78,
      79
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      24,    47,    48,    49,    50,    89,    84,    85,    15,    87,
      88,    44,    53,   105,   106,   107,    47,    48,    49,    50,
      91,    62,    63,    64,    65,    30,    44,    92,    95,    96,
      66,    30,   117,    93,    93,    62,    63,    64,    65,    67,
       3,    68,    62,    63,    64,    65,    62,    63,    64,    65,
      37,    69,    70,    67,   110,    68,    37,   115,     4,    16,
      71,    93,    68,   135,    23,    69,    70,   137,     7,   139,
      23,   111,    69,    70,    71,    93,    69,    70,    17,    18,
     134,    71,    38,    39,    40,    71,    41,    42,    38,    39,
     123,    19,    41,    42,     8,     9,    10,    11,    12,    23,
      47,    48,    49,    50,   113,   114,    95,    96,    93,    93,
      44,    97,    98,    99,   100,   101,   102,   136,   -14,    25,
      33,    93,     8,     9,    10,    11,    34,    55,    57,    80,
      58,    59,    60,    61,    82,    86,   131,    83,   132,   121,
      94,   112,   122,   138,   109,    81,    54,   133,   116,   118,
       0,    90,   119,     0,     0,     0,     0,    35,   120
};

static const yytype_int16 yycheck[] =
{
      20,    31,    31,    31,    31,    67,    57,    58,     6,    60,
      61,    31,    32,    24,    25,    26,    46,    46,    46,    46,
      71,     3,     4,     5,     6,    23,    46,    12,    22,    23,
      12,    29,    94,    19,    19,     3,     4,     5,     6,    21,
       0,    23,     3,     4,     5,     6,     3,     4,     5,     6,
       3,    33,    34,    21,    12,    23,     3,    43,     7,    14,
      42,    19,    23,   132,    17,    33,    34,   136,    41,   138,
      17,    15,    33,    34,    42,    19,    33,    34,     3,    15,
     131,    42,    35,    36,    37,    42,    39,    40,    35,    36,
      37,    14,    39,    40,     7,     8,     9,    10,    11,    17,
     130,   130,   130,   130,    15,    15,    22,    23,    19,    19,
     130,    27,    28,    29,    30,    31,    32,    15,    15,    15,
      13,    19,     7,     8,     9,    10,     3,     3,    16,    18,
      14,    14,    14,    14,    13,     3,    14,    12,    38,    12,
      20,    15,    12,    38,    82,    46,    33,   130,    93,   103,
      -1,    68,   104,    -1,    -1,    -1,    -1,    29,   108
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    45,    48,     0,     7,    46,    49,    41,     7,     8,
       9,    10,    11,    50,    52,    60,    14,     3,    15,    14,
      47,    53,    54,    17,    63,    15,    55,    56,    60,    57,
      60,    64,    51,    13,     3,    64,    58,     3,    35,    36,
      37,    39,    40,    61,    63,    65,    66,    67,    68,    70,
      71,    72,    73,    63,    56,     3,    59,    16,    14,    14,
      14,    14,     3,     4,     5,     6,    12,    21,    23,    33,
      34,    42,    74,    75,    76,    77,    79,    81,    83,    84,
      18,    65,    13,    12,    74,    74,     3,    74,    74,    76,
      84,    74,    12,    19,    20,    22,    23,    27,    28,    29,
      30,    31,    32,    78,    80,    24,    25,    26,    82,    59,
      12,    15,    15,    15,    15,    43,    75,    76,    79,    81,
      83,    12,    12,    37,    62,    63,    67,    68,    70,    71,
      69,    14,    38,    66,    74,    62,    15,    62,    38,    62
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    44,    45,    47,    46,    49,    48,    48,    51,    50,
      52,    52,    54,    53,    53,    55,    55,    56,    58,    57,
      59,    59,    60,    60,    60,    60,    61,    62,    62,    62,
      62,    62,    62,    63,    64,    64,    65,    65,    66,    66,
      66,    66,    66,    66,    67,    69,    68,    70,    70,    71,
      71,    72,    73,    74,    74,    75,    75,    76,    76,    77,
      77,    78,    78,    78,    78,    78,    78,    79,    79,    80,
      80,    81,    81,    82,    82,    82,    83,    83,    84,    84,
      84,    84,    84,    84,    84
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     0,     6,     0,     3,     0,     0,     7,
       1,     1,     0,     2,     0,     1,     3,     2,     0,     4,
       1,     3,     1,     1,     1,     1,     7,     1,     1,     7,
       1,     1,     1,     4,     2,     0,     2,     0,     1,     1,
       1,     1,     1,     1,     4,     0,     6,     3,     2,     1,
       1,     5,     5,     3,     1,     3,     1,     2,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     3,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 3: /* $@1: %empty  */
#line 64 "parser.y"
                          {function_type="int"; 
    has_return_statement = false;
}
#line 1284 "parser.tab.c"
    break;

  case 4: /* MAINFUNCTION: INT MAIN LPAREN RPAREN $@1 COMPOUNDSTMT  */
#line 66 "parser.y"
               {
        if (function_type != "void" && !has_return_statement) {
                yyerror("Non-void function must end with a return statement");
            }
        add_to_symbol_functions("main", "int", NULL); // assuming no params for main
    }
#line 1295 "parser.tab.c"
    break;

  case 5: /* $@2: %empty  */
#line 75 "parser.y"
                          {/* pass current symbol table*/ current_table[index++].passglobal}
#line 1301 "parser.tab.c"
    break;

  case 8: /* $@3: %empty  */
#line 80 "parser.y"
                                          {
        function_type=(yyvsp[-4].strval);
        has_return_statement = false;

    }
#line 1311 "parser.tab.c"
    break;

  case 9: /* FUNCTIONDEC: RETURNTYPE ID LPAREN PARAMETERS RPAREN $@3 COMPOUNDSTMT  */
#line 84 "parser.y"
                   {
        if (!has_return_statement) {
            yyerror("main() must end with a return statement");
        }
        GlobalTable.AddFunctionToTable((yyvsp[-5].strval),currentSignature,function_type);
    }
#line 1322 "parser.tab.c"
    break;

  case 10: /* RETURNTYPE: VOID  */
#line 95 "parser.y"
                {(yyval.strval)="void"}
#line 1328 "parser.tab.c"
    break;

  case 11: /* RETURNTYPE: BaseType  */
#line 96 "parser.y"
               {(yyval.strval)=(yyvsp[0].strval)}
#line 1334 "parser.tab.c"
    break;

  case 12: /* $@4: %empty  */
#line 98 "parser.y"
           {sig_index=0}
#line 1340 "parser.tab.c"
    break;

  case 13: /* PARAMETERS: $@4 PARAMETERLIST  */
#line 98 "parser.y"
                                      {sig_index=0;}
#line 1346 "parser.tab.c"
    break;

  case 17: /* PARAMETER: BaseType ID  */
#line 104 "parser.y"
                       {
    currentSignature.param_types[index] = (yyvsp[-1].strval);
    currentSignature.param_id[index] = (yyvsp[0].strval);
    sig_index++;
}
#line 1356 "parser.tab.c"
    break;

  case 18: /* $@5: %empty  */
#line 112 "parser.y"
             { current_type = (yyvsp[0].strval); }
#line 1362 "parser.tab.c"
    break;

  case 20: /* IDLIST: ID  */
#line 116 "parser.y"
       { insert_symbol((yyvsp[0].strval), current_type); }
#line 1368 "parser.tab.c"
    break;

  case 21: /* IDLIST: ID COMMA IDLIST  */
#line 117 "parser.y"
                    { insert_symbol((yyvsp[-2].strval), current_type); }
#line 1374 "parser.tab.c"
    break;

  case 22: /* BaseType: INT  */
#line 121 "parser.y"
           { (yyval.strval) = "int"; }
#line 1380 "parser.tab.c"
    break;

  case 23: /* BaseType: BOOL  */
#line 122 "parser.y"
           { (yyval.strval) = "bool"; }
#line 1386 "parser.tab.c"
    break;

  case 24: /* BaseType: CHAR  */
#line 123 "parser.y"
           { (yyval.strval) = "char"; }
#line 1392 "parser.tab.c"
    break;

  case 25: /* BaseType: STRING  */
#line 124 "parser.y"
           { (yyval.strval) = "string"; }
#line 1398 "parser.tab.c"
    break;

  case 26: /* SELECTIONSTMT: IF LPAREN Expression RPAREN MATCHSTMT ELSE MATCHSTMT  */
#line 132 "parser.y"
                                                                   { 
    if ((yyvsp[-4].type) != "bool" && (yyvsp[-4].type) != "int")
        yyerror("Condition must be bool or int");
}
#line 1407 "parser.tab.c"
    break;

  case 29: /* MATCHSTMT: IF LPAREN Expression RPAREN MATCHSTMT ELSE MATCHSTMT  */
#line 139 "parser.y"
                                                           { 
    if ((yyvsp[-4].type)!="bool" || (yyvsp[-4].type)!="int")
        yyerror("MUST GIVE BOOL EXPRESSION");
}
#line 1416 "parser.tab.c"
    break;

  case 44: /* EXPRSTMT: ID ASSIGN Expression SEMICOLON  */
#line 169 "parser.y"
                                   {
        enum Type declared_type = GetTypeFromSymbol((yyvsp[-3].strval));
        if (declared_type != (yyvsp[-1].type))
            yyerror("Type mismatch in assignment");
    }
#line 1426 "parser.tab.c"
    break;

  case 45: /* $@6: %empty  */
#line 176 "parser.y"
                                             {
    if((yyvsp[-1].type)=="bool")
        continue;
    else
        yyerror("MUST GIVE BOOL EXPRESSION");

}
#line 1438 "parser.tab.c"
    break;

  case 47: /* RETURNSTMT: RETURN Expression SEMICOLON  */
#line 185 "parser.y"
                                {
        if (function_type != (yyvsp[-1].type))
            yyerror("Return type does not match function return type");
        has_return_statement = true;

    }
#line 1449 "parser.tab.c"
    break;

  case 48: /* RETURNSTMT: RETURN SEMICOLON  */
#line 191 "parser.y"
                     {
        if (function_type != "void")
            yyerror("Non-void function must return a value");
        has_return_statement = true;

    }
#line 1460 "parser.tab.c"
    break;

  case 53: /* Expression: Expression OR AndExpr  */
#line 276 "parser.y"
                          {
        if ((yyvsp[-2].type) == "bool" && (yyvsp[0].type) == "bool")
            (yyval.type) = "bool";
        else {
            yyerror("OR operands must be bool");
            (yyval.type) = "error";
        }
    }
#line 1473 "parser.tab.c"
    break;

  case 54: /* Expression: AndExpr  */
#line 284 "parser.y"
            { (yyval.type) = (yyvsp[0].type); }
#line 1479 "parser.tab.c"
    break;

  case 55: /* AndExpr: AndExpr AND NotExpr  */
#line 288 "parser.y"
                        {
        if ((yyvsp[-2].type) == "bool" && (yyvsp[0].type) == "bool")
            (yyval.type) = "bool";
        else {
            yyerror("AND operands must be bool");
            (yyval.type) = "error";
        }
    }
#line 1492 "parser.tab.c"
    break;

  case 56: /* AndExpr: NotExpr  */
#line 296 "parser.y"
            { (yyval.type) = (yyvsp[0].type); }
#line 1498 "parser.tab.c"
    break;

  case 57: /* NotExpr: NOT NotExpr  */
#line 300 "parser.y"
                {
        if ((yyvsp[0].type) == "bool")
            (yyval.type) = "bool";
        else {
            yyerror("Operand of 'not' must be bool");
            (yyval.type) = "error";
        }
    }
#line 1511 "parser.tab.c"
    break;

  case 58: /* NotExpr: RelationalExpr  */
#line 308 "parser.y"
                   { (yyval.type) = (yyvsp[0].type); }
#line 1517 "parser.tab.c"
    break;

  case 59: /* RelationalExpr: AdditiveExpr  */
#line 312 "parser.y"
                 {
        (yyval.type) = (yyvsp[0].type);
    }
#line 1525 "parser.tab.c"
    break;

  case 60: /* RelationalExpr: AdditiveExpr RELOP AdditiveExpr  */
#line 315 "parser.y"
                                    {
        if ((yyvsp[-2].type) == "int" && (yyvsp[0].type) == "int")
            (yyval.type) = "bool";
        else {
            yyerror("Comparison operands must be int");
            (yyval.type) = "error";
        }
    }
#line 1538 "parser.tab.c"
    break;

  case 67: /* AdditiveExpr: AdditiveExpr ARTHOP MultExpr  */
#line 335 "parser.y"
                                 {
        if ((yyvsp[-2].type) == "int" && (yyvsp[0].type) == "int")
            (yyval.type) = "int";
        else {
            yyerror("Operands of '+' must be int");
            (yyval.type) = "error";
        }
    }
#line 1551 "parser.tab.c"
    break;

  case 68: /* AdditiveExpr: MultExpr  */
#line 344 "parser.y"
             { (yyval.type) = (yyvsp[0].type); }
#line 1557 "parser.tab.c"
    break;

  case 71: /* MultExpr: MultExpr MULOP UnaryExpr  */
#line 352 "parser.y"
                             {
        if ((yyvsp[-2].type) == "int" && (yyvsp[0].type) == "int")
            (yyval.type) = "int";
        else {
            yyerror("Operands of '*' must be int");
            (yyval.type) = "error";
        }
    }
#line 1570 "parser.tab.c"
    break;

  case 72: /* MultExpr: UnaryExpr  */
#line 361 "parser.y"
              { (yyval.type) = (yyvsp[0].type); }
#line 1576 "parser.tab.c"
    break;

  case 76: /* UnaryExpr: MINUS Factor  */
#line 370 "parser.y"
                 {
        if ((yyvsp[0].type) == "int")
            (yyval.type) = "int";
        else {
            yyerror("Unary minus only allowed on int");
            (yyval.type) = "error";
        }
    }
#line 1589 "parser.tab.c"
    break;

  case 77: /* UnaryExpr: Factor  */
#line 378 "parser.y"
           { (yyval.type) = (yyvsp[0].type); }
#line 1595 "parser.tab.c"
    break;

  case 78: /* Factor: INT_LITERAL  */
#line 382 "parser.y"
                      { (yyval.type) = "int"; }
#line 1601 "parser.tab.c"
    break;

  case 79: /* Factor: STRINGLITERAL  */
#line 383 "parser.y"
                      { (yyval.type) = "string"; }
#line 1607 "parser.tab.c"
    break;

  case 80: /* Factor: CHARLITERAL  */
#line 384 "parser.y"
                      { (yyval.type) = "char"; }
#line 1613 "parser.tab.c"
    break;

  case 82: /* Factor: FALSE  */
#line 385 "parser.y"
                      { (yyval.type) = "bool"; }
#line 1619 "parser.tab.c"
    break;

  case 83: /* Factor: ID  */
#line 386 "parser.y"
       {
        (yyval.type) = lookup_type((yyvsp[0].strval));  
        if ((yyval.type) == "error") {
            char msg[128];
            sprintf(msg, "Undeclared variable: %s", (yyvsp[0].strval));
            yyerror(msg);
        }
    }
#line 1632 "parser.tab.c"
    break;

  case 84: /* Factor: '(' Expression ')'  */
#line 394 "parser.y"
                       { (yyval.type) = (yyvsp[-1].type); }
#line 1638 "parser.tab.c"
    break;


#line 1642 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 397 "parser.y"


int main() {
    return yyparse();
}

int yyerror(const char *s) {
    fprintf(stderr, "Parser Error: %s\n", s);
    return 0;
}
