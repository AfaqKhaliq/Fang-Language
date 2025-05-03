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
  YYSYMBOL_66_8 = 66,                      /* @8  */
  YYSYMBOL_67_9 = 67,                      /* $@9  */
  YYSYMBOL_SELECTIONSTMT = 68,             /* SELECTIONSTMT  */
  YYSYMBOL_69_10 = 69,                     /* @10  */
  YYSYMBOL_70_11 = 70,                     /* $@11  */
  YYSYMBOL_71_12 = 71,                     /* @12  */
  YYSYMBOL_72_13 = 72,                     /* $@13  */
  YYSYMBOL_MATCHSTMT = 73,                 /* MATCHSTMT  */
  YYSYMBOL_74_14 = 74,                     /* $@14  */
  YYSYMBOL_midMarker = 75,                 /* midMarker  */
  YYSYMBOL_RETURNSTMT = 76,                /* RETURNSTMT  */
  YYSYMBOL_IOSTMT = 77,                    /* IOSTMT  */
  YYSYMBOL_PRINTSTMT = 78,                 /* PRINTSTMT  */
  YYSYMBOL_SCANESTMT = 79,                 /* SCANESTMT  */
  YYSYMBOL_80_15 = 80,                     /* $@15  */
  YYSYMBOL_EXPRSTMT = 81,                  /* EXPRSTMT  */
  YYSYMBOL_FunctionCall = 82,              /* FunctionCall  */
  YYSYMBOL_83_16 = 83,                     /* $@16  */
  YYSYMBOL_ARGUMENTS = 84,                 /* ARGUMENTS  */
  YYSYMBOL_ARGUMENTSLIST = 85,             /* ARGUMENTSLIST  */
  YYSYMBOL_Expression = 86,                /* Expression  */
  YYSYMBOL_AndExpr = 87,                   /* AndExpr  */
  YYSYMBOL_NotExpr = 88,                   /* NotExpr  */
  YYSYMBOL_RelationalExpr = 89,            /* RelationalExpr  */
  YYSYMBOL_RELOP = 90,                     /* RELOP  */
  YYSYMBOL_AdditiveExpr = 91,              /* AdditiveExpr  */
  YYSYMBOL_ARTHOP = 92,                    /* ARTHOP  */
  YYSYMBOL_MultExpr = 93,                  /* MultExpr  */
  YYSYMBOL_MULOP = 94,                     /* MULOP  */
  YYSYMBOL_UnaryExpr = 95,                 /* UnaryExpr  */
  YYSYMBOL_Factor = 96                     /* Factor  */
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
#define YYLAST   153

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  101
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
     421,   419,   442,   445,   450,   456,   442,   464,   465,   465,
     466,   470,   471,   472,   475,   480,   489,   503,   504,   508,
     514,   514,   525,   539,   539,   571,   572,   578,   595,   616,
     627,   631,   642,   646,   656,   660,   661,   677,   678,   679,
     680,   681,   682,   686,   697,   701,   702,   706,   724,   731,
     732,   733,   737,   750,   757,   762,   767,   772,   777,   782,
     783,   796
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
  "STMTLIST", "STATEMENT", "$@7", "ITERATIONSTMT", "@8", "$@9",
  "SELECTIONSTMT", "@10", "$@11", "@12", "$@13", "MATCHSTMT", "$@14",
  "midMarker", "RETURNSTMT", "IOSTMT", "PRINTSTMT", "SCANESTMT", "$@15",
  "EXPRSTMT", "FunctionCall", "$@16", "ARGUMENTS", "ARGUMENTSLIST",
  "Expression", "AndExpr", "NotExpr", "RelationalExpr", "RELOP",
  "AdditiveExpr", "ARTHOP", "MultExpr", "MULOP", "UnaryExpr", "Factor", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-99)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-64)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -99,     7,   101,   -99,   -19,   -99,   -99,   -99,   -99,   -99,
     -99,    22,   -99,    20,    33,    39,   -99,   -99,   113,    45,
     -99,   -99,    62,   -99,    79,   113,   -99,    81,   113,   -99,
     -99,    80,   113,   -99,   -99,    94,    83,    80,     2,   -99,
      45,    90,    92,   -99,   -99,    89,    99,   102,   103,   110,
      47,    45,   -99,   -99,   -99,   -99,   -99,   -99,   -99,   -99,
     112,   -99,    66,    66,   123,   -99,   -99,   114,   -99,   -99,
     -99,   -99,    66,    66,    23,   -99,   -99,   -99,    11,    95,
     -99,   -99,    -8,    54,   -99,   -99,   -99,    94,    24,    -9,
     -99,    66,    66,   115,    75,   -99,   -99,   -99,    66,    66,
     -99,   -99,   -99,   -99,   -99,   -99,   -99,   -99,    85,    85,
     -99,   -99,   -99,    85,   -99,   -99,   118,   116,    48,    58,
      66,   -99,    95,   -99,    37,    54,   -99,   -99,   120,   -99,
     -99,   119,   122,   108,   -99,   -99,   -99,   -99,    66,   -99,
       9,   -99,   108,    98,   124,   -99,    45,   -99,   -99,   -99,
     -99,    66,   -99,   -99,    59,   -99,   -99,   104,   -99,   -99
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       6,     0,     0,     1,    18,    19,    20,    21,    11,     2,
       5,     0,    12,     0,     0,     0,     7,     3,    14,     0,
      18,     8,    13,    15,     0,    24,     4,     0,     0,    17,
      25,    54,    24,     9,    16,     0,     0,    54,    33,    23,
       0,    27,     0,    22,    30,     0,     0,     0,     0,     0,
       0,     0,    36,    35,    37,    38,    57,    58,    32,    10,
       0,    26,     0,     0,     0,    42,    39,   100,    94,    95,
      96,    56,     0,     0,     0,    97,    98,    99,     0,    70,
      72,    74,    75,    84,    88,    93,    34,     0,     0,     0,
      60,     0,     0,     0,     0,    73,    92,    55,     0,     0,
      77,    78,    79,    80,    81,    82,    85,    86,     0,     0,
      90,    89,    91,     0,    29,    62,     0,     0,     0,     0,
      66,   101,    69,    71,    76,    83,    87,    59,     0,    43,
      40,     0,    65,    68,    61,    54,    54,    64,     0,    44,
      48,    41,    67,     0,     0,    51,     0,    52,    53,    47,
      45,     0,    49,    54,     0,    46,    54,     0,    54,    50
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -99,   -99,   -99,   -99,   -99,   -99,   -99,   -99,   -99,   -99,
     -99,   -99,   105,    -1,   -40,   107,   -99,   -99,    50,   -99,
     106,     4,   -99,     1,   -99,   -99,   -99,   -99,   -99,   -99,
     -99,   -98,   -99,   -29,     5,     6,   -99,   -99,   -99,     8,
     -99,   -99,   -99,   -99,   -59,    46,   -64,   -99,   -99,    41,
     -99,    38,   -99,    40,    76
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     9,    19,     2,    10,    18,    27,    40,    11,
      21,    22,    23,    24,    26,    31,    32,    35,    42,    60,
      36,    37,    51,    52,    92,   136,    53,    91,   135,   143,
     153,   139,   146,   140,    54,    55,    56,    57,   117,    58,
      77,    93,   131,   132,    78,    79,    80,    81,   108,    82,
     109,    83,   113,    84,    85
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      59,    12,    38,    88,    89,    45,   116,     3,    38,    95,
      98,    86,    45,    94,   100,   101,   102,   103,   104,   105,
     106,   107,    13,    97,    30,    14,    67,    68,    69,    70,
      98,    30,   118,   119,    15,   123,   115,    46,    47,    48,
      72,    49,    50,    98,    46,    47,   144,    16,    49,    50,
      67,    68,    69,    70,    17,   155,    75,    76,   157,    71,
     159,   133,    25,   129,    72,   106,   107,    98,    73,    67,
      68,    69,    70,   130,   156,    28,    74,    98,    98,   142,
      75,    76,    29,    72,   110,   111,   112,    73,    67,    68,
      69,    70,   154,   121,    98,    74,    33,    41,   -31,    75,
      76,    43,    72,   -28,    61,    62,   152,    38,     4,     5,
       6,     7,     8,    63,    74,    99,    64,    65,    75,    76,
      20,     5,     6,     7,    66,    87,    90,    98,   -63,   120,
     127,   128,   134,    34,   137,   138,   150,   114,   151,    39,
     141,   145,   158,    44,   122,   147,   148,   125,   149,   124,
      96,     0,     0,   126
};

static const yytype_int16 yycheck[] =
{
      40,     2,    31,    62,    63,     3,    15,     0,    37,    73,
      19,    51,     3,    72,    22,    23,    24,    25,    26,    27,
      28,    29,    41,    12,    25,     3,     3,     4,     5,     6,
      19,    32,    91,    92,    14,    99,    12,    35,    36,    37,
      17,    39,    40,    19,    35,    36,    37,    14,    39,    40,
       3,     4,     5,     6,    15,   153,    33,    34,   156,    12,
     158,   120,    17,    15,    17,    28,    29,    19,    21,     3,
       4,     5,     6,    15,    15,    13,    29,    19,    19,   138,
      33,    34,     3,    17,    30,    31,    32,    21,     3,     4,
       5,     6,   151,    18,    19,    29,    15,     3,    18,    33,
      34,    18,    17,    13,    12,    16,   146,   136,     7,     8,
       9,    10,    11,    14,    29,    20,    14,    14,    33,    34,
       7,     8,     9,    10,    14,    13,     3,    19,    14,    14,
      12,    15,    12,    28,    15,    13,    38,    87,    14,    32,
     136,   140,    38,    37,    98,   140,   140,   109,   140,   108,
      74,    -1,    -1,   113
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    43,    46,     0,     7,     8,     9,    10,    11,    44,
      47,    51,    55,    41,     3,    14,    14,    15,    48,    45,
       7,    52,    53,    54,    55,    17,    56,    49,    13,     3,
      55,    57,    58,    15,    54,    59,    62,    63,    75,    57,
      50,     3,    60,    18,    62,     3,    35,    36,    37,    39,
      40,    64,    65,    68,    76,    77,    78,    79,    81,    56,
      61,    12,    16,    14,    14,    14,    14,     3,     4,     5,
       6,    12,    17,    21,    29,    33,    34,    82,    86,    87,
      88,    89,    91,    93,    95,    96,    56,    13,    86,    86,
       3,    69,    66,    83,    86,    88,    96,    12,    19,    20,
      22,    23,    24,    25,    26,    27,    28,    29,    90,    92,
      30,    31,    32,    94,    60,    12,    15,    80,    86,    86,
      14,    18,    87,    88,    91,    93,    95,    12,    15,    15,
      15,    84,    85,    86,    12,    70,    67,    15,    13,    73,
      75,    63,    86,    71,    37,    65,    74,    76,    77,    81,
      38,    14,    56,    72,    86,    73,    15,    73,    38,    73
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    45,    44,    46,    46,    48,    49,    50,
      47,    51,    51,    52,    52,    53,    53,    54,    55,    55,
      55,    55,    56,    57,    57,    59,    58,    60,    61,    60,
      62,    62,    63,    64,    63,    63,    63,    63,    63,    66,
      67,    65,    69,    70,    71,    72,    68,    73,    74,    73,
      73,    73,    73,    73,    75,    76,    76,    77,    77,    78,
      80,    79,    81,    83,    82,    84,    84,    85,    85,    86,
      86,    87,    87,    88,    88,    89,    89,    90,    90,    90,
      90,    90,    90,    91,    91,    92,    92,    93,    93,    94,
      94,    94,    95,    95,    96,    96,    96,    96,    96,    96,
      96,    96
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     0,     6,     2,     0,     0,     0,     0,
       9,     1,     1,     1,     0,     1,     3,     2,     1,     1,
       1,     1,     4,     2,     0,     0,     4,     1,     0,     4,
       2,     0,     2,     0,     3,     2,     2,     2,     2,     0,
       0,     7,     0,     0,     0,     0,    11,     2,     0,     3,
       8,     2,     2,     2,     0,     3,     2,     1,     1,     5,
       0,     6,     4,     0,     5,     1,     0,     3,     1,     3,
       1,     3,     1,     2,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     3,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     3
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
#line 1801 "parser.tab.c"
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
#line 1813 "parser.tab.c"
    break;

  case 7: /* $@2: %empty  */
#line 321 "parser.y"
        {
            currentSignature.param_types.clear();
            currentSignature.param_id.clear();
        }
#line 1822 "parser.tab.c"
    break;

  case 8: /* $@3: %empty  */
#line 326 "parser.y"
        {
            currentTable->AddFunctionToTable((yyvsp[-3].strval),currentSignature,(yyvsp[-4].strval));
        }
#line 1830 "parser.tab.c"
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
#line 1842 "parser.tab.c"
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
#line 1854 "parser.tab.c"
    break;

  case 11: /* RETURNTYPE: VOID  */
#line 348 "parser.y"
                    {(yyval.strval)=strdup("void");}
#line 1860 "parser.tab.c"
    break;

  case 12: /* RETURNTYPE: BaseType  */
#line 349 "parser.y"
                   {(yyval.strval)=(yyvsp[0].strval);}
#line 1866 "parser.tab.c"
    break;

  case 17: /* PARAMETER: BaseType ID  */
#line 357 "parser.y"
                           {
        currentSignature.param_types.push_back((yyvsp[-1].strval));
        currentSignature.param_id.push_back((yyvsp[0].strval));
    }
#line 1875 "parser.tab.c"
    break;

  case 18: /* BaseType: INT  */
#line 363 "parser.y"
           { (yyval.strval) = strdup("int");  }
#line 1881 "parser.tab.c"
    break;

  case 19: /* BaseType: BOOL  */
#line 364 "parser.y"
           { (yyval.strval) = strdup("bool"); }
#line 1887 "parser.tab.c"
    break;

  case 20: /* BaseType: CHAR  */
#line 365 "parser.y"
           { (yyval.strval) = strdup("char"); }
#line 1893 "parser.tab.c"
    break;

  case 21: /* BaseType: STRING  */
#line 366 "parser.y"
           { (yyval.strval) = strdup("string"); }
#line 1899 "parser.tab.c"
    break;

  case 25: /* $@5: %empty  */
#line 381 "parser.y"
    {
        current_type = (yyvsp[0].strval);
    }
#line 1907 "parser.tab.c"
    break;

  case 27: /* IDLIST: ID  */
#line 389 "parser.y"
    {
        currentTable->AddId((yyvsp[0].strval), current_type);
        Code[currentCodeLine++] = "declare " + std::string((yyvsp[0].strval)) + " : " + current_type;
    }
#line 1916 "parser.tab.c"
    break;

  case 28: /* $@6: %empty  */
#line 394 "parser.y"
    {
        currentTable->AddId((yyvsp[0].strval), current_type);
        Code[currentCodeLine++] = "declare " + std::string((yyvsp[0].strval)) + " : " + current_type;
    }
#line 1925 "parser.tab.c"
    break;

  case 32: /* STATEMENT: midMarker EXPRSTMT  */
#line 409 "parser.y"
                             {(yyval.strval)=(yyvsp[-1].strval);}
#line 1931 "parser.tab.c"
    break;

  case 33: /* $@7: %empty  */
#line 410 "parser.y"
               {createScope();}
#line 1937 "parser.tab.c"
    break;

  case 34: /* STATEMENT: midMarker $@7 COMPOUNDSTMT  */
#line 410 "parser.y"
                                             {exitScope(); (yyval.strval)=(yyvsp[-2].strval);}
#line 1943 "parser.tab.c"
    break;

  case 35: /* STATEMENT: midMarker SELECTIONSTMT  */
#line 411 "parser.y"
                             {(yyval.strval)=(yyvsp[-1].strval);}
#line 1949 "parser.tab.c"
    break;

  case 36: /* STATEMENT: midMarker ITERATIONSTMT  */
#line 412 "parser.y"
                              {(yyval.strval)=(yyvsp[-1].strval);}
#line 1955 "parser.tab.c"
    break;

  case 37: /* STATEMENT: midMarker RETURNSTMT  */
#line 413 "parser.y"
                           {(yyval.strval)=(yyvsp[-1].strval);}
#line 1961 "parser.tab.c"
    break;

  case 38: /* STATEMENT: midMarker IOSTMT  */
#line 414 "parser.y"
                       {(yyval.strval)=(yyvsp[-1].strval);}
#line 1967 "parser.tab.c"
    break;

  case 39: /* @8: %empty  */
#line 419 "parser.y"
                 {(yyval.intval) = currentCodeLine; 
            // Save the line number where the condition starts
    }
#line 1975 "parser.tab.c"
    break;

  case 40: /* $@9: %empty  */
#line 421 "parser.y"
                        {
        if (std::string((yyvsp[-1].attribute)->type) != "bool") {
            yyerror("While condition must be bool");
        }

        
    }
#line 1987 "parser.tab.c"
    break;

  case 41: /* ITERATIONSTMT: WHILE LPAREN @8 Expression RPAREN $@9 STATEMENT  */
#line 428 "parser.y"
              {
        // Backpatch truelist of the condition to start of body
        backpatch((yyvsp[-3].attribute)->truelist, std::stoi((yyvsp[0].strval)));

        // Add jump back to condition after body
        Code[currentCodeLine++] = "goto " + std::to_string((yyvsp[-2].intval));

        // Mark falselist (loop exit) to next instruction
        backpatch((yyvsp[-3].attribute)->falselist, currentCodeLine); //next line
    }
#line 2002 "parser.tab.c"
    break;

  case 42: /* @10: %empty  */
#line 442 "parser.y"
             {
        (yyval.intval) = currentCodeLine; 
        // Save the line number where the condition starts
    }
#line 2011 "parser.tab.c"
    break;

  case 43: /* $@11: %empty  */
#line 445 "parser.y"
                        {
        if (std::string((yyvsp[-1].attribute)->type) != "bool") {
            yyerror("Condition must be bool");
        }
    }
#line 2021 "parser.tab.c"
    break;

  case 44: /* @12: %empty  */
#line 450 "parser.y"
              {
        int afterIf = currentCodeLine++;
        Code[afterIf] = "goto "; // Jump over ELSE
        (yyval.intval) = afterIf;
        backpatch((yyvsp[-3].attribute)->truelist, std::stoi((yyvsp[0].strval)));
    }
#line 2032 "parser.tab.c"
    break;

  case 45: /* $@13: %empty  */
#line 456 "parser.y"
         {
        backpatch((yyvsp[-5].attribute)->falselist, currentCodeLine);
    }
#line 2040 "parser.tab.c"
    break;

  case 46: /* SELECTIONSTMT: IF LPAREN @10 Expression RPAREN $@11 MATCHSTMT @12 ELSE $@13 MATCHSTMT  */
#line 459 "parser.y"
              {
        backpatch(MakeList((yyvsp[-3].intval)), currentCodeLine); // Fill jump over ELSE
    }
#line 2048 "parser.tab.c"
    break;

  case 47: /* MATCHSTMT: midMarker EXPRSTMT  */
#line 464 "parser.y"
                             {(yyval.strval)=(yyvsp[-1].strval);}
#line 2054 "parser.tab.c"
    break;

  case 48: /* $@14: %empty  */
#line 465 "parser.y"
               {createScope();}
#line 2060 "parser.tab.c"
    break;

  case 49: /* MATCHSTMT: midMarker $@14 COMPOUNDSTMT  */
#line 465 "parser.y"
                                             { exitScope(); (yyval.strval)=(yyvsp[-2].strval);}
#line 2066 "parser.tab.c"
    break;

  case 50: /* MATCHSTMT: midMarker IF LPAREN Expression RPAREN MATCHSTMT ELSE MATCHSTMT  */
#line 466 "parser.y"
                                                                    { 
    if (std::string((yyvsp[-4].attribute)->type) != "bool")
        yyerror("MUST GIVE BOOL EXPRESSION");
    }
#line 2075 "parser.tab.c"
    break;

  case 51: /* MATCHSTMT: midMarker ITERATIONSTMT  */
#line 470 "parser.y"
                               {(yyval.strval)=(yyvsp[-1].strval);}
#line 2081 "parser.tab.c"
    break;

  case 52: /* MATCHSTMT: midMarker RETURNSTMT  */
#line 471 "parser.y"
                            {(yyval.strval)=(yyvsp[-1].strval);}
#line 2087 "parser.tab.c"
    break;

  case 53: /* MATCHSTMT: midMarker IOSTMT  */
#line 472 "parser.y"
                       {(yyval.strval)=(yyvsp[-1].strval);}
#line 2093 "parser.tab.c"
    break;

  case 54: /* midMarker: %empty  */
#line 475 "parser.y"
          {(yyval.strval) = strdup(std::to_string(currentCodeLine).c_str());}
#line 2099 "parser.tab.c"
    break;

  case 55: /* RETURNSTMT: RETURN Expression SEMICOLON  */
#line 480 "parser.y"
                                {
        if (function_type != std::string((yyvsp[-1].attribute)->type)) {
            printf("Return error: expected %s, got %s\n", function_type.c_str(), (yyvsp[-1].attribute)->type);
            fflush(stdout);
            yyerror("Return type does not match function return type");
        }
        Code[currentCodeLine++] = "return " + std::string((yyvsp[-1].attribute)->place);
        has_return_statement = true;
    }
#line 2113 "parser.tab.c"
    break;

  case 56: /* RETURNSTMT: RETURN SEMICOLON  */
#line 489 "parser.y"
                     {
        if (function_type != "void") {
            printf("Return error: expected void, got empty return\n");
            fflush(stdout);
            yyerror("Non-void function must return a value");
        }
        Code[currentCodeLine++] = "return";  // For void return
        has_return_statement = true;
    }
#line 2127 "parser.tab.c"
    break;

  case 59: /* PRINTSTMT: PRINT LPAREN Expression RPAREN SEMICOLON  */
#line 508 "parser.y"
                                             {
        Code[currentCodeLine++] = "print " + std::string((yyvsp[-2].attribute)->place);
    }
#line 2135 "parser.tab.c"
    break;

  case 60: /* $@15: %empty  */
#line 514 "parser.y"
                   {
        if(!currentTable->IfExist((yyvsp[0].strval)))
        {
            yyerror("Identifier does not exist");
        } 
    }
#line 2146 "parser.tab.c"
    break;

  case 61: /* SCANESTMT: SCAN LPAREN ID $@15 RPAREN SEMICOLON  */
#line 519 "parser.y"
                       {
        Code[currentCodeLine++] = "scan " + std::string((yyvsp[-3].strval));
    }
#line 2154 "parser.tab.c"
    break;

  case 62: /* EXPRSTMT: ID ASSIGN Expression SEMICOLON  */
#line 525 "parser.y"
                                   {
        string declared_type = currentTable->lookup((yyvsp[-3].strval));
        if (declared_type != std::string((yyvsp[-1].attribute)->type)) {
            yyerror("Type mismatch in assignment");
        }

        Code[currentCodeLine++] = std::string((yyvsp[-3].strval)) + " = " + std::string((yyvsp[-1].attribute)->place);
    }
#line 2167 "parser.tab.c"
    break;

  case 63: /* $@16: %empty  */
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
#line 2182 "parser.tab.c"
    break;

  case 64: /* FunctionCall: ID $@16 LPAREN ARGUMENTS RPAREN  */
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
#line 2203 "parser.tab.c"
    break;

  case 65: /* ARGUMENTS: ARGUMENTSLIST  */
#line 571 "parser.y"
                  { }
#line 2209 "parser.tab.c"
    break;

  case 66: /* ARGUMENTS: %empty  */
#line 572 "parser.y"
                  { }
#line 2215 "parser.tab.c"
    break;

  case 67: /* ARGUMENTSLIST: ARGUMENTSLIST COMMA Expression  */
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
#line 2237 "parser.tab.c"
    break;

  case 68: /* ARGUMENTSLIST: Expression  */
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
#line 2259 "parser.tab.c"
    break;

  case 69: /* Expression: Expression OR AndExpr  */
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
#line 2275 "parser.tab.c"
    break;

  case 70: /* Expression: AndExpr  */
#line 627 "parser.y"
            { (yyval.attribute) = (yyvsp[0].attribute); }
#line 2281 "parser.tab.c"
    break;

  case 71: /* AndExpr: AndExpr AND NotExpr  */
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
#line 2297 "parser.tab.c"
    break;

  case 72: /* AndExpr: NotExpr  */
#line 642 "parser.y"
            { (yyval.attribute) = (yyvsp[0].attribute); }
#line 2303 "parser.tab.c"
    break;

  case 73: /* NotExpr: NOT NotExpr  */
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
#line 2318 "parser.tab.c"
    break;

  case 74: /* NotExpr: RelationalExpr  */
#line 656 "parser.y"
                   { (yyval.attribute) = (yyvsp[0].attribute); }
#line 2324 "parser.tab.c"
    break;

  case 75: /* RelationalExpr: AdditiveExpr  */
#line 660 "parser.y"
                 { (yyval.attribute) = (yyvsp[0].attribute); }
#line 2330 "parser.tab.c"
    break;

  case 76: /* RelationalExpr: AdditiveExpr RELOP AdditiveExpr  */
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
#line 2348 "parser.tab.c"
    break;

  case 77: /* RELOP: LESSTHAN  */
#line 677 "parser.y"
                 { (yyval.strval) = strdup("<"); }
#line 2354 "parser.tab.c"
    break;

  case 78: /* RELOP: MORETHAN  */
#line 678 "parser.y"
                 { (yyval.strval) = strdup(">"); }
#line 2360 "parser.tab.c"
    break;

  case 79: /* RELOP: LESSANDEQUAL  */
#line 679 "parser.y"
                 { (yyval.strval) = strdup("<="); }
#line 2366 "parser.tab.c"
    break;

  case 80: /* RELOP: MOREANDEQUAL  */
#line 680 "parser.y"
                 { (yyval.strval) = strdup(">="); }
#line 2372 "parser.tab.c"
    break;

  case 81: /* RELOP: EQUAL  */
#line 681 "parser.y"
                 { (yyval.strval) = strdup("=="); }
#line 2378 "parser.tab.c"
    break;

  case 82: /* RELOP: NOTEQUAL  */
#line 682 "parser.y"
                 { (yyval.strval) = strdup("!="); }
#line 2384 "parser.tab.c"
    break;

  case 83: /* AdditiveExpr: AdditiveExpr ARTHOP MultExpr  */
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
#line 2400 "parser.tab.c"
    break;

  case 84: /* AdditiveExpr: MultExpr  */
#line 697 "parser.y"
             { (yyval.attribute) = (yyvsp[0].attribute); }
#line 2406 "parser.tab.c"
    break;

  case 85: /* ARTHOP: PLUS  */
#line 701 "parser.y"
          { (yyval.strval) = strdup("+"); }
#line 2412 "parser.tab.c"
    break;

  case 86: /* ARTHOP: MINUS  */
#line 702 "parser.y"
          { (yyval.strval) = strdup("-"); }
#line 2418 "parser.tab.c"
    break;

  case 87: /* MultExpr: MultExpr MULOP UnaryExpr  */
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
#line 2441 "parser.tab.c"
    break;

  case 88: /* MultExpr: UnaryExpr  */
#line 724 "parser.y"
              {
        (yyval.attribute) = (yyvsp[0].attribute);
    }
#line 2449 "parser.tab.c"
    break;

  case 89: /* MULOP: DIV  */
#line 731 "parser.y"
        {(yyval.strval)=strdup("/");}
#line 2455 "parser.tab.c"
    break;

  case 90: /* MULOP: MUL  */
#line 732 "parser.y"
          {(yyval.strval)=strdup("*");}
#line 2461 "parser.tab.c"
    break;

  case 91: /* MULOP: MODULO  */
#line 733 "parser.y"
             {(yyval.strval)=strdup("%");}
#line 2467 "parser.tab.c"
    break;

  case 92: /* UnaryExpr: MINUS Factor  */
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
#line 2485 "parser.tab.c"
    break;

  case 93: /* UnaryExpr: Factor  */
#line 750 "parser.y"
           {
        (yyval.attribute) = (yyvsp[0].attribute);
    }
#line 2493 "parser.tab.c"
    break;

  case 94: /* Factor: INT_LITERAL  */
#line 757 "parser.y"
                {
        (yyval.attribute) = new Attr();
        (yyval.attribute)->type = strdup("int");
        (yyval.attribute)->place = strdup((yyvsp[0].strval));  // or genTemp() if it's constant folded into temp
    }
#line 2503 "parser.tab.c"
    break;

  case 95: /* Factor: STRINGLITERAL  */
#line 762 "parser.y"
                  {
        (yyval.attribute) = new Attr();
        (yyval.attribute)->type = strdup("string");
        (yyval.attribute)->place = strdup((yyvsp[0].strval));
    }
#line 2513 "parser.tab.c"
    break;

  case 96: /* Factor: CHARLITERAL  */
#line 767 "parser.y"
                {
        (yyval.attribute) = new Attr();
        (yyval.attribute)->type = strdup("char");
        (yyval.attribute)->place = strdup((yyvsp[0].strval));
    }
#line 2523 "parser.tab.c"
    break;

  case 97: /* Factor: TRUE  */
#line 772 "parser.y"
         {
        (yyval.attribute) = new Attr();
        (yyval.attribute)->type = strdup("bool");
        (yyval.attribute)->place = strdup("true");
    }
#line 2533 "parser.tab.c"
    break;

  case 98: /* Factor: FALSE  */
#line 777 "parser.y"
          {
        (yyval.attribute) = new Attr();
        (yyval.attribute)->type = strdup("bool");
        (yyval.attribute)->place = strdup("false");
    }
#line 2543 "parser.tab.c"
    break;

  case 99: /* Factor: FunctionCall  */
#line 782 "parser.y"
                 {(yyval.attribute)= (yyvsp[0].attribute);}
#line 2549 "parser.tab.c"
    break;

  case 100: /* Factor: ID  */
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
#line 2567 "parser.tab.c"
    break;

  case 101: /* Factor: LBRACE Expression RBRACE  */
#line 796 "parser.y"
                             { (yyval.attribute) = (yyvsp[-1].attribute); }
#line 2573 "parser.tab.c"
    break;


#line 2577 "parser.tab.c"

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
