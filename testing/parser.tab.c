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
#line 16 "parser.y"

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
    #include<sstream>
    #include <fstream>
    using namespace std;

 

    int currentCodeLine=0;
    vector<string> Code(1000);

    void saveTACToFile(const string& filename) {
        ofstream outFile(filename);
        if (!outFile) {
            cerr << "Error: Could not open file " << filename << " for writing.\n";
            return;
        }

        for (int i = 0; i < currentCodeLine; ++i) {
            outFile << i << ": " << Code[i] << "\n";
        }

        outFile.close();
        cout << "TAC saved to " << filename << endl;
    }

    void backpatch(const std::vector<int>* PatchList, int target) {
            for (auto i : *PatchList) {
                Code[i] += " " + std::to_string(target);
            }
    }

    std::vector<int>* merge(const std::vector<int>* list1, const std::vector<int>* list2) {
            std::vector<int>* result = new std::vector<int>(*list1);  // Copy contents of list1
            result->insert(result->end(), list2->begin(), list2->end());  // Append contents of list2
            return result;
    }



    vector<int>* MakeList(int x){
        vector<int>* ptr= new vector<int>;
        ptr->push_back(x);
        return ptr;
    }

    int tempcount=0;
    string genTemp(){
        ostringstream oss;
        oss<<"t"<<++tempcount;
        return oss.str();
    }


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

        bool IfExist(const string& name) {
            if (Table.count(name)) {
                return true;
            } else {
                return false;
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



 

    

#line 324 "parser.tab.c"

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
  YYSYMBOL_68_9 = 68,                      /* @9  */
  YYSYMBOL_69_10 = 69,                     /* $@10  */
  YYSYMBOL_70_11 = 70,                     /* @11  */
  YYSYMBOL_71_12 = 71,                     /* $@12  */
  YYSYMBOL_MATCHSTMT = 72,                 /* MATCHSTMT  */
  YYSYMBOL_73_13 = 73,                     /* $@13  */
  YYSYMBOL_midMarker = 74,                 /* midMarker  */
  YYSYMBOL_RETURNSTMT = 75,                /* RETURNSTMT  */
  YYSYMBOL_IOSTMT = 76,                    /* IOSTMT  */
  YYSYMBOL_PRINTSTMT = 77,                 /* PRINTSTMT  */
  YYSYMBOL_SCANESTMT = 78,                 /* SCANESTMT  */
  YYSYMBOL_79_14 = 79,                     /* $@14  */
  YYSYMBOL_EXPRSTMT = 80,                  /* EXPRSTMT  */
  YYSYMBOL_FunctionCall = 81,              /* FunctionCall  */
  YYSYMBOL_82_15 = 82,                     /* $@15  */
  YYSYMBOL_ARGUMENTS = 83,                 /* ARGUMENTS  */
  YYSYMBOL_ARGUMENTSLIST = 84,             /* ARGUMENTSLIST  */
  YYSYMBOL_Expression = 85,                /* Expression  */
  YYSYMBOL_AndExpr = 86,                   /* AndExpr  */
  YYSYMBOL_NotExpr = 87,                   /* NotExpr  */
  YYSYMBOL_RelationalExpr = 88,            /* RelationalExpr  */
  YYSYMBOL_RELOP = 89,                     /* RELOP  */
  YYSYMBOL_AdditiveExpr = 90,              /* AdditiveExpr  */
  YYSYMBOL_ARTHOP = 91,                    /* ARTHOP  */
  YYSYMBOL_MultExpr = 92,                  /* MultExpr  */
  YYSYMBOL_MULOP = 93,                     /* MULOP  */
  YYSYMBOL_UnaryExpr = 94,                 /* UnaryExpr  */
  YYSYMBOL_Factor = 95                     /* Factor  */
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
#define YYLAST   152

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  54
/* YYNRULES -- Number of rules.  */
#define YYNRULES  100
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  160

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
       0,   292,   292,   297,   296,   315,   316,   321,   326,   330,
     320,   348,   349,   351,   352,   354,   355,   357,   363,   364,
     365,   366,   370,   375,   376,   381,   380,   388,   394,   393,
     402,   403,   409,   410,   410,   411,   412,   413,   414,   419,
     419,   440,   443,   448,   454,   440,   462,   463,   463,   464,
     468,   469,   470,   473,   478,   487,   501,   502,   506,   513,
     513,   525,   539,   539,   571,   572,   578,   595,   616,   627,
     631,   642,   646,   656,   660,   661,   677,   678,   679,   680,
     681,   682,   686,   697,   701,   702,   706,   724,   731,   732,
     733,   737,   750,   757,   762,   767,   772,   777,   782,   783,
     796
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
  "@9", "$@10", "@11", "$@12", "MATCHSTMT", "$@13", "midMarker",
  "RETURNSTMT", "IOSTMT", "PRINTSTMT", "SCANESTMT", "$@14", "EXPRSTMT",
  "FunctionCall", "$@15", "ARGUMENTS", "ARGUMENTSLIST", "Expression",
  "AndExpr", "NotExpr", "RelationalExpr", "RELOP", "AdditiveExpr",
  "ARTHOP", "MultExpr", "MULOP", "UnaryExpr", "Factor", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-94)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-63)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -94,     5,   101,   -94,   -34,   -94,   -94,   -94,   -94,   -94,
     -94,    20,   -94,    -4,    11,    19,   -94,   -94,   113,    39,
     -94,   -94,    23,   -94,    72,   113,   -94,    78,   113,   -94,
     -94,    76,   113,   -94,   -94,    93,    79,    76,     3,   -94,
      39,    88,    86,   -94,   -94,    97,   102,   103,   110,   111,
      47,    39,   -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,
     114,   -94,    66,    66,   112,   -94,   -94,   115,   -94,   -94,
     -94,   -94,    66,    66,    24,   -94,   -94,   -94,    35,   106,
     -94,   -94,    -8,    73,   -94,   -94,   -94,    93,    43,     7,
     -94,    66,    66,   116,    48,   -94,   -94,   -94,    66,    66,
     -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,    85,    85,
     -94,   -94,   -94,    85,   -94,   -94,   119,   117,    58,    59,
      66,   -94,   106,   -94,    56,    73,   -94,   -94,   121,   -94,
     -94,   120,   123,   109,   -94,   -94,   -94,   -94,    66,   -94,
       9,   -94,   109,    96,   124,   -94,    39,   -94,   -94,   -94,
     -94,    66,   -94,   -94,    67,   -94,   -94,    99,   -94,   -94
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       6,     0,     0,     1,    18,    19,    20,    21,    11,     2,
       5,     0,    12,     0,     0,     0,     7,     3,    14,     0,
      18,     8,    13,    15,     0,    24,     4,     0,     0,    17,
      25,    53,    24,     9,    16,     0,     0,    53,    33,    23,
       0,    27,     0,    22,    30,     0,     0,     0,     0,     0,
       0,     0,    36,    35,    37,    38,    56,    57,    32,    10,
       0,    26,     0,     0,     0,    41,    53,    99,    93,    94,
      95,    55,     0,     0,     0,    96,    97,    98,     0,    69,
      71,    73,    74,    83,    87,    92,    34,     0,     0,     0,
      59,     0,     0,     0,     0,    72,    91,    54,     0,     0,
      76,    77,    78,    79,    80,    81,    84,    85,     0,     0,
      89,    88,    90,     0,    29,    61,     0,     0,     0,     0,
      65,   100,    68,    70,    75,    82,    86,    58,     0,    42,
      39,     0,    64,    67,    60,    53,    53,    63,     0,    43,
      47,    40,    66,     0,     0,    50,     0,    51,    52,    46,
      44,     0,    48,    53,     0,    45,    53,     0,    53,    49
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,
     -94,   -94,   118,    -1,   -40,   107,   -94,   -94,    53,   -94,
     104,     6,   -94,     4,   -94,   -94,   -94,   -94,   -94,   -94,
     -93,   -94,   -29,     8,    10,   -94,   -94,   -94,    12,   -94,
     -94,   -94,   -94,   -59,    45,   -64,   -94,   -94,    37,   -94,
      38,   -94,    36,    77
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     9,    19,     2,    10,    18,    27,    40,    11,
      21,    22,    23,    24,    26,    31,    32,    35,    42,    60,
      36,    37,    51,    52,   136,    53,    91,   135,   143,   153,
     139,   146,   140,    54,    55,    56,    57,   117,    58,    77,
      93,   131,   132,    78,    79,    80,    81,   108,    82,   109,
      83,   113,    84,    85
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      59,    12,    38,    88,    89,     3,    45,    13,    38,    95,
      15,    86,    45,    94,   100,   101,   102,   103,   104,   105,
     106,   107,   116,    14,    30,    16,    98,    67,    68,    69,
      70,    30,   118,   119,    17,   123,    28,    92,    46,    47,
      48,    72,    49,    50,    46,    47,   144,    97,    49,    50,
      67,    68,    69,    70,    98,   115,    25,    75,    76,    71,
     155,   133,    98,   157,    72,   159,   121,    98,    73,    67,
      68,    69,    70,   129,   130,    29,    74,    98,    98,   142,
      75,    76,   156,    72,   106,   107,    98,    73,    67,    68,
      69,    70,   154,    33,   -31,    74,    41,    43,    61,    75,
      76,   -28,    72,   110,   111,   112,   152,    38,     4,     5,
       6,     7,     8,    62,    74,    90,    63,    64,    75,    76,
      20,     5,     6,     7,    65,    66,    99,    87,    98,   -62,
     120,   127,   128,   134,   150,   137,   138,   158,   151,    39,
     114,    44,   141,   122,   145,   124,    34,   125,   147,   126,
     148,    96,   149
};

static const yytype_uint8 yycheck[] =
{
      40,     2,    31,    62,    63,     0,     3,    41,    37,    73,
      14,    51,     3,    72,    22,    23,    24,    25,    26,    27,
      28,    29,    15,     3,    25,    14,    19,     3,     4,     5,
       6,    32,    91,    92,    15,    99,    13,    66,    35,    36,
      37,    17,    39,    40,    35,    36,    37,    12,    39,    40,
       3,     4,     5,     6,    19,    12,    17,    33,    34,    12,
     153,   120,    19,   156,    17,   158,    18,    19,    21,     3,
       4,     5,     6,    15,    15,     3,    29,    19,    19,   138,
      33,    34,    15,    17,    28,    29,    19,    21,     3,     4,
       5,     6,   151,    15,    18,    29,     3,    18,    12,    33,
      34,    13,    17,    30,    31,    32,   146,   136,     7,     8,
       9,    10,    11,    16,    29,     3,    14,    14,    33,    34,
       7,     8,     9,    10,    14,    14,    20,    13,    19,    14,
      14,    12,    15,    12,    38,    15,    13,    38,    14,    32,
      87,    37,   136,    98,   140,   108,    28,   109,   140,   113,
     140,    74,   140
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    43,    46,     0,     7,     8,     9,    10,    11,    44,
      47,    51,    55,    41,     3,    14,    14,    15,    48,    45,
       7,    52,    53,    54,    55,    17,    56,    49,    13,     3,
      55,    57,    58,    15,    54,    59,    62,    63,    74,    57,
      50,     3,    60,    18,    62,     3,    35,    36,    37,    39,
      40,    64,    65,    67,    75,    76,    77,    78,    80,    56,
      61,    12,    16,    14,    14,    14,    14,     3,     4,     5,
       6,    12,    17,    21,    29,    33,    34,    81,    85,    86,
      87,    88,    90,    92,    94,    95,    56,    13,    85,    85,
       3,    68,    74,    82,    85,    87,    95,    12,    19,    20,
      22,    23,    24,    25,    26,    27,    28,    29,    89,    91,
      30,    31,    32,    93,    60,    12,    15,    79,    85,    85,
      14,    18,    86,    87,    90,    92,    94,    12,    15,    15,
      15,    83,    84,    85,    12,    69,    66,    15,    13,    72,
      74,    63,    85,    70,    37,    65,    73,    75,    76,    80,
      38,    14,    56,    71,    85,    72,    15,    72,    38,    72
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    45,    44,    46,    46,    48,    49,    50,
      47,    51,    51,    52,    52,    53,    53,    54,    55,    55,
      55,    55,    56,    57,    57,    59,    58,    60,    61,    60,
      62,    62,    63,    64,    63,    63,    63,    63,    63,    66,
      65,    68,    69,    70,    71,    67,    72,    73,    72,    72,
      72,    72,    72,    74,    75,    75,    76,    76,    77,    79,
      78,    80,    82,    81,    83,    83,    84,    84,    85,    85,
      86,    86,    87,    87,    88,    88,    89,    89,    89,    89,
      89,    89,    90,    90,    91,    91,    92,    92,    93,    93,
      93,    94,    94,    95,    95,    95,    95,    95,    95,    95,
      95
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     0,     6,     2,     0,     0,     0,     0,
       9,     1,     1,     1,     0,     1,     3,     2,     1,     1,
       1,     1,     4,     2,     0,     0,     4,     1,     0,     4,
       2,     0,     2,     0,     3,     2,     2,     2,     2,     0,
       7,     0,     0,     0,     0,    11,     2,     0,     3,     8,
       2,     2,     2,     0,     3,     2,     1,     1,     5,     0,
       6,     4,     0,     5,     1,     0,     3,     1,     3,     1,
       3,     1,     2,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     3,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       3
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
#line 297 "parser.y"
        {
            function_type = "int"; 
            has_return_statement = false;
            createScope();
            Code[currentCodeLine++] = "func main:";
        }
#line 1800 "parser.tab.c"
    break;

  case 4: /* MAINFUNCTION: INT MAIN LPAREN RPAREN $@1 COMPOUNDSTMT  */
#line 304 "parser.y"
        {
            exitScope();
            if (!has_return_statement) {
                yyerror("Non-void function must end with a return statement");
            }
            Code[currentCodeLine++] = "endfunc";
        }
#line 1812 "parser.tab.c"
    break;

  case 7: /* $@2: %empty  */
#line 321 "parser.y"
        {
            currentSignature.param_types.clear();
            currentSignature.param_id.clear();
        }
#line 1821 "parser.tab.c"
    break;

  case 8: /* $@3: %empty  */
#line 326 "parser.y"
        {
            currentTable->AddFunctionToTable((yyvsp[-3].strval),currentSignature,(yyvsp[-4].strval));
        }
#line 1829 "parser.tab.c"
    break;

  case 9: /* $@4: %empty  */
#line 330 "parser.y"
        {
            createScope();
            currentTable->AddId(currentSignature);
            function_type = (yyvsp[-6].strval);
            has_return_statement = false;
            Code[currentCodeLine++] = "func " + std::string((yyvsp[-5].strval)) + ":";
        }
#line 1841 "parser.tab.c"
    break;

  case 10: /* FUNCTIONDEC: RETURNTYPE ID LPAREN $@2 PARAMETERS $@3 RPAREN $@4 COMPOUNDSTMT  */
#line 338 "parser.y"
        {
            exitScope();
            if (strcmp((yyvsp[-8].strval), "void") != 0 && !has_return_statement) {
                yyerror("func() must end with a return statement");
            }
            Code[currentCodeLine++] = "endfunc";
        }
#line 1853 "parser.tab.c"
    break;

  case 11: /* RETURNTYPE: VOID  */
#line 348 "parser.y"
                    {(yyval.strval)=strdup("void");}
#line 1859 "parser.tab.c"
    break;

  case 12: /* RETURNTYPE: BaseType  */
#line 349 "parser.y"
                   {(yyval.strval)=(yyvsp[0].strval);}
#line 1865 "parser.tab.c"
    break;

  case 17: /* PARAMETER: BaseType ID  */
#line 357 "parser.y"
                           {
        currentSignature.param_types.push_back((yyvsp[-1].strval));
        currentSignature.param_id.push_back((yyvsp[0].strval));
    }
#line 1874 "parser.tab.c"
    break;

  case 18: /* BaseType: INT  */
#line 363 "parser.y"
           { (yyval.strval) = strdup("int");  }
#line 1880 "parser.tab.c"
    break;

  case 19: /* BaseType: BOOL  */
#line 364 "parser.y"
           { (yyval.strval) = strdup("bool"); }
#line 1886 "parser.tab.c"
    break;

  case 20: /* BaseType: CHAR  */
#line 365 "parser.y"
           { (yyval.strval) = strdup("char"); }
#line 1892 "parser.tab.c"
    break;

  case 21: /* BaseType: STRING  */
#line 366 "parser.y"
           { (yyval.strval) = strdup("string"); }
#line 1898 "parser.tab.c"
    break;

  case 25: /* $@5: %empty  */
#line 381 "parser.y"
    {
        current_type = (yyvsp[0].strval);
    }
#line 1906 "parser.tab.c"
    break;

  case 27: /* IDLIST: ID  */
#line 389 "parser.y"
    {
        currentTable->AddId((yyvsp[0].strval), current_type);
        Code[currentCodeLine++] = "declare " + std::string((yyvsp[0].strval)) + " : " + current_type;
    }
#line 1915 "parser.tab.c"
    break;

  case 28: /* $@6: %empty  */
#line 394 "parser.y"
    {
        currentTable->AddId((yyvsp[0].strval), current_type);
        Code[currentCodeLine++] = "declare " + std::string((yyvsp[0].strval)) + " : " + current_type;
    }
#line 1924 "parser.tab.c"
    break;

  case 32: /* STATEMENT: midMarker EXPRSTMT  */
#line 409 "parser.y"
                             {(yyval.strval)=(yyvsp[-1].strval);}
#line 1930 "parser.tab.c"
    break;

  case 33: /* $@7: %empty  */
#line 410 "parser.y"
               {createScope();}
#line 1936 "parser.tab.c"
    break;

  case 34: /* STATEMENT: midMarker $@7 COMPOUNDSTMT  */
#line 410 "parser.y"
                                             {exitScope(); (yyval.strval)=(yyvsp[-2].strval);}
#line 1942 "parser.tab.c"
    break;

  case 35: /* STATEMENT: midMarker SELECTIONSTMT  */
#line 411 "parser.y"
                             {(yyval.strval)=(yyvsp[-1].strval);}
#line 1948 "parser.tab.c"
    break;

  case 36: /* STATEMENT: midMarker ITERATIONSTMT  */
#line 412 "parser.y"
                              {(yyval.strval)=(yyvsp[-1].strval);}
#line 1954 "parser.tab.c"
    break;

  case 37: /* STATEMENT: midMarker RETURNSTMT  */
#line 413 "parser.y"
                           {(yyval.strval)=(yyvsp[-1].strval);}
#line 1960 "parser.tab.c"
    break;

  case 38: /* STATEMENT: midMarker IOSTMT  */
#line 414 "parser.y"
                       {(yyval.strval)=(yyvsp[-1].strval);}
#line 1966 "parser.tab.c"
    break;

  case 39: /* $@8: %empty  */
#line 419 "parser.y"
                                              {
        if (std::string((yyvsp[-1].attribute)->type) != "bool") {
            yyerror("While condition must be bool");
        }

        
    }
#line 1978 "parser.tab.c"
    break;

  case 40: /* ITERATIONSTMT: WHILE LPAREN midMarker Expression RPAREN $@8 STATEMENT  */
#line 426 "parser.y"
              {
        // Backpatch truelist of the condition to start of body
        backpatch((yyvsp[-3].attribute)->truelist, std::stoi((yyvsp[0].strval)));

        // Add jump back to condition after body
        Code[currentCodeLine++] = "goto " + string((yyvsp[-4].strval));

        // Mark falselist (loop exit) to next instruction
        backpatch((yyvsp[-3].attribute)->falselist, currentCodeLine); //next line
    }
#line 1993 "parser.tab.c"
    break;

  case 41: /* @9: %empty  */
#line 440 "parser.y"
             {
        (yyval.intval) = currentCodeLine; 
        // Save the line number where the condition starts
    }
#line 2002 "parser.tab.c"
    break;

  case 42: /* $@10: %empty  */
#line 443 "parser.y"
                        {
        if (std::string((yyvsp[-1].attribute)->type) != "bool") {
            yyerror("Condition must be bool");
        }
    }
#line 2012 "parser.tab.c"
    break;

  case 43: /* @11: %empty  */
#line 448 "parser.y"
              {
        int afterIf = currentCodeLine++;
        Code[afterIf] = "goto "; // Jump over ELSE
        (yyval.intval) = afterIf;
        backpatch((yyvsp[-3].attribute)->truelist, std::stoi((yyvsp[0].strval)));
    }
#line 2023 "parser.tab.c"
    break;

  case 44: /* $@12: %empty  */
#line 454 "parser.y"
         {
        backpatch((yyvsp[-5].attribute)->falselist, currentCodeLine);
    }
#line 2031 "parser.tab.c"
    break;

  case 45: /* SELECTIONSTMT: IF LPAREN @9 Expression RPAREN $@10 MATCHSTMT @11 ELSE $@12 MATCHSTMT  */
#line 457 "parser.y"
              {
        backpatch(MakeList((yyvsp[-3].intval)), currentCodeLine); // Fill jump over ELSE
    }
#line 2039 "parser.tab.c"
    break;

  case 46: /* MATCHSTMT: midMarker EXPRSTMT  */
#line 462 "parser.y"
                             {(yyval.strval)=(yyvsp[-1].strval);}
#line 2045 "parser.tab.c"
    break;

  case 47: /* $@13: %empty  */
#line 463 "parser.y"
               {createScope();}
#line 2051 "parser.tab.c"
    break;

  case 48: /* MATCHSTMT: midMarker $@13 COMPOUNDSTMT  */
#line 463 "parser.y"
                                             { exitScope(); (yyval.strval)=(yyvsp[-2].strval);}
#line 2057 "parser.tab.c"
    break;

  case 49: /* MATCHSTMT: midMarker IF LPAREN Expression RPAREN MATCHSTMT ELSE MATCHSTMT  */
#line 464 "parser.y"
                                                                    { 
    if (std::string((yyvsp[-4].attribute)->type) != "bool")
        yyerror("MUST GIVE BOOL EXPRESSION");
    }
#line 2066 "parser.tab.c"
    break;

  case 50: /* MATCHSTMT: midMarker ITERATIONSTMT  */
#line 468 "parser.y"
                               {(yyval.strval)=(yyvsp[-1].strval);}
#line 2072 "parser.tab.c"
    break;

  case 51: /* MATCHSTMT: midMarker RETURNSTMT  */
#line 469 "parser.y"
                            {(yyval.strval)=(yyvsp[-1].strval);}
#line 2078 "parser.tab.c"
    break;

  case 52: /* MATCHSTMT: midMarker IOSTMT  */
#line 470 "parser.y"
                       {(yyval.strval)=(yyvsp[-1].strval);}
#line 2084 "parser.tab.c"
    break;

  case 53: /* midMarker: %empty  */
#line 473 "parser.y"
          {(yyval.strval) = strdup(std::to_string(currentCodeLine).c_str());}
#line 2090 "parser.tab.c"
    break;

  case 54: /* RETURNSTMT: RETURN Expression SEMICOLON  */
#line 478 "parser.y"
                                {
        if (function_type != std::string((yyvsp[-1].attribute)->type)) {
            printf("Return error: expected %s, got %s\n", function_type.c_str(), (yyvsp[-1].attribute)->type);
            fflush(stdout);
            yyerror("Return type does not match function return type");
        }
        Code[currentCodeLine++] = "return " + std::string((yyvsp[-1].attribute)->place);
        has_return_statement = true;
    }
#line 2104 "parser.tab.c"
    break;

  case 55: /* RETURNSTMT: RETURN SEMICOLON  */
#line 487 "parser.y"
                     {
        if (function_type != "void") {
            printf("Return error: expected void, got empty return\n");
            fflush(stdout);
            yyerror("Non-void function must return a value");
        }
        Code[currentCodeLine++] = "return";  // For void return
        has_return_statement = true;
    }
#line 2118 "parser.tab.c"
    break;

  case 58: /* PRINTSTMT: PRINT LPAREN Expression RPAREN SEMICOLON  */
#line 506 "parser.y"
                                             {
        Code[currentCodeLine++] = "param " + std::string((yyvsp[-2].attribute)->place);
        Code[currentCodeLine++] = "call print,1 ";
    }
#line 2127 "parser.tab.c"
    break;

  case 59: /* $@14: %empty  */
#line 513 "parser.y"
                   {
        if(!currentTable->IfExist((yyvsp[0].strval)))
        {
            yyerror("Identifier does not exist");
        } 
    }
#line 2138 "parser.tab.c"
    break;

  case 60: /* SCANESTMT: SCAN LPAREN ID $@14 RPAREN SEMICOLON  */
#line 518 "parser.y"
                       {
        Code[currentCodeLine++] = "param " + std::string((yyvsp[-3].strval));
        Code[currentCodeLine++] = "call scan,1 ";
    }
#line 2147 "parser.tab.c"
    break;

  case 61: /* EXPRSTMT: ID ASSIGN Expression SEMICOLON  */
#line 525 "parser.y"
                                   {
        string declared_type = currentTable->lookup((yyvsp[-3].strval));
        if (declared_type != std::string((yyvsp[-1].attribute)->type)) {
            yyerror("Type mismatch in assignment");
        }

        Code[currentCodeLine++] = std::string((yyvsp[-3].strval)) + " = " + std::string((yyvsp[-1].attribute)->place);
    }
#line 2160 "parser.tab.c"
    break;

  case 62: /* $@15: %empty  */
#line 539 "parser.y"
       {
        checkFunctionCall = currentTable->LookupFunction((yyvsp[0].strval));
        if (!checkFunctionCall || !checkFunctionCall->isFunc) {
            yyerror(("Function '" + std::string((yyvsp[0].strval)) + "' not declared").c_str());
        } else {
            function_type = checkFunctionCall->type;  // Save return type
            argument_index = 0;
            parsing_arguments = true;
        }
    }
#line 2175 "parser.tab.c"
    break;

  case 63: /* FunctionCall: ID $@15 LPAREN ARGUMENTS RPAREN  */
#line 549 "parser.y"
                            {
        parsing_arguments = false;
        
        if (!checkFunctionCall) {
            yyerror("Function Doesn't Exist\n");
        } else if (argument_index != checkFunctionCall->param_types.size()) {
            yyerror("Incorrect number of arguments in function call\n");
    
        } else {
            (yyval.attribute) = new Attr();
            (yyval.attribute)->type = strdup(function_type.c_str());
            std::string temp = genTemp();
            Code[currentCodeLine++] = temp + " = call " + std::string((yyvsp[-4].strval));
            (yyval.attribute)->place = strdup(temp.c_str());
        }
    }
#line 2196 "parser.tab.c"
    break;

  case 64: /* ARGUMENTS: ARGUMENTSLIST  */
#line 571 "parser.y"
                  { }
#line 2202 "parser.tab.c"
    break;

  case 65: /* ARGUMENTS: %empty  */
#line 572 "parser.y"
                  { }
#line 2208 "parser.tab.c"
    break;

  case 66: /* ARGUMENTSLIST: ARGUMENTSLIST COMMA Expression  */
#line 578 "parser.y"
                                   {
        if (parsing_arguments) {
            if (argument_index >= checkFunctionCall->param_types.size()) {
                yyerror("Too many arguments in function call");
            } else if (std::string((yyvsp[0].attribute)->type) != checkFunctionCall->param_types[argument_index]) {
                char msg[256];
                sprintf(msg, "Argument %d: expected %s, got %s",
                        argument_index + 1,
                        checkFunctionCall->param_types[argument_index].c_str(),
                        (yyvsp[0].attribute)->type);
                yyerror(msg);
            }
            // ✅ TAC generation
            Code[currentCodeLine++] = "param " + std::string((yyvsp[0].attribute)->place);
            argument_index++;
        }
    }
#line 2230 "parser.tab.c"
    break;

  case 67: /* ARGUMENTSLIST: Expression  */
#line 595 "parser.y"
               {
        if (parsing_arguments) {
            if (argument_index >= checkFunctionCall->param_types.size()) {
                yyerror("Too many arguments in function call");
            } else if (std::string((yyvsp[0].attribute)->type) != checkFunctionCall->param_types[argument_index]) {
                char msg[256];
                sprintf(msg, "Argument %d: expected %s, got %s",
                        argument_index + 1,
                        checkFunctionCall->param_types[argument_index].c_str(),
                        (yyvsp[0].attribute)->type);
                yyerror(msg);
            }
            // ✅ TAC generation
            Code[currentCodeLine++] = "param " + std::string((yyvsp[0].attribute)->place);
            argument_index++;
        }
    }
#line 2252 "parser.tab.c"
    break;

  case 68: /* Expression: Expression OR AndExpr  */
#line 616 "parser.y"
                          {
        if (std::string((yyvsp[-2].attribute)->type) == "bool" && std::string((yyvsp[0].attribute)->type) == "bool") {
            (yyval.attribute) = new Attr();
            (yyval.attribute)->type = strdup("bool");
            (yyval.attribute)->truelist = merge((yyvsp[-2].attribute)->truelist, (yyvsp[0].attribute)->truelist);
            (yyval.attribute)->falselist = (yyvsp[0].attribute)->falselist;
            backpatch((yyvsp[-2].attribute)->falselist, currentCodeLine);  // evaluate second condition only if first is false
        } else {
            yyerror("OR operands must be bool");
        }
    }
#line 2268 "parser.tab.c"
    break;

  case 69: /* Expression: AndExpr  */
#line 627 "parser.y"
            { (yyval.attribute) = (yyvsp[0].attribute); }
#line 2274 "parser.tab.c"
    break;

  case 70: /* AndExpr: AndExpr AND NotExpr  */
#line 631 "parser.y"
                        {
        if (std::string((yyvsp[-2].attribute)->type) == "bool" && std::string((yyvsp[0].attribute)->type) == "bool") {
            (yyval.attribute) = new Attr();
            (yyval.attribute)->type = strdup("bool");
            (yyval.attribute)->truelist = (yyvsp[0].attribute)->truelist;
            (yyval.attribute)->falselist = merge((yyvsp[-2].attribute)->falselist, (yyvsp[0].attribute)->falselist);
            backpatch((yyvsp[-2].attribute)->truelist, currentCodeLine);  // evaluate second condition only if first is true
        } else {
            yyerror("AND operands must be bool");
        }
    }
#line 2290 "parser.tab.c"
    break;

  case 71: /* AndExpr: NotExpr  */
#line 642 "parser.y"
            { (yyval.attribute) = (yyvsp[0].attribute); }
#line 2296 "parser.tab.c"
    break;

  case 72: /* NotExpr: NOT NotExpr  */
#line 646 "parser.y"
                {
        if (std::string((yyvsp[0].attribute)->type) == "bool") {
            (yyval.attribute) = new Attr();
            (yyval.attribute)->type = strdup("bool");
            (yyval.attribute)->truelist = (yyvsp[0].attribute)->falselist;
            (yyval.attribute)->falselist = (yyvsp[0].attribute)->truelist;
        } else {
            yyerror("Operand of 'not' must be bool");
        }
    }
#line 2311 "parser.tab.c"
    break;

  case 73: /* NotExpr: RelationalExpr  */
#line 656 "parser.y"
                   { (yyval.attribute) = (yyvsp[0].attribute); }
#line 2317 "parser.tab.c"
    break;

  case 74: /* RelationalExpr: AdditiveExpr  */
#line 660 "parser.y"
                 { (yyval.attribute) = (yyvsp[0].attribute); }
#line 2323 "parser.tab.c"
    break;

  case 75: /* RelationalExpr: AdditiveExpr RELOP AdditiveExpr  */
#line 661 "parser.y"
                                    {
        if (std::string((yyvsp[-2].attribute)->type) == std::string((yyvsp[0].attribute)->type)) {
            (yyval.attribute) = new Attr();
            (yyval.attribute)->type = strdup("bool");
            string relop = (yyvsp[-1].strval);
            Code[currentCodeLine] = "if " + string((yyvsp[-2].attribute)->place) + " " + relop + " " + string((yyvsp[0].attribute)->place) + " goto ";
            (yyval.attribute)->truelist = MakeList(currentCodeLine++);
            Code[currentCodeLine] = "goto ";
            (yyval.attribute)->falselist = MakeList(currentCodeLine++);
        } else {
            yyerror("Comparison operands must be of the same type");
        }
    }
#line 2341 "parser.tab.c"
    break;

  case 76: /* RELOP: LESSTHAN  */
#line 677 "parser.y"
                 { (yyval.strval) = strdup("<"); }
#line 2347 "parser.tab.c"
    break;

  case 77: /* RELOP: MORETHAN  */
#line 678 "parser.y"
                 { (yyval.strval) = strdup(">"); }
#line 2353 "parser.tab.c"
    break;

  case 78: /* RELOP: LESSANDEQUAL  */
#line 679 "parser.y"
                 { (yyval.strval) = strdup("<="); }
#line 2359 "parser.tab.c"
    break;

  case 79: /* RELOP: MOREANDEQUAL  */
#line 680 "parser.y"
                 { (yyval.strval) = strdup(">="); }
#line 2365 "parser.tab.c"
    break;

  case 80: /* RELOP: EQUAL  */
#line 681 "parser.y"
                 { (yyval.strval) = strdup("=="); }
#line 2371 "parser.tab.c"
    break;

  case 81: /* RELOP: NOTEQUAL  */
#line 682 "parser.y"
                 { (yyval.strval) = strdup("!="); }
#line 2377 "parser.tab.c"
    break;

  case 82: /* AdditiveExpr: AdditiveExpr ARTHOP MultExpr  */
#line 686 "parser.y"
                                 {
        if (std::string((yyvsp[-2].attribute)->type) == "int" && std::string((yyvsp[0].attribute)->type) == "int") {
            (yyval.attribute) = new Attr();
            (yyval.attribute)->type = strdup("int");
            string temp = genTemp();
            Code[currentCodeLine++] = temp + " = " + string((yyvsp[-2].attribute)->place) + " " + string((yyvsp[-1].strval)) + " " + string((yyvsp[0].attribute)->place);
            (yyval.attribute)->place = strdup(temp.c_str());
        } else {
            yyerror("Operands of '+' or '-' must be int");
        }
    }
#line 2393 "parser.tab.c"
    break;

  case 83: /* AdditiveExpr: MultExpr  */
#line 697 "parser.y"
             { (yyval.attribute) = (yyvsp[0].attribute); }
#line 2399 "parser.tab.c"
    break;

  case 84: /* ARTHOP: PLUS  */
#line 701 "parser.y"
          { (yyval.strval) = strdup("+"); }
#line 2405 "parser.tab.c"
    break;

  case 85: /* ARTHOP: MINUS  */
#line 702 "parser.y"
          { (yyval.strval) = strdup("-"); }
#line 2411 "parser.tab.c"
    break;

  case 86: /* MultExpr: MultExpr MULOP UnaryExpr  */
#line 706 "parser.y"
                             {
        if (std::string((yyvsp[-2].attribute)->type) == "int" && std::string((yyvsp[0].attribute)->type) == "int") {
            (yyval.attribute) = new Attr();
            (yyval.attribute)->type = strdup("int");

            string temp = genTemp();
            string op = (yyvsp[-1].strval);  

            Code[currentCodeLine++] = temp + " = " + (yyvsp[-2].attribute)->place + " " + op + " " + (yyvsp[0].attribute)->place;

            (yyval.attribute)->place = strdup(temp.c_str());
        } else {
            yyerror("Operands of '*', '/', '%' must be int");
            (yyval.attribute) = new Attr();
            (yyval.attribute)->type = strdup("error");
            (yyval.attribute)->place = strdup("err");
        }
    }
#line 2434 "parser.tab.c"
    break;

  case 87: /* MultExpr: UnaryExpr  */
#line 724 "parser.y"
              {
        (yyval.attribute) = (yyvsp[0].attribute);
    }
#line 2442 "parser.tab.c"
    break;

  case 88: /* MULOP: DIV  */
#line 731 "parser.y"
        {(yyval.strval)=strdup("/");}
#line 2448 "parser.tab.c"
    break;

  case 89: /* MULOP: MUL  */
#line 732 "parser.y"
          {(yyval.strval)=strdup("*");}
#line 2454 "parser.tab.c"
    break;

  case 90: /* MULOP: MODULO  */
#line 733 "parser.y"
             {(yyval.strval)=strdup("%");}
#line 2460 "parser.tab.c"
    break;

  case 91: /* UnaryExpr: MINUS Factor  */
#line 737 "parser.y"
                 {
        if (std::string((yyvsp[0].attribute)->type) == "int"){
            (yyval.attribute) = new Attr();
            (yyval.attribute)->type = strdup("int");

            string temp = genTemp();
            Code[currentCodeLine++] = temp + " = -" + (yyvsp[0].attribute)->place;

            (yyval.attribute)->place = strdup(temp.c_str());
        }
        else
            yyerror("Unary minus only allowed on int");
    }
#line 2478 "parser.tab.c"
    break;

  case 92: /* UnaryExpr: Factor  */
#line 750 "parser.y"
           {
        (yyval.attribute) = (yyvsp[0].attribute);
    }
#line 2486 "parser.tab.c"
    break;

  case 93: /* Factor: INT_LITERAL  */
#line 757 "parser.y"
                {
        (yyval.attribute) = new Attr();
        (yyval.attribute)->type = strdup("int");
        (yyval.attribute)->place = strdup((yyvsp[0].strval));  // or genTemp() if it's constant folded into temp
    }
#line 2496 "parser.tab.c"
    break;

  case 94: /* Factor: STRINGLITERAL  */
#line 762 "parser.y"
                  {
        (yyval.attribute) = new Attr();
        (yyval.attribute)->type = strdup("string");
        (yyval.attribute)->place = strdup((yyvsp[0].strval));
    }
#line 2506 "parser.tab.c"
    break;

  case 95: /* Factor: CHARLITERAL  */
#line 767 "parser.y"
                {
        (yyval.attribute) = new Attr();
        (yyval.attribute)->type = strdup("char");
        (yyval.attribute)->place = strdup((yyvsp[0].strval));
    }
#line 2516 "parser.tab.c"
    break;

  case 96: /* Factor: TRUE  */
#line 772 "parser.y"
         {
        (yyval.attribute) = new Attr();
        (yyval.attribute)->type = strdup("bool");
        (yyval.attribute)->place = strdup("true");
    }
#line 2526 "parser.tab.c"
    break;

  case 97: /* Factor: FALSE  */
#line 777 "parser.y"
          {
        (yyval.attribute) = new Attr();
        (yyval.attribute)->type = strdup("bool");
        (yyval.attribute)->place = strdup("false");
    }
#line 2536 "parser.tab.c"
    break;

  case 98: /* Factor: FunctionCall  */
#line 782 "parser.y"
                 {(yyval.attribute)= (yyvsp[0].attribute);}
#line 2542 "parser.tab.c"
    break;

  case 99: /* Factor: ID  */
#line 783 "parser.y"
       {  
    char* var=currentTable->lookup((yyvsp[0].strval));
        if (!var) {
            char msg[128];
            sprintf(msg, "Undeclared variable: %s", (yyvsp[0].strval));
            yyerror(msg);
        }
        else{   
            (yyval.attribute) = new Attr(); 
            (yyval.attribute)->type = strdup(var);
            (yyval.attribute)->place = strdup((yyvsp[0].strval));  
        }
    }
#line 2560 "parser.tab.c"
    break;

  case 100: /* Factor: LBRACE Expression RBRACE  */
#line 796 "parser.y"
                             { (yyval.attribute) = (yyvsp[-1].attribute); }
#line 2566 "parser.tab.c"
    break;


#line 2570 "parser.tab.c"

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

#line 801 "parser.y"


    int main() {
        FILE *fp;
        char filename[50];
        cout<<"Enter the filename:"<<endl;
        cin>> filename;
        fp = fopen(filename,"r");
        yyin = fp;
        yyparse();
        saveTACToFile("tac.txt");
        return 0;
    }

    int yyerror(const char *s) {
        fprintf(stderr, "Parser Error: %s\n", s);
        //exit(1);
        return 0;
    }
