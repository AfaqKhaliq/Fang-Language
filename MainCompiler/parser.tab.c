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
    using namespace std;


    
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



 

    

#line 276 "parser.tab.c"

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
  YYSYMBOL_LESSTHAN = 22,                  /* LESSTHAN  */
  YYSYMBOL_MORETHAN = 23,                  /* MORETHAN  */
  YYSYMBOL_LESSANDEQUAL = 24,              /* LESSANDEQUAL  */
  YYSYMBOL_MOREANDEQUAL = 25,              /* MOREANDEQUAL  */
  YYSYMBOL_EQUAL = 26,                     /* EQUAL  */
  YYSYMBOL_NOTEQUAL = 27,                  /* NOTEQUAL  */
  YYSYMBOL_PLUS = 28,                      /* PLUS  */
  YYSYMBOL_MINUS = 29,                     /* MINUS  */
  YYSYMBOL_MUL = 30,                       /* MUL  */
  YYSYMBOL_DIV = 31,                       /* DIV  */
  YYSYMBOL_MODULO = 32,                    /* MODULO  */
  YYSYMBOL_TRUE = 33,                      /* TRUE  */
  YYSYMBOL_FALSE = 34,                     /* FALSE  */
  YYSYMBOL_PRINT = 35,                     /* PRINT  */
  YYSYMBOL_SCAN = 36,                      /* SCAN  */
  YYSYMBOL_IF = 37,                        /* IF  */
  YYSYMBOL_ELSE = 38,                      /* ELSE  */
  YYSYMBOL_WHILE = 39,                     /* WHILE  */
  YYSYMBOL_RETURN = 40,                    /* RETURN  */
  YYSYMBOL_MAIN = 41,                      /* MAIN  */
  YYSYMBOL_YYACCEPT = 42,                  /* $accept  */
  YYSYMBOL_Program = 43,                   /* Program  */
  YYSYMBOL_MAINFUNCTION = 44,              /* MAINFUNCTION  */
  YYSYMBOL_45_1 = 45,                      /* $@1  */
  YYSYMBOL_FUNCTIONDECLARATIONS = 46,      /* FUNCTIONDECLARATIONS  */
  YYSYMBOL_FUNCTIONDEC = 47,               /* FUNCTIONDEC  */
  YYSYMBOL_48_2 = 48,                      /* $@2  */
  YYSYMBOL_49_3 = 49,                      /* $@3  */
  YYSYMBOL_50_4 = 50,                      /* $@4  */
  YYSYMBOL_RETURNTYPE = 51,                /* RETURNTYPE  */
  YYSYMBOL_PARAMETERS = 52,                /* PARAMETERS  */
  YYSYMBOL_PARAMETERLIST = 53,             /* PARAMETERLIST  */
  YYSYMBOL_PARAMETER = 54,                 /* PARAMETER  */
  YYSYMBOL_BaseType = 55,                  /* BaseType  */
  YYSYMBOL_COMPOUNDSTMT = 56,              /* COMPOUNDSTMT  */
  YYSYMBOL_LOCALDECLARATIONS = 57,         /* LOCALDECLARATIONS  */
  YYSYMBOL_VarDeclaration = 58,            /* VarDeclaration  */
  YYSYMBOL_59_5 = 59,                      /* $@5  */
  YYSYMBOL_IDLIST = 60,                    /* IDLIST  */
  YYSYMBOL_61_6 = 61,                      /* $@6  */
  YYSYMBOL_STMTLIST = 62,                  /* STMTLIST  */
  YYSYMBOL_STATEMENT = 63,                 /* STATEMENT  */
  YYSYMBOL_64_7 = 64,                      /* $@7  */
  YYSYMBOL_ITERATIONSTMT = 65,             /* ITERATIONSTMT  */
  YYSYMBOL_66_8 = 66,                      /* $@8  */
  YYSYMBOL_SELECTIONSTMT = 67,             /* SELECTIONSTMT  */
  YYSYMBOL_MATCHSTMT = 68,                 /* MATCHSTMT  */
  YYSYMBOL_69_9 = 69,                      /* $@9  */
  YYSYMBOL_RETURNSTMT = 70,                /* RETURNSTMT  */
  YYSYMBOL_IOSTMT = 71,                    /* IOSTMT  */
  YYSYMBOL_PRINTSTMT = 72,                 /* PRINTSTMT  */
  YYSYMBOL_SCANESTMT = 73,                 /* SCANESTMT  */
  YYSYMBOL_74_10 = 74,                     /* $@10  */
  YYSYMBOL_EXPRSTMT = 75,                  /* EXPRSTMT  */
  YYSYMBOL_FunctionCall = 76,              /* FunctionCall  */
  YYSYMBOL_77_11 = 77,                     /* $@11  */
  YYSYMBOL_ARGUMENTS = 78,                 /* ARGUMENTS  */
  YYSYMBOL_ARGUMENTSLIST = 79,             /* ARGUMENTSLIST  */
  YYSYMBOL_Expression = 80,                /* Expression  */
  YYSYMBOL_AndExpr = 81,                   /* AndExpr  */
  YYSYMBOL_NotExpr = 82,                   /* NotExpr  */
  YYSYMBOL_RelationalExpr = 83,            /* RelationalExpr  */
  YYSYMBOL_RELOP = 84,                     /* RELOP  */
  YYSYMBOL_AdditiveExpr = 85,              /* AdditiveExpr  */
  YYSYMBOL_ARTHOP = 86,                    /* ARTHOP  */
  YYSYMBOL_MultExpr = 87,                  /* MultExpr  */
  YYSYMBOL_MULOP = 88,                     /* MULOP  */
  YYSYMBOL_UnaryExpr = 89,                 /* UnaryExpr  */
  YYSYMBOL_Factor = 90                     /* Factor  */
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

#if 1

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
#endif /* 1 */

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
#define YYLAST   163

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  95
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  153

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
       0,   227,   227,   232,   231,   247,   248,   253,   258,   262,
     252,   280,   281,   283,   284,   286,   287,   289,   295,   296,
     297,   298,   302,   305,   306,   311,   310,   315,   320,   319,
     326,   327,   333,   334,   334,   335,   336,   337,   338,   343,
     342,   349,   354,   355,   355,   356,   360,   361,   362,   368,
     376,   387,   388,   390,   391,   391,   395,   408,   408,   432,
     433,   439,   454,   472,   479,   486,   493,   496,   504,   508,
     511,   521,   522,   523,   524,   525,   526,   530,   537,   541,
     542,   546,   553,   557,   558,   559,   563,   569,   573,   574,
     575,   576,   576,   577,   578,   587
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
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
  "OR", "AND", "NOT", "LESSTHAN", "MORETHAN", "LESSANDEQUAL",
  "MOREANDEQUAL", "EQUAL", "NOTEQUAL", "PLUS", "MINUS", "MUL", "DIV",
  "MODULO", "TRUE", "FALSE", "PRINT", "SCAN", "IF", "ELSE", "WHILE",
  "RETURN", "MAIN", "$accept", "Program", "MAINFUNCTION", "$@1",
  "FUNCTIONDECLARATIONS", "FUNCTIONDEC", "$@2", "$@3", "$@4", "RETURNTYPE",
  "PARAMETERS", "PARAMETERLIST", "PARAMETER", "BaseType", "COMPOUNDSTMT",
  "LOCALDECLARATIONS", "VarDeclaration", "$@5", "IDLIST", "$@6",
  "STMTLIST", "STATEMENT", "$@7", "ITERATIONSTMT", "$@8", "SELECTIONSTMT",
  "MATCHSTMT", "$@9", "RETURNSTMT", "IOSTMT", "PRINTSTMT", "SCANESTMT",
  "$@10", "EXPRSTMT", "FunctionCall", "$@11", "ARGUMENTS", "ARGUMENTSLIST",
  "Expression", "AndExpr", "NotExpr", "RelationalExpr", "RELOP",
  "AdditiveExpr", "ARTHOP", "MultExpr", "MULOP", "UnaryExpr", "Factor", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-123)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-58)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -123,     8,    35,  -123,   -20,  -123,  -123,  -123,  -123,  -123,
    -123,    36,  -123,    44,    53,    51,  -123,  -123,   110,    69,
    -123,  -123,    65,  -123,    85,   110,  -123,    78,   110,  -123,
    -123,     1,   110,  -123,  -123,    91,    80,    86,    89,   102,
     107,    58,    81,     1,    69,  -123,  -123,  -123,  -123,  -123,
    -123,  -123,  -123,    69,   111,   113,    68,    68,   120,    68,
      68,   114,  -123,  -123,  -123,  -123,    68,    68,   109,  -123,
    -123,  -123,    12,   112,  -123,  -123,   122,    52,  -123,  -123,
    -123,  -123,  -123,  -123,   116,  -123,    13,    11,  -123,    50,
      61,   117,    15,  -123,  -123,  -123,    68,    68,  -123,  -123,
    -123,  -123,  -123,  -123,  -123,  -123,   105,   105,  -123,  -123,
    -123,   105,    91,  -123,   115,   118,    14,  -123,    68,  -123,
     112,  -123,    19,    52,  -123,  -123,  -123,   123,   126,  -123,
      92,    69,  -123,  -123,  -123,    20,   121,   124,   133,  -123,
      68,    14,  -123,  -123,  -123,    68,    62,  -123,   133,    14,
     103,    14,  -123
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       6,     0,     0,     1,    18,    19,    20,    21,    11,     2,
       5,     0,    12,     0,     0,     0,     7,     3,    14,     0,
      18,     8,    13,    15,     0,    24,     4,     0,     0,    17,
      25,    31,    24,     9,    16,     0,     0,     0,     0,     0,
       0,     0,     0,    31,     0,    36,    35,    37,    38,    51,
      52,    32,    23,     0,    27,     0,     0,     0,     0,     0,
       0,    94,    88,    89,    90,    50,     0,     0,     0,    91,
      92,    93,     0,    64,    66,    68,    69,    78,    82,    87,
      22,    30,    34,    10,     0,    26,     0,     0,    54,     0,
       0,     0,     0,    67,    86,    49,     0,     0,    71,    72,
      73,    74,    75,    76,    79,    80,     0,     0,    84,    83,
      85,     0,     0,    56,     0,     0,    43,    39,    60,    95,
      63,    65,    70,    77,    81,    29,    53,     0,     0,    46,
       0,     0,    47,    48,    42,    33,     0,    59,    62,    55,
       0,    43,    44,    40,    58,     0,     0,    41,    61,    43,
       0,    43,    45
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -123,  -123,  -123,  -123,  -123,  -123,  -123,  -123,  -123,  -123,
    -123,  -123,   125,     3,   -33,   127,  -123,  -123,    42,  -123,
     119,    21,  -123,   -31,  -123,  -123,  -122,  -123,   -30,   -29,
    -123,  -123,  -123,   -28,  -123,  -123,  -123,  -123,   -50,    59,
     -45,  -123,  -123,    54,  -123,    56,  -123,    46,    90
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     9,    19,     2,    10,    18,    27,    53,    11,
      21,    22,    23,    24,    26,    31,    32,    35,    55,    84,
      42,    43,    44,   129,   135,    46,   130,   131,   132,   133,
      49,    50,   115,   134,    71,    91,   136,   137,    72,    73,
      74,    75,   106,    76,   107,    77,   111,    78,    79
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      45,    47,    48,    51,    36,    12,    86,    87,     3,    89,
      90,    82,    45,    47,    48,    51,    92,    36,   -33,   147,
      83,    13,    93,    36,    95,   113,   114,   150,    30,   152,
      96,    96,    96,   119,    96,    30,    37,    38,    39,    14,
      40,    41,     4,     5,     6,     7,     8,   104,   105,    37,
      38,   128,   121,    40,    41,    37,    38,    39,    15,    40,
      41,    61,    62,    63,    64,   116,    17,    16,   138,    96,
      65,    61,    62,    63,    64,    66,   117,   149,    28,    67,
      96,    96,   108,   109,   110,    66,    25,    68,    29,    67,
     146,    69,    70,    33,    54,   148,    56,    68,   142,    80,
      57,    69,    70,    58,    45,    47,    48,    51,    61,    62,
      63,    64,    61,    62,    63,    64,    59,    20,     5,     6,
       7,    60,    66,    88,   -28,    85,    66,   126,   -57,   112,
     141,   118,    97,   127,    68,   139,   144,   145,    69,    70,
     140,   151,    69,    70,    98,    99,   100,   101,   102,   103,
     104,   105,    96,    34,   125,   120,   143,   124,    94,    52,
     122,     0,    81,   123
};

static const yytype_int16 yycheck[] =
{
      31,    31,    31,    31,     3,     2,    56,    57,     0,    59,
      60,    44,    43,    43,    43,    43,    66,     3,    17,   141,
      53,    41,    67,     3,    12,    12,    15,   149,    25,   151,
      19,    19,    19,    18,    19,    32,    35,    36,    37,     3,
      39,    40,     7,     8,     9,    10,    11,    28,    29,    35,
      36,    37,    97,    39,    40,    35,    36,    37,    14,    39,
      40,     3,     4,     5,     6,    15,    15,    14,   118,    19,
      12,     3,     4,     5,     6,    17,    15,    15,    13,    21,
      19,    19,    30,    31,    32,    17,    17,    29,     3,    21,
     140,    33,    34,    15,     3,   145,    16,    29,   131,    18,
      14,    33,    34,    14,   135,   135,   135,   135,     3,     4,
       5,     6,     3,     4,     5,     6,    14,     7,     8,     9,
      10,    14,    17,     3,    13,    12,    17,    12,    14,    13,
      38,    14,    20,    15,    29,    12,    15,    13,    33,    34,
      14,    38,    33,    34,    22,    23,    24,    25,    26,    27,
      28,    29,    19,    28,   112,    96,   135,   111,    68,    32,
     106,    -1,    43,   107
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    43,    46,     0,     7,     8,     9,    10,    11,    44,
      47,    51,    55,    41,     3,    14,    14,    15,    48,    45,
       7,    52,    53,    54,    55,    17,    56,    49,    13,     3,
      55,    57,    58,    15,    54,    59,     3,    35,    36,    37,
      39,    40,    62,    63,    64,    65,    67,    70,    71,    72,
      73,    75,    57,    50,     3,    60,    16,    14,    14,    14,
      14,     3,     4,     5,     6,    12,    17,    21,    29,    33,
      34,    76,    80,    81,    82,    83,    85,    87,    89,    90,
      18,    62,    56,    56,    61,    12,    80,    80,     3,    80,
      80,    77,    80,    82,    90,    12,    19,    20,    22,    23,
      24,    25,    26,    27,    28,    29,    84,    86,    30,    31,
      32,    88,    13,    12,    15,    74,    15,    15,    14,    18,
      81,    82,    85,    87,    89,    60,    12,    15,    37,    65,
      68,    69,    70,    71,    75,    66,    78,    79,    80,    12,
      14,    38,    56,    63,    15,    13,    80,    68,    80,    15,
      68,    38,    68
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    45,    44,    46,    46,    48,    49,    50,
      47,    51,    51,    52,    52,    53,    53,    54,    55,    55,
      55,    55,    56,    57,    57,    59,    58,    60,    61,    60,
      62,    62,    63,    64,    63,    63,    63,    63,    63,    66,
      65,    67,    68,    69,    68,    68,    68,    68,    68,    70,
      70,    71,    71,    72,    74,    73,    75,    77,    76,    78,
      78,    79,    79,    80,    80,    81,    81,    82,    82,    83,
      83,    84,    84,    84,    84,    84,    84,    85,    85,    86,
      86,    87,    87,    88,    88,    88,    89,    89,    90,    90,
      90,    90,    90,    90,    90,    90
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     0,     6,     2,     0,     0,     0,     0,
       9,     1,     1,     1,     0,     1,     3,     2,     1,     1,
       1,     1,     4,     2,     0,     0,     4,     1,     0,     4,
       2,     0,     1,     0,     2,     1,     1,     1,     1,     0,
       6,     7,     1,     0,     2,     7,     1,     1,     1,     3,
       2,     1,     1,     5,     0,     6,     4,     0,     5,     1,
       0,     3,     1,     3,     1,     3,     1,     2,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     3,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     3
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


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

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

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
#line 232 "parser.y"
        {
            function_type="int"; 
            has_return_statement = false;
            createScope();
        }
#line 1742 "parser.tab.c"
    break;

  case 4: /* MAINFUNCTION: INT MAIN LPAREN RPAREN $@1 COMPOUNDSTMT  */
#line 238 "parser.y"
        {
            exitScope();
            if (!has_return_statement) {
                    yyerror("Non-void function must end with a return statement");
            }
        }
#line 1753 "parser.tab.c"
    break;

  case 7: /* $@2: %empty  */
#line 253 "parser.y"
        {
            currentSignature.param_types.clear();
            currentSignature.param_id.clear();
        }
#line 1762 "parser.tab.c"
    break;

  case 8: /* $@3: %empty  */
#line 258 "parser.y"
        {
            currentTable->AddFunctionToTable((yyvsp[-3].strval),currentSignature,(yyvsp[-4].strval));
        }
#line 1770 "parser.tab.c"
    break;

  case 9: /* $@4: %empty  */
#line 262 "parser.y"
        {
            createScope();
            currentTable->AddId(currentSignature);
            function_type=(yyvsp[-6].strval);
            //cout<<function_type;
            //printf("Function return type = %s\n", function_type.c_str());
            //fflush(stdout);
            has_return_statement = false;
        }
#line 1784 "parser.tab.c"
    break;

  case 10: /* FUNCTIONDEC: RETURNTYPE ID LPAREN $@2 PARAMETERS $@3 RPAREN $@4 COMPOUNDSTMT  */
#line 272 "parser.y"
        {
            exitScope();
            if ( strcmp((yyvsp[-8].strval),"void")!=0 && !has_return_statement ) {
               yyerror("func() must end with a return statement");
            }
        }
#line 1795 "parser.tab.c"
    break;

  case 11: /* RETURNTYPE: VOID  */
#line 280 "parser.y"
                    {(yyval.strval)=strdup("void");}
#line 1801 "parser.tab.c"
    break;

  case 12: /* RETURNTYPE: BaseType  */
#line 281 "parser.y"
                   {(yyval.strval)=(yyvsp[0].strval);}
#line 1807 "parser.tab.c"
    break;

  case 17: /* PARAMETER: BaseType ID  */
#line 289 "parser.y"
                           {
        currentSignature.param_types.push_back((yyvsp[-1].strval));
        currentSignature.param_id.push_back((yyvsp[0].strval));
    }
#line 1816 "parser.tab.c"
    break;

  case 18: /* BaseType: INT  */
#line 295 "parser.y"
           { (yyval.strval) = strdup("int");  }
#line 1822 "parser.tab.c"
    break;

  case 19: /* BaseType: BOOL  */
#line 296 "parser.y"
           { (yyval.strval) = strdup("bool"); }
#line 1828 "parser.tab.c"
    break;

  case 20: /* BaseType: CHAR  */
#line 297 "parser.y"
           { (yyval.strval) = strdup("char"); }
#line 1834 "parser.tab.c"
    break;

  case 21: /* BaseType: STRING  */
#line 298 "parser.y"
           { (yyval.strval) = strdup("string"); }
#line 1840 "parser.tab.c"
    break;

  case 25: /* $@5: %empty  */
#line 311 "parser.y"
    { current_type = (yyvsp[0].strval); }
#line 1846 "parser.tab.c"
    break;

  case 27: /* IDLIST: ID  */
#line 316 "parser.y"
    { 
        currentTable->AddId((yyvsp[0].strval), current_type);
    }
#line 1854 "parser.tab.c"
    break;

  case 28: /* $@6: %empty  */
#line 320 "parser.y"
    {
        currentTable->AddId((yyvsp[0].strval), current_type);
    }
#line 1862 "parser.tab.c"
    break;

  case 33: /* $@7: %empty  */
#line 334 "parser.y"
     {createScope();}
#line 1868 "parser.tab.c"
    break;

  case 34: /* STATEMENT: $@7 COMPOUNDSTMT  */
#line 334 "parser.y"
                                   {exitScope();}
#line 1874 "parser.tab.c"
    break;

  case 39: /* $@8: %empty  */
#line 343 "parser.y"
    {
        if(std::string((yyvsp[-1].strval)) != "bool" && std::string((yyvsp[-1].strval))!="int")
            yyerror("Must Give bool expression for while loop");
    }
#line 1883 "parser.tab.c"
    break;

  case 41: /* SELECTIONSTMT: IF LPAREN Expression RPAREN MATCHSTMT ELSE MATCHSTMT  */
#line 349 "parser.y"
                                                                   { 
    if (std::string((yyvsp[-4].strval)) != "bool" && std::string((yyvsp[-4].strval))!="int")
        yyerror("Condition must be bool or int");
}
#line 1892 "parser.tab.c"
    break;

  case 43: /* $@9: %empty  */
#line 355 "parser.y"
     { createScope(); }
#line 1898 "parser.tab.c"
    break;

  case 44: /* MATCHSTMT: $@9 COMPOUNDSTMT  */
#line 355 "parser.y"
                                     { exitScope(); }
#line 1904 "parser.tab.c"
    break;

  case 45: /* MATCHSTMT: IF LPAREN Expression RPAREN MATCHSTMT ELSE MATCHSTMT  */
#line 356 "parser.y"
                                                           { 
    if (std::string((yyvsp[-4].strval)) != "bool")
        yyerror("MUST GIVE BOOL EXPRESSION");
}
#line 1913 "parser.tab.c"
    break;

  case 49: /* RETURNSTMT: RETURN Expression SEMICOLON  */
#line 368 "parser.y"
                                {
        if (function_type != std::string((yyvsp[-1].strval))) {
            printf("Return error: expected %s, got %s\n", function_type.c_str(), (yyvsp[-1].strval));
            fflush(stdout);
            yyerror("Return type does not match function return type");
        }
        has_return_statement = true;
    }
#line 1926 "parser.tab.c"
    break;

  case 50: /* RETURNSTMT: RETURN SEMICOLON  */
#line 376 "parser.y"
                     {
        if (function_type != "void") {
            printf("Return error: expected void, got empty return\n");
            fflush(stdout);
            yyerror("Non-void function must return a value");
        }
        has_return_statement = true;
    }
#line 1939 "parser.tab.c"
    break;

  case 54: /* $@10: %empty  */
#line 391 "parser.y"
                         {currentTable->IfExist((yyvsp[0].strval));}
#line 1945 "parser.tab.c"
    break;

  case 56: /* EXPRSTMT: ID ASSIGN Expression SEMICOLON  */
#line 395 "parser.y"
                                  {
        string declared_type =currentTable->lookup((yyvsp[-3].strval));
        if (declared_type != string((yyvsp[-1].strval)))
            yyerror("Type mismatch in assignment");
        cout<<"ID Assigned value\n";

    }
#line 1957 "parser.tab.c"
    break;

  case 57: /* $@11: %empty  */
#line 408 "parser.y"
       {
        checkFunctionCall = currentTable->LookupFunction((yyvsp[0].strval));
        if (!checkFunctionCall || !checkFunctionCall->isFunc) {
            yyerror(("Function '" + std::string((yyvsp[0].strval)) + "' not declared").c_str());
        } else {

            function_type = checkFunctionCall->type;  // Save return type for $$ later
            argument_index = 0;
            parsing_arguments = true;
        }
    }
#line 1973 "parser.tab.c"
    break;

  case 58: /* FunctionCall: ID $@11 LPAREN ARGUMENTS RPAREN  */
#line 419 "parser.y"
                            {
        parsing_arguments = false;
        if (argument_index != checkFunctionCall->param_id.size()) {
            yyerror("Incorrect number of arguments in function call");
        } else {
            (yyval.strval) = strdup(function_type.c_str());
        }
    }
#line 1986 "parser.tab.c"
    break;

  case 59: /* ARGUMENTS: ARGUMENTSLIST  */
#line 432 "parser.y"
                  { }
#line 1992 "parser.tab.c"
    break;

  case 60: /* ARGUMENTS: %empty  */
#line 433 "parser.y"
                  { }
#line 1998 "parser.tab.c"
    break;

  case 61: /* ARGUMENTSLIST: ARGUMENTSLIST COMMA Expression  */
#line 439 "parser.y"
                                   {
        if (parsing_arguments) {
            if (argument_index >= checkFunctionCall->param_types.size()) {
                yyerror("Too many arguments");
            } else if (strcmp((yyvsp[0].strval), checkFunctionCall->param_types[argument_index].c_str()) != 0) {
                char msg[128];
                sprintf(msg, "Argument %d: expected %s, got %s",
                        argument_index + 1,
                        checkFunctionCall->param_types[argument_index].c_str(),
                        (yyvsp[0].strval));
                yyerror(msg);
            }
            argument_index++;
        }
    }
#line 2018 "parser.tab.c"
    break;

  case 62: /* ARGUMENTSLIST: Expression  */
#line 454 "parser.y"
               {
        if (parsing_arguments) {
            if (argument_index >= checkFunctionCall->param_types.size()) {
                yyerror("Too many arguments");
            } else if (strcmp((yyvsp[0].strval), checkFunctionCall->param_types[argument_index].c_str()) != 0) {
                char msg[128];
                sprintf(msg, "Argument %d: expected %s, got %s",
                        argument_index + 1,
                        checkFunctionCall->param_types[argument_index].c_str(),
                        (yyvsp[0].strval));
                yyerror(msg);
            }
            argument_index++;
        }
    }
#line 2038 "parser.tab.c"
    break;

  case 63: /* Expression: Expression OR AndExpr  */
#line 472 "parser.y"
                          {
        if (std::string((yyvsp[-2].strval))=="bool"  && std::string((yyvsp[0].strval))=="bool" )
            (yyval.strval) = strdup("bool"); 
        else {
            yyerror("OR operands must be bool");
        }
    }
#line 2050 "parser.tab.c"
    break;

  case 64: /* Expression: AndExpr  */
#line 479 "parser.y"
            { (yyval.strval) = (yyvsp[0].strval); }
#line 2056 "parser.tab.c"
    break;

  case 65: /* AndExpr: AndExpr AND NotExpr  */
#line 486 "parser.y"
                        {
        if (std::string((yyvsp[-2].strval))=="bool"  && std::string((yyvsp[0].strval))=="bool" )
            (yyval.strval) = strdup("bool"); 
        else {
            yyerror("AND operands must be bool");
        }
    }
#line 2068 "parser.tab.c"
    break;

  case 66: /* AndExpr: NotExpr  */
#line 493 "parser.y"
            { (yyval.strval) = (yyvsp[0].strval); }
#line 2074 "parser.tab.c"
    break;

  case 67: /* NotExpr: NOT NotExpr  */
#line 497 "parser.y"
      {
        if (std::string((yyvsp[0].strval))=="bool")
            (yyval.strval) = strdup("bool"); 
        else {
            yyerror("Operand of 'not' must be bool");
        }
    }
#line 2086 "parser.tab.c"
    break;

  case 68: /* NotExpr: RelationalExpr  */
#line 504 "parser.y"
                   { (yyval.strval) = (yyvsp[0].strval); }
#line 2092 "parser.tab.c"
    break;

  case 69: /* RelationalExpr: AdditiveExpr  */
#line 508 "parser.y"
                 {
        (yyval.strval) = (yyvsp[0].strval);
    }
#line 2100 "parser.tab.c"
    break;

  case 70: /* RelationalExpr: AdditiveExpr RELOP AdditiveExpr  */
#line 511 "parser.y"
                                    {
        if (std::string((yyvsp[-2].strval))==std::string((yyvsp[0].strval))) //type must be same
            (yyval.strval) = strdup("bool"); 
        else {
            yyerror("Comparison operands must be int");
        }
    }
#line 2112 "parser.tab.c"
    break;

  case 77: /* AdditiveExpr: AdditiveExpr ARTHOP MultExpr  */
#line 530 "parser.y"
                                 {
        if (std::string((yyvsp[-2].strval))=="int" && std::string((yyvsp[0].strval))=="int")
            (yyval.strval) = strdup("int");
        else {
            yyerror("Operands of '+' must be int");
        }
    }
#line 2124 "parser.tab.c"
    break;

  case 78: /* AdditiveExpr: MultExpr  */
#line 537 "parser.y"
             { (yyval.strval) = (yyvsp[0].strval); }
#line 2130 "parser.tab.c"
    break;

  case 81: /* MultExpr: MultExpr MULOP UnaryExpr  */
#line 546 "parser.y"
                             {
        if (std::string((yyvsp[-2].strval))=="int"  && std::string((yyvsp[0].strval))=="int")
            (yyval.strval) = strdup("int");
        else {
            yyerror("Operands of '*' must be int");
        }
    }
#line 2142 "parser.tab.c"
    break;

  case 82: /* MultExpr: UnaryExpr  */
#line 553 "parser.y"
              { (yyval.strval) = (yyvsp[0].strval); }
#line 2148 "parser.tab.c"
    break;

  case 86: /* UnaryExpr: MINUS Factor  */
#line 563 "parser.y"
                 {
        if (std::string((yyvsp[0].strval)) == "int")
            (yyval.strval) = strdup("int");
        else
            yyerror("Unary minus only allowed on int");
    }
#line 2159 "parser.tab.c"
    break;

  case 87: /* UnaryExpr: Factor  */
#line 569 "parser.y"
           { (yyval.strval) = (yyvsp[0].strval); }
#line 2165 "parser.tab.c"
    break;

  case 88: /* Factor: INT_LITERAL  */
#line 573 "parser.y"
                      { (yyval.strval) = strdup("int"); }
#line 2171 "parser.tab.c"
    break;

  case 89: /* Factor: STRINGLITERAL  */
#line 574 "parser.y"
                      { (yyval.strval) = strdup("string"); }
#line 2177 "parser.tab.c"
    break;

  case 90: /* Factor: CHARLITERAL  */
#line 575 "parser.y"
                      { (yyval.strval) = strdup("char"); }
#line 2183 "parser.tab.c"
    break;

  case 92: /* Factor: FALSE  */
#line 576 "parser.y"
                      { (yyval.strval) = strdup("bool"); }
#line 2189 "parser.tab.c"
    break;

  case 93: /* Factor: FunctionCall  */
#line 577 "parser.y"
                 {(yyval.strval) = strdup((yyvsp[0].strval));}
#line 2195 "parser.tab.c"
    break;

  case 94: /* Factor: ID  */
#line 578 "parser.y"
       {  
    char* var=currentTable->lookup((yyvsp[0].strval));
        if (!var) {
            char msg[128];
            sprintf(msg, "Undeclared variable: %s", (yyvsp[0].strval));
            yyerror(msg);
        }
        else{ (yyval.strval)=strdup(var);}
    }
#line 2209 "parser.tab.c"
    break;

  case 95: /* Factor: LBRACE Expression RBRACE  */
#line 587 "parser.y"
                             { (yyval.strval) = (yyvsp[-1].strval); }
#line 2215 "parser.tab.c"
    break;


#line 2219 "parser.tab.c"

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 592 "parser.y"


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
