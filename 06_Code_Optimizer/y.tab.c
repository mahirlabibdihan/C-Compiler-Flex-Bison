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
#line 1 "1905072_parser.y"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <string>
#include "1905072_SymbolInfo.h"
#include "1905072_SymbolTable.h"
#include "1905072_ScopeTable.h"
#include "1905072_Logger.h"
#include "1905072_Error_Handler.h"
#include "1905072_Semantic_Analyzer.h"
#include "1905072_Helper.h"
#include "1905072_Assembly_Generator.h"
#include "1905072_Token.h"
#include "1905072_Expression.h"
using namespace std;

extern ofstream logout;
extern ofstream errout;
extern ofstream tokenout;
extern ofstream codeout;

int yylex(void);
extern int line_count;
extern int error_count;
extern SymbolTable *table;
extern AssemblyGenerator* asm_gen;
extern SemanticAnalyzer* sem_anlz;
bool in_function = false;
vector<Variable*> params;
vector<Variable*> vars;
vector<string> args;
unsigned long sdbmHash(string str);
extern vector<string> data_segment;
void yyerror(string s){
	logout<<"Error at line "<<line_count<<": "<<s<<"\n"<<endl;
	errout<<"Error at line "<<line_count<<": "<<s<<"\n"<<endl;
    error_count++;
}

void erm_s(SymbolInfo* s) // erase memory of SymbolInfo pointer
{
    if(s!=NULL) delete s;
}

void erm_se(Segment* s) // erase memory of SymbolInfo pointer
{
    if(s!=NULL) delete s;
}

void erm_e(Expression* s) // erase memory of SymbolInfo pointer
{
    if(s!=NULL) delete s;
}

void erm_v(Variable* s) // erase memory of SymbolInfo pointer
{
    if(s!=NULL) delete s;
}

void freeMemory(vector<SymbolInfo*> symbols)
{
	for(auto &i: symbols)
	{
		erm_s(i);
	}
}

void freeMemory(vector<Segment*> symbols)
{
	for(auto &i: symbols)
	{
		erm_se(i);
	}
}

void freeMemory(vector<Variable*> symbols)
{
	for(auto &i: symbols)
	{
		erm_v(i);
	}
}

void freeArrayMemory(vector<Variable*> &symbols)
{
	freeMemory(symbols);
	symbols.clear();
}


#line 165 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IF = 258,                      /* IF  */
    ELSE = 259,                    /* ELSE  */
    LOWER_THAN_ELSE = 260,         /* LOWER_THAN_ELSE  */
    SWITCH = 261,                  /* SWITCH  */
    CASE = 262,                    /* CASE  */
    DEFAULT = 263,                 /* DEFAULT  */
    FOR = 264,                     /* FOR  */
    DO = 265,                      /* DO  */
    WHILE = 266,                   /* WHILE  */
    INT = 267,                     /* INT  */
    FLOAT = 268,                   /* FLOAT  */
    DOUBLE = 269,                  /* DOUBLE  */
    CHAR = 270,                    /* CHAR  */
    STRING = 271,                  /* STRING  */
    VOID = 272,                    /* VOID  */
    BREAK = 273,                   /* BREAK  */
    RETURN = 274,                  /* RETURN  */
    CONTINUE = 275,                /* CONTINUE  */
    INCOP = 276,                   /* INCOP  */
    DECOP = 277,                   /* DECOP  */
    ASSIGNOP = 278,                /* ASSIGNOP  */
    NOT = 279,                     /* NOT  */
    PRINTLN = 280,                 /* PRINTLN  */
    LPAREN = 281,                  /* LPAREN  */
    RPAREN = 282,                  /* RPAREN  */
    LCURL = 283,                   /* LCURL  */
    RCURL = 284,                   /* RCURL  */
    LTHIRD = 285,                  /* LTHIRD  */
    RTHIRD = 286,                  /* RTHIRD  */
    COMMA = 287,                   /* COMMA  */
    SEMICOLON = 288,               /* SEMICOLON  */
    ID = 289,                      /* ID  */
    CONST_INT = 290,               /* CONST_INT  */
    CONST_FLOAT = 291,             /* CONST_FLOAT  */
    CONST_CHAR = 292,              /* CONST_CHAR  */
    ADDOP = 293,                   /* ADDOP  */
    MULOP = 294,                   /* MULOP  */
    LOGICOP = 295,                 /* LOGICOP  */
    RELOP = 296                    /* RELOP  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define IF 258
#define ELSE 259
#define LOWER_THAN_ELSE 260
#define SWITCH 261
#define CASE 262
#define DEFAULT 263
#define FOR 264
#define DO 265
#define WHILE 266
#define INT 267
#define FLOAT 268
#define DOUBLE 269
#define CHAR 270
#define STRING 271
#define VOID 272
#define BREAK 273
#define RETURN 274
#define CONTINUE 275
#define INCOP 276
#define DECOP 277
#define ASSIGNOP 278
#define NOT 279
#define PRINTLN 280
#define LPAREN 281
#define RPAREN 282
#define LCURL 283
#define RCURL 284
#define LTHIRD 285
#define RTHIRD 286
#define COMMA 287
#define SEMICOLON 288
#define ID 289
#define CONST_INT 290
#define CONST_FLOAT 291
#define CONST_CHAR 292
#define ADDOP 293
#define MULOP 294
#define LOGICOP 295
#define RELOP 296

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 97 "1905072_parser.y"

	Segment* segment;
	Expression* expression;

#line 305 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IF = 3,                         /* IF  */
  YYSYMBOL_ELSE = 4,                       /* ELSE  */
  YYSYMBOL_LOWER_THAN_ELSE = 5,            /* LOWER_THAN_ELSE  */
  YYSYMBOL_SWITCH = 6,                     /* SWITCH  */
  YYSYMBOL_CASE = 7,                       /* CASE  */
  YYSYMBOL_DEFAULT = 8,                    /* DEFAULT  */
  YYSYMBOL_FOR = 9,                        /* FOR  */
  YYSYMBOL_DO = 10,                        /* DO  */
  YYSYMBOL_WHILE = 11,                     /* WHILE  */
  YYSYMBOL_INT = 12,                       /* INT  */
  YYSYMBOL_FLOAT = 13,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 14,                    /* DOUBLE  */
  YYSYMBOL_CHAR = 15,                      /* CHAR  */
  YYSYMBOL_STRING = 16,                    /* STRING  */
  YYSYMBOL_VOID = 17,                      /* VOID  */
  YYSYMBOL_BREAK = 18,                     /* BREAK  */
  YYSYMBOL_RETURN = 19,                    /* RETURN  */
  YYSYMBOL_CONTINUE = 20,                  /* CONTINUE  */
  YYSYMBOL_INCOP = 21,                     /* INCOP  */
  YYSYMBOL_DECOP = 22,                     /* DECOP  */
  YYSYMBOL_ASSIGNOP = 23,                  /* ASSIGNOP  */
  YYSYMBOL_NOT = 24,                       /* NOT  */
  YYSYMBOL_PRINTLN = 25,                   /* PRINTLN  */
  YYSYMBOL_LPAREN = 26,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 27,                    /* RPAREN  */
  YYSYMBOL_LCURL = 28,                     /* LCURL  */
  YYSYMBOL_RCURL = 29,                     /* RCURL  */
  YYSYMBOL_LTHIRD = 30,                    /* LTHIRD  */
  YYSYMBOL_RTHIRD = 31,                    /* RTHIRD  */
  YYSYMBOL_COMMA = 32,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 33,                 /* SEMICOLON  */
  YYSYMBOL_ID = 34,                        /* ID  */
  YYSYMBOL_CONST_INT = 35,                 /* CONST_INT  */
  YYSYMBOL_CONST_FLOAT = 36,               /* CONST_FLOAT  */
  YYSYMBOL_CONST_CHAR = 37,                /* CONST_CHAR  */
  YYSYMBOL_ADDOP = 38,                     /* ADDOP  */
  YYSYMBOL_MULOP = 39,                     /* MULOP  */
  YYSYMBOL_LOGICOP = 40,                   /* LOGICOP  */
  YYSYMBOL_RELOP = 41,                     /* RELOP  */
  YYSYMBOL_YYACCEPT = 42,                  /* $accept  */
  YYSYMBOL_start = 43,                     /* start  */
  YYSYMBOL_program = 44,                   /* program  */
  YYSYMBOL_unit = 45,                      /* unit  */
  YYSYMBOL_func_declaration = 46,          /* func_declaration  */
  YYSYMBOL_func_definition = 47,           /* func_definition  */
  YYSYMBOL_48_1 = 48,                      /* $@1  */
  YYSYMBOL_49_2 = 49,                      /* $@2  */
  YYSYMBOL_50_3 = 50,                      /* $@3  */
  YYSYMBOL_51_4 = 51,                      /* $@4  */
  YYSYMBOL_parameter_list = 52,            /* parameter_list  */
  YYSYMBOL_compound_statement = 53,        /* compound_statement  */
  YYSYMBOL_create_scope = 54,              /* create_scope  */
  YYSYMBOL_var_declaration = 55,           /* var_declaration  */
  YYSYMBOL_type_specifier = 56,            /* type_specifier  */
  YYSYMBOL_declaration_list = 57,          /* declaration_list  */
  YYSYMBOL_statements = 58,                /* statements  */
  YYSYMBOL_statement = 59,                 /* statement  */
  YYSYMBOL_60_5 = 60,                      /* $@5  */
  YYSYMBOL_61_6 = 61,                      /* $@6  */
  YYSYMBOL_62_7 = 62,                      /* $@7  */
  YYSYMBOL_63_8 = 63,                      /* $@8  */
  YYSYMBOL_64_9 = 64,                      /* $@9  */
  YYSYMBOL_65_10 = 65,                     /* $@10  */
  YYSYMBOL_create_if_block = 66,           /* create_if_block  */
  YYSYMBOL_expression_statement = 67,      /* expression_statement  */
  YYSYMBOL_variable = 68,                  /* variable  */
  YYSYMBOL_expression = 69,                /* expression  */
  YYSYMBOL_logic_expression = 70,          /* logic_expression  */
  YYSYMBOL_rel_expression = 71,            /* rel_expression  */
  YYSYMBOL_simple_expression = 72,         /* simple_expression  */
  YYSYMBOL_term = 73,                      /* term  */
  YYSYMBOL_unary_expression = 74,          /* unary_expression  */
  YYSYMBOL_factor = 75,                    /* factor  */
  YYSYMBOL_argument_list = 76,             /* argument_list  */
  YYSYMBOL_arguments = 77,                 /* arguments  */
  YYSYMBOL_constant = 78                   /* constant  */
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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   327

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  98
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  163

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
       0,   117,   117,   127,   133,   141,   147,   153,   161,   169,
     177,   185,   193,   201,   209,   217,   228,   227,   241,   240,
     253,   252,   266,   265,   279,   286,   293,   300,   307,   314,
     323,   331,   339,   347,   355,   366,   388,   396,   406,   412,
     418,   426,   437,   448,   466,   484,   495,   515,   521,   527,
     535,   541,   547,   553,   559,   566,   568,   570,   565,   578,
     587,   586,   595,   596,   595,   603,   618,   625,   635,   640,
     646,   655,   664,   675,   682,   702,   709,   718,   725,   734,
     741,   750,   757,   766,   774,   782,   791,   800,   808,   815,
     824,   833,   843,   854,   861,   868,   875,   886,   894
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
  "\"end of file\"", "error", "\"invalid token\"", "IF", "ELSE",
  "LOWER_THAN_ELSE", "SWITCH", "CASE", "DEFAULT", "FOR", "DO", "WHILE",
  "INT", "FLOAT", "DOUBLE", "CHAR", "STRING", "VOID", "BREAK", "RETURN",
  "CONTINUE", "INCOP", "DECOP", "ASSIGNOP", "NOT", "PRINTLN", "LPAREN",
  "RPAREN", "LCURL", "RCURL", "LTHIRD", "RTHIRD", "COMMA", "SEMICOLON",
  "ID", "CONST_INT", "CONST_FLOAT", "CONST_CHAR", "ADDOP", "MULOP",
  "LOGICOP", "RELOP", "$accept", "start", "program", "unit",
  "func_declaration", "func_definition", "$@1", "$@2", "$@3", "$@4",
  "parameter_list", "compound_statement", "create_scope",
  "var_declaration", "type_specifier", "declaration_list", "statements",
  "statement", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10",
  "create_if_block", "expression_statement", "variable", "expression",
  "logic_expression", "rel_expression", "simple_expression", "term",
  "unary_expression", "factor", "argument_list", "arguments", "constant", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-107)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-21)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      53,  -107,  -107,  -107,     7,    53,  -107,  -107,  -107,  -107,
     -17,  -107,  -107,    41,     4,   107,    37,    42,    -7,  -107,
       8,     5,    22,    28,  -107,  -107,    19,    60,  -107,    34,
      63,  -107,  -107,    72,   -19,    13,    53,  -107,  -107,    71,
      37,    78,    72,  -107,  -107,    14,    53,  -107,  -107,    72,
      75,    37,    74,  -107,  -107,   114,  -107,  -107,    72,    76,
    -107,  -107,    87,  -107,   214,    95,    96,  -107,   276,   120,
     102,   120,  -107,  -107,    62,  -107,  -107,   120,  -107,  -107,
    -107,  -107,   150,  -107,  -107,    30,    97,  -107,    89,   -13,
      93,  -107,  -107,  -107,  -107,  -107,  -107,   186,   120,   289,
     109,  -107,   103,    77,  -107,   111,   110,   120,   120,  -107,
     242,  -107,  -107,  -107,  -107,   120,  -107,   120,   120,   120,
     120,   270,  -107,   130,  -107,   120,  -107,   133,  -107,  -107,
     137,   134,   139,  -107,  -107,  -107,  -107,    93,   127,  -107,
    -107,   289,  -107,   108,  -107,   120,  -107,   270,  -107,   141,
    -107,  -107,   167,   120,   270,  -107,  -107,  -107,   270,   145,
    -107,   270,  -107
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    38,    39,    40,     0,     2,     4,     6,     7,     5,
       0,     1,     3,    45,     0,     0,     0,     0,     0,    36,
       0,     0,     0,    29,    97,    98,     0,     0,    37,    41,
      22,    13,    12,     0,     0,     0,     0,    28,    46,    42,
       0,     0,     0,    35,    21,     0,     0,     9,     8,     0,
      26,     0,     0,    15,    23,     0,    11,    10,     0,    27,
      17,    24,     0,    43,     0,     0,     0,    62,     0,     0,
       0,     0,    33,    69,    71,    89,    90,     0,    52,    51,
      54,    50,     0,    47,    53,    86,     0,    73,    75,    77,
      79,    81,    85,    19,    25,    44,    34,     0,     0,     0,
       0,    67,     0,    86,    84,     0,     0,    94,     0,    83,
       0,    30,    48,    91,    92,     0,    70,     0,     0,     0,
       0,     0,    32,     0,    55,     0,    66,     0,    88,    96,
       0,    93,     0,    31,    49,    74,    76,    80,    78,    82,
      68,     0,    63,     0,    87,     0,    72,     0,    56,     0,
      65,    95,    59,     0,     0,    60,    57,    64,     0,     0,
      61,     0,    58
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -107,  -107,  -107,   168,    16,    26,  -107,  -107,  -107,  -107,
    -107,    35,  -107,    29,     9,  -107,   113,   -78,  -107,  -107,
    -107,  -107,  -107,  -107,  -107,   -97,   -59,   -68,  -106,    64,
      61,    73,   -57,  -107,  -107,  -107,   -29
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     4,     5,     6,    78,    79,    49,    58,    33,    42,
      22,    80,    55,    81,    10,    14,    82,    83,   141,   153,
     159,   158,   100,   149,   147,    84,    85,    86,    87,    88,
      89,    90,    91,    92,   130,   131,    26
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     102,   129,   124,   106,   112,    17,    31,    11,    45,   135,
     103,    52,   104,    46,    47,    56,     7,    13,   103,   112,
     109,     7,    62,    34,    23,   118,     8,    29,   119,     9,
     123,     8,   134,   -20,     9,    30,    18,    19,    32,   151,
     132,   -16,   -18,   134,   148,    50,    48,    57,   103,    35,
      38,   113,   114,   115,    36,    59,   103,   142,   103,   103,
     103,   103,    37,   139,    40,     1,     2,    15,    44,   152,
       3,    16,    24,    25,    27,    28,   157,    54,   -14,    53,
     160,   -14,   -14,   162,    60,   156,   103,   -14,   107,   -14,
     -14,   -14,   108,    93,    39,   -14,    41,   -14,   113,   114,
      43,    51,   -14,   -14,   -14,    63,   -14,   -14,    20,    61,
      94,   -14,   -14,   -14,   -14,    64,   -14,    65,    95,     1,
       2,    98,    99,    66,     3,    67,     1,     2,   105,   117,
     116,     3,   120,    68,    21,   125,   126,   128,    69,    70,
      71,   150,    43,    72,    69,   127,    71,    73,    74,    75,
      76,   110,    77,    65,    74,    75,    76,   140,    77,    66,
     143,    67,     1,     2,   144,   118,   145,     3,   154,    68,
     146,   155,   161,    12,    69,    70,    71,    97,    43,   111,
     138,   136,     0,    73,    74,    75,    76,   121,    77,    65,
       0,   137,     0,     0,     0,    66,     0,    67,     1,     2,
       0,     0,     0,     3,     0,    68,     0,     0,     0,     0,
      69,    70,    71,     0,    43,   122,     0,    65,     0,    73,
      74,    75,    76,    66,    77,    67,     1,     2,     0,     0,
       0,     3,     0,    68,     0,     0,     0,     0,    69,    70,
      71,     0,    43,    96,     0,    65,     0,    73,    74,    75,
      76,    66,    77,    67,     1,     2,     0,     0,     0,     3,
       0,    68,     0,     0,     0,     0,    69,    70,    71,     0,
      43,   133,     0,    65,     0,    73,    74,    75,    76,    66,
      77,    67,     1,     2,     0,     0,     0,     3,     0,    68,
       0,     0,     0,     0,    69,    70,    71,     0,    43,     0,
      69,     0,    71,    73,    74,    75,    76,     0,    77,   101,
      74,    75,    76,    69,    77,    71,     0,     0,     0,     0,
       0,     0,    73,    74,    75,    76,     0,    77
};

static const yytype_int16 yycheck[] =
{
      68,   107,    99,    71,    82,     1,     1,     0,    27,   115,
      69,    40,    69,    32,     1,     1,     0,    34,    77,    97,
      77,     5,    51,     1,    15,    38,     0,    34,    41,     0,
      98,     5,   110,    28,     5,    27,    32,    33,    33,   145,
     108,    28,    28,   121,   141,    36,    33,    33,   107,    27,
      31,    21,    22,    23,    32,    46,   115,   125,   117,   118,
     119,   120,    34,   120,    30,    12,    13,    26,    33,   147,
      17,    30,    35,    36,    32,    33,   154,    42,     0,     1,
     158,     3,     4,   161,    49,   153,   145,     9,    26,    11,
      12,    13,    30,    58,    34,    17,    33,    19,    21,    22,
      28,    30,    24,    25,    26,    31,    28,    29,     1,    34,
      34,    33,    34,    35,    36,     1,    38,     3,    31,    12,
      13,    26,    26,     9,    17,    11,    12,    13,    26,    40,
      33,    17,    39,    19,    27,    26,    33,    27,    24,    25,
      26,    33,    28,    29,    24,    34,    26,    33,    34,    35,
      36,     1,    38,     3,    34,    35,    36,    27,    38,     9,
      27,    11,    12,    13,    27,    38,    32,    17,    27,    19,
      31,     4,    27,     5,    24,    25,    26,    64,    28,    29,
     119,   117,    -1,    33,    34,    35,    36,     1,    38,     3,
      -1,   118,    -1,    -1,    -1,     9,    -1,    11,    12,    13,
      -1,    -1,    -1,    17,    -1,    19,    -1,    -1,    -1,    -1,
      24,    25,    26,    -1,    28,    29,    -1,     3,    -1,    33,
      34,    35,    36,     9,    38,    11,    12,    13,    -1,    -1,
      -1,    17,    -1,    19,    -1,    -1,    -1,    -1,    24,    25,
      26,    -1,    28,    29,    -1,     3,    -1,    33,    34,    35,
      36,     9,    38,    11,    12,    13,    -1,    -1,    -1,    17,
      -1,    19,    -1,    -1,    -1,    -1,    24,    25,    26,    -1,
      28,    29,    -1,     3,    -1,    33,    34,    35,    36,     9,
      38,    11,    12,    13,    -1,    -1,    -1,    17,    -1,    19,
      -1,    -1,    -1,    -1,    24,    25,    26,    -1,    28,    -1,
      24,    -1,    26,    33,    34,    35,    36,    -1,    38,    33,
      34,    35,    36,    24,    38,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    34,    35,    36,    -1,    38
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    12,    13,    17,    43,    44,    45,    46,    47,    55,
      56,     0,    45,    34,    57,    26,    30,     1,    32,    33,
       1,    27,    52,    56,    35,    36,    78,    32,    33,    34,
      27,     1,    33,    50,     1,    27,    32,    34,    31,    34,
      30,    33,    51,    28,    53,    27,    32,     1,    33,    48,
      56,    30,    78,     1,    53,    54,     1,    33,    49,    56,
      53,    34,    78,    31,     1,     3,     9,    11,    19,    24,
      25,    26,    29,    33,    34,    35,    36,    38,    46,    47,
      53,    55,    58,    59,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    53,    34,    31,    29,    58,    26,    26,
      64,    33,    69,    68,    74,    26,    69,    26,    30,    74,
       1,    29,    59,    21,    22,    23,    33,    40,    38,    41,
      39,     1,    29,    69,    67,    26,    33,    34,    27,    70,
      76,    77,    69,    29,    59,    70,    71,    73,    72,    74,
      27,    60,    69,    27,    27,    32,    31,    66,    67,    65,
      33,    70,    59,    61,    27,     4,    69,    59,    63,    62,
      59,    27,    59
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    45,    45,    46,    46,
      46,    46,    46,    46,    46,    46,    48,    47,    49,    47,
      50,    47,    51,    47,    52,    52,    52,    52,    52,    52,
      53,    53,    53,    53,    53,    54,    55,    55,    56,    56,
      56,    57,    57,    57,    57,    57,    57,    58,    58,    58,
      59,    59,    59,    59,    59,    60,    61,    62,    59,    59,
      63,    59,    64,    65,    59,    59,    59,    59,    66,    67,
      67,    68,    68,    69,    69,    70,    70,    71,    71,    72,
      72,    73,    73,    74,    74,    74,    75,    75,    75,    75,
      75,    75,    75,    76,    76,    77,    77,    78,    78
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     6,
       7,     7,     5,     5,     6,     7,     0,     7,     0,     8,
       0,     6,     0,     7,     4,     5,     3,     4,     2,     1,
       4,     5,     5,     3,     4,     0,     3,     4,     1,     1,
       1,     3,     4,     6,     7,     1,     4,     1,     2,     3,
       1,     1,     1,     1,     1,     0,     0,     0,    10,     6,
       0,     9,     0,     0,     7,     5,     3,     2,     0,     1,
       2,     1,     4,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     2,     2,     1,     1,     4,     3,     1,
       1,     2,     2,     1,     0,     3,     1,     1,     1
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
  switch (yykind)
    {
    case YYSYMBOL_IF: /* IF  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1516 "y.tab.c"
        break;

    case YYSYMBOL_ELSE: /* ELSE  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1522 "y.tab.c"
        break;

    case YYSYMBOL_LOWER_THAN_ELSE: /* LOWER_THAN_ELSE  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1528 "y.tab.c"
        break;

    case YYSYMBOL_SWITCH: /* SWITCH  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1534 "y.tab.c"
        break;

    case YYSYMBOL_CASE: /* CASE  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1540 "y.tab.c"
        break;

    case YYSYMBOL_DEFAULT: /* DEFAULT  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1546 "y.tab.c"
        break;

    case YYSYMBOL_FOR: /* FOR  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1552 "y.tab.c"
        break;

    case YYSYMBOL_DO: /* DO  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1558 "y.tab.c"
        break;

    case YYSYMBOL_WHILE: /* WHILE  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1564 "y.tab.c"
        break;

    case YYSYMBOL_INT: /* INT  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1570 "y.tab.c"
        break;

    case YYSYMBOL_FLOAT: /* FLOAT  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1576 "y.tab.c"
        break;

    case YYSYMBOL_DOUBLE: /* DOUBLE  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1582 "y.tab.c"
        break;

    case YYSYMBOL_CHAR: /* CHAR  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1588 "y.tab.c"
        break;

    case YYSYMBOL_STRING: /* STRING  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1594 "y.tab.c"
        break;

    case YYSYMBOL_VOID: /* VOID  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1600 "y.tab.c"
        break;

    case YYSYMBOL_BREAK: /* BREAK  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1606 "y.tab.c"
        break;

    case YYSYMBOL_RETURN: /* RETURN  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1612 "y.tab.c"
        break;

    case YYSYMBOL_CONTINUE: /* CONTINUE  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1618 "y.tab.c"
        break;

    case YYSYMBOL_INCOP: /* INCOP  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1624 "y.tab.c"
        break;

    case YYSYMBOL_DECOP: /* DECOP  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1630 "y.tab.c"
        break;

    case YYSYMBOL_ASSIGNOP: /* ASSIGNOP  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1636 "y.tab.c"
        break;

    case YYSYMBOL_NOT: /* NOT  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1642 "y.tab.c"
        break;

    case YYSYMBOL_PRINTLN: /* PRINTLN  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1648 "y.tab.c"
        break;

    case YYSYMBOL_LPAREN: /* LPAREN  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1654 "y.tab.c"
        break;

    case YYSYMBOL_RPAREN: /* RPAREN  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1660 "y.tab.c"
        break;

    case YYSYMBOL_LCURL: /* LCURL  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1666 "y.tab.c"
        break;

    case YYSYMBOL_RCURL: /* RCURL  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1672 "y.tab.c"
        break;

    case YYSYMBOL_LTHIRD: /* LTHIRD  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1678 "y.tab.c"
        break;

    case YYSYMBOL_RTHIRD: /* RTHIRD  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1684 "y.tab.c"
        break;

    case YYSYMBOL_COMMA: /* COMMA  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1690 "y.tab.c"
        break;

    case YYSYMBOL_SEMICOLON: /* SEMICOLON  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1696 "y.tab.c"
        break;

    case YYSYMBOL_ID: /* ID  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1702 "y.tab.c"
        break;

    case YYSYMBOL_CONST_INT: /* CONST_INT  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1708 "y.tab.c"
        break;

    case YYSYMBOL_CONST_FLOAT: /* CONST_FLOAT  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1714 "y.tab.c"
        break;

    case YYSYMBOL_CONST_CHAR: /* CONST_CHAR  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1720 "y.tab.c"
        break;

    case YYSYMBOL_ADDOP: /* ADDOP  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1726 "y.tab.c"
        break;

    case YYSYMBOL_MULOP: /* MULOP  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1732 "y.tab.c"
        break;

    case YYSYMBOL_LOGICOP: /* LOGICOP  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1738 "y.tab.c"
        break;

    case YYSYMBOL_RELOP: /* RELOP  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1744 "y.tab.c"
        break;

    case YYSYMBOL_start: /* start  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1750 "y.tab.c"
        break;

    case YYSYMBOL_program: /* program  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1756 "y.tab.c"
        break;

    case YYSYMBOL_unit: /* unit  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1762 "y.tab.c"
        break;

    case YYSYMBOL_func_declaration: /* func_declaration  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1768 "y.tab.c"
        break;

    case YYSYMBOL_func_definition: /* func_definition  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1774 "y.tab.c"
        break;

    case YYSYMBOL_parameter_list: /* parameter_list  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1780 "y.tab.c"
        break;

    case YYSYMBOL_compound_statement: /* compound_statement  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1786 "y.tab.c"
        break;

    case YYSYMBOL_var_declaration: /* var_declaration  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1792 "y.tab.c"
        break;

    case YYSYMBOL_type_specifier: /* type_specifier  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1798 "y.tab.c"
        break;

    case YYSYMBOL_declaration_list: /* declaration_list  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1804 "y.tab.c"
        break;

    case YYSYMBOL_statements: /* statements  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1810 "y.tab.c"
        break;

    case YYSYMBOL_statement: /* statement  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1816 "y.tab.c"
        break;

    case YYSYMBOL_create_if_block: /* create_if_block  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1822 "y.tab.c"
        break;

    case YYSYMBOL_expression_statement: /* expression_statement  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1828 "y.tab.c"
        break;

    case YYSYMBOL_variable: /* variable  */
#line 110 "1905072_parser.y"
            { erm_e(((*yyvaluep).expression));  }
#line 1834 "y.tab.c"
        break;

    case YYSYMBOL_expression: /* expression  */
#line 110 "1905072_parser.y"
            { erm_e(((*yyvaluep).expression));  }
#line 1840 "y.tab.c"
        break;

    case YYSYMBOL_logic_expression: /* logic_expression  */
#line 110 "1905072_parser.y"
            { erm_e(((*yyvaluep).expression));  }
#line 1846 "y.tab.c"
        break;

    case YYSYMBOL_rel_expression: /* rel_expression  */
#line 110 "1905072_parser.y"
            { erm_e(((*yyvaluep).expression));  }
#line 1852 "y.tab.c"
        break;

    case YYSYMBOL_simple_expression: /* simple_expression  */
#line 110 "1905072_parser.y"
            { erm_e(((*yyvaluep).expression));  }
#line 1858 "y.tab.c"
        break;

    case YYSYMBOL_term: /* term  */
#line 110 "1905072_parser.y"
            { erm_e(((*yyvaluep).expression));  }
#line 1864 "y.tab.c"
        break;

    case YYSYMBOL_unary_expression: /* unary_expression  */
#line 110 "1905072_parser.y"
            { erm_e(((*yyvaluep).expression));  }
#line 1870 "y.tab.c"
        break;

    case YYSYMBOL_factor: /* factor  */
#line 110 "1905072_parser.y"
            { erm_e(((*yyvaluep).expression));  }
#line 1876 "y.tab.c"
        break;

    case YYSYMBOL_argument_list: /* argument_list  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1882 "y.tab.c"
        break;

    case YYSYMBOL_arguments: /* arguments  */
#line 109 "1905072_parser.y"
            { erm_se(((*yyvaluep).segment)); }
#line 1888 "y.tab.c"
        break;

    case YYSYMBOL_constant: /* constant  */
#line 110 "1905072_parser.y"
            { erm_e(((*yyvaluep).expression));  }
#line 1894 "y.tab.c"
        break;

      default:
        break;
    }
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
  case 2: /* start: program  */
#line 118 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"start");
							if(error_count==0) asm_gen->endCode();
							cout<<"Code compiled successfully"<<endl;
							freeMemory(child);
						}
#line 2173 "y.tab.c"
    break;

  case 3: /* program: program unit  */
#line 128 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-1].segment),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"program");
							freeMemory(child);			 
						}
#line 2183 "y.tab.c"
    break;

  case 4: /* program: unit  */
#line 134 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"program");
							freeMemory(child);
						}
#line 2193 "y.tab.c"
    break;

  case 5: /* unit: var_declaration  */
#line 142 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"unit");
							freeMemory(child);
						}
#line 2203 "y.tab.c"
    break;

  case 6: /* unit: func_declaration  */
#line 148 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"unit");
							freeMemory(child);
						}
#line 2213 "y.tab.c"
    break;

  case 7: /* unit: func_definition  */
#line 154 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"unit");
							freeMemory(child);
						}
#line 2223 "y.tab.c"
    break;

  case 8: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON  */
#line 162 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-5].segment),(yyvsp[-4].segment),(yyvsp[-3].segment),(yyvsp[-2].segment),(yyvsp[-1].segment),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"func_declaration");
							sem_anlz->declareFunction((yyvsp[-5].segment)->getCode(),(yyvsp[-4].segment)->getCode(),params);
							freeArrayMemory(params);
							freeMemory(child);
						}
#line 2235 "y.tab.c"
    break;

  case 9: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN error  */
#line 170 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-5].segment),(yyvsp[-4].segment),(yyvsp[-3].segment),(yyvsp[-2].segment),(yyvsp[-1].segment)};
							(yyval.segment) = printRuleAndCode(child,"func_declaration");
							sem_anlz->declareFunction((yyvsp[-5].segment)->getCode(),(yyvsp[-4].segment)->getCode(),params);	
							freeArrayMemory(params);
							freeMemory(child);
						}
#line 2247 "y.tab.c"
    break;

  case 10: /* func_declaration: type_specifier ID LPAREN parameter_list error RPAREN SEMICOLON  */
#line 178 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-6].segment),(yyvsp[-5].segment),(yyvsp[-4].segment),(yyvsp[-3].segment),(yyvsp[-1].segment),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"func_declaration");
							sem_anlz->declareFunction((yyvsp[-6].segment)->getCode(),(yyvsp[-5].segment)->getCode(),params);
							freeArrayMemory(params);
							freeMemory(child);
						}
#line 2259 "y.tab.c"
    break;

  case 11: /* func_declaration: type_specifier ID LPAREN parameter_list error RPAREN error  */
#line 186 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-6].segment),(yyvsp[-5].segment),(yyvsp[-4].segment),(yyvsp[-3].segment),(yyvsp[-1].segment)};
							(yyval.segment) = printRuleAndCode(child,"func_declaration");
							sem_anlz->declareFunction((yyvsp[-6].segment)->getCode(),(yyvsp[-5].segment)->getCode(),params);
							freeArrayMemory(params);
							freeMemory(child);
						}
#line 2271 "y.tab.c"
    break;

  case 12: /* func_declaration: type_specifier ID LPAREN RPAREN SEMICOLON  */
#line 194 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-4].segment),(yyvsp[-3].segment),(yyvsp[-2].segment),(yyvsp[-1].segment),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"func_declaration");
							sem_anlz->declareFunction((yyvsp[-4].segment)->getCode(),(yyvsp[-3].segment)->getCode(),vector<Variable*>());
							freeArrayMemory(params);
							freeMemory(child);
						}
#line 2283 "y.tab.c"
    break;

  case 13: /* func_declaration: type_specifier ID LPAREN RPAREN error  */
#line 202 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-4].segment),(yyvsp[-3].segment),(yyvsp[-2].segment),(yyvsp[-1].segment)};
							(yyval.segment) = printRuleAndCode(child,"func_declaration");
							sem_anlz->declareFunction((yyvsp[-4].segment)->getCode(),(yyvsp[-3].segment)->getCode(),{});
							freeArrayMemory(params);
							freeMemory(child);
						}
#line 2295 "y.tab.c"
    break;

  case 14: /* func_declaration: type_specifier ID LPAREN error RPAREN SEMICOLON  */
#line 210 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-5].segment),(yyvsp[-4].segment),(yyvsp[-3].segment),(yyvsp[-1].segment),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"func_declaration");
							sem_anlz->declareFunction((yyvsp[-5].segment)->getCode(),(yyvsp[-4].segment)->getCode(),{});
							freeArrayMemory(params);
							freeMemory(child);
						}
#line 2307 "y.tab.c"
    break;

  case 15: /* func_declaration: type_specifier ID LPAREN error RPAREN SEMICOLON error  */
#line 218 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-6].segment),(yyvsp[-5].segment),(yyvsp[-4].segment),(yyvsp[-2].segment),(yyvsp[-1].segment)};
							(yyval.segment) = printRuleAndCode(child,"func_declaration");
							sem_anlz->declareFunction((yyvsp[-6].segment)->getCode(),(yyvsp[-5].segment)->getCode(),{});
							freeArrayMemory(params);
							freeMemory(child);
						}
#line 2319 "y.tab.c"
    break;

  case 16: /* $@1: %empty  */
#line 228 "1905072_parser.y"
                                                {
							sem_anlz->defineFunction((yyvsp[-4].segment)->getCode(),(yyvsp[-3].segment)->getCode(), params);
						}
#line 2327 "y.tab.c"
    break;

  case 17: /* func_definition: type_specifier ID LPAREN parameter_list RPAREN $@1 compound_statement  */
#line 232 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-6].segment),(yyvsp[-5].segment),(yyvsp[-4].segment),(yyvsp[-3].segment),(yyvsp[-2].segment),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"func_definition");
							// in_function = false;
							// freeArrayMemory(params);
							asm_gen->endProcedure((yyvsp[-5].segment)->getCode());
							freeMemory(child);
						}
#line 2340 "y.tab.c"
    break;

  case 18: /* $@2: %empty  */
#line 241 "1905072_parser.y"
                                                {
							sem_anlz->defineFunction((yyvsp[-5].segment)->getCode(),(yyvsp[-4].segment)->getCode(), params);
						}
#line 2348 "y.tab.c"
    break;

  case 19: /* func_definition: type_specifier ID LPAREN parameter_list error RPAREN $@2 compound_statement  */
#line 245 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-7].segment),(yyvsp[-6].segment),(yyvsp[-5].segment),(yyvsp[-4].segment),(yyvsp[-2].segment),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"func_definition");
							// in_function = false;
							// freeArrayMemory(params);
							freeMemory(child);
						}
#line 2360 "y.tab.c"
    break;

  case 20: /* $@3: %empty  */
#line 253 "1905072_parser.y"
                                                {
							sem_anlz->defineFunction((yyvsp[-3].segment)->getCode(),(yyvsp[-2].segment)->getCode(), vector<Variable*>());
						}
#line 2368 "y.tab.c"
    break;

  case 21: /* func_definition: type_specifier ID LPAREN RPAREN $@3 compound_statement  */
#line 257 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-5].segment),(yyvsp[-4].segment),(yyvsp[-3].segment),(yyvsp[-2].segment),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"func_definition");
							// in_function = false;
							// freeArrayMemory(params);
							asm_gen->endProcedure((yyvsp[-4].segment)->getCode());
							freeMemory(child);
						}
#line 2381 "y.tab.c"
    break;

  case 22: /* $@4: %empty  */
#line 266 "1905072_parser.y"
                                                {
							sem_anlz->defineFunction((yyvsp[-4].segment)->getCode(),(yyvsp[-3].segment)->getCode(), vector<Variable*>());
						}
#line 2389 "y.tab.c"
    break;

  case 23: /* func_definition: type_specifier ID LPAREN error RPAREN $@4 compound_statement  */
#line 270 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-6].segment),(yyvsp[-5].segment),(yyvsp[-4].segment),(yyvsp[-2].segment),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"func_definition");
							// in_function = false;
							// freeArrayMemory(params);
							freeMemory(child);
						}
#line 2401 "y.tab.c"
    break;

  case 24: /* parameter_list: parameter_list COMMA type_specifier ID  */
#line 280 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-3].segment),(yyvsp[-2].segment),(yyvsp[-1].segment),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"parameter_list");
							params.push_back(new Variable((yyvsp[0].segment)->getCode(),(yyvsp[-1].segment)->getCode()));
							freeMemory(child);
						}
#line 2412 "y.tab.c"
    break;

  case 25: /* parameter_list: parameter_list error COMMA type_specifier ID  */
#line 287 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-4].segment),(yyvsp[-2].segment),(yyvsp[-1].segment),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"parameter_list");
							params.push_back(new Variable((yyvsp[0].segment)->getCode(),(yyvsp[-1].segment)->getCode()));
							freeMemory(child);
						}
#line 2423 "y.tab.c"
    break;

  case 26: /* parameter_list: parameter_list COMMA type_specifier  */
#line 294 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-2].segment),(yyvsp[-1].segment),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"parameter_list");
							params.push_back(new Variable("blank",(yyvsp[0].segment)->getCode()));
							freeMemory(child);
						}
#line 2434 "y.tab.c"
    break;

  case 27: /* parameter_list: parameter_list error COMMA type_specifier  */
#line 301 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-3].segment),(yyvsp[-1].segment),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"parameter_list");
							params.push_back(new Variable("blank",(yyvsp[-1].segment)->getCode()));
							freeMemory(child);
						}
#line 2445 "y.tab.c"
    break;

  case 28: /* parameter_list: type_specifier ID  */
#line 308 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-1].segment),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"parameter_list");
							params.push_back(new Variable((yyvsp[0].segment)->getCode(),(yyvsp[-1].segment)->getCode()));
							freeMemory(child);
						}
#line 2456 "y.tab.c"
    break;

  case 29: /* parameter_list: type_specifier  */
#line 315 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"parameter_list");
							params.push_back(new Variable("blank",(yyvsp[0].segment)->getCode()));
							freeMemory(child);
						}
#line 2467 "y.tab.c"
    break;

  case 30: /* compound_statement: LCURL create_scope statements RCURL  */
#line 324 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-3].segment),(yyvsp[-1].segment),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"compound_statement");
							table->printAllScope();
							table->exitScope();
							freeMemory(child);
						}
#line 2479 "y.tab.c"
    break;

  case 31: /* compound_statement: LCURL create_scope statements error RCURL  */
#line 332 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-4].segment),(yyvsp[-2].segment),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"compound_statement");
							table->printAllScope();
							table->exitScope();
							freeMemory(child);
						}
#line 2491 "y.tab.c"
    break;

  case 32: /* compound_statement: LCURL create_scope error statements RCURL  */
#line 340 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-4].segment),(yyvsp[-1].segment),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"compound_statement");
							table->printAllScope();
							table->exitScope();
							freeMemory(child);
						}
#line 2503 "y.tab.c"
    break;

  case 33: /* compound_statement: LCURL create_scope RCURL  */
#line 348 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-2].segment),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"compound_statement");
							table->printAllScope();
							table->exitScope();
							freeMemory(child);
						}
#line 2515 "y.tab.c"
    break;

  case 34: /* compound_statement: LCURL create_scope error RCURL  */
#line 356 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-3].segment),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"compound_statement");
							table->printAllScope();
							table->exitScope();
							freeMemory(child);
						}
#line 2527 "y.tab.c"
    break;

  case 35: /* create_scope: %empty  */
#line 366 "1905072_parser.y"
                                                { 
							table->enterScope(); 
							// cout<<line_count<<" entering new scope"<<endl;
							if(in_function)
							{
								vector<Variable*> func_params;
								for(auto i:params)
								{
									if(i->getName() == "blank") continue;
									Variable *var = new Variable(i->getName(), i->getDataType());
									if(!table->insert(var))
									{
										handleError(MULTIPLE_DECLARATION, line_count, i->getName());
									}
									func_params.push_back(var);
								}
								asm_gen->createFunctionScope(func_params);
								in_function = false;
								freeArrayMemory(params);
							}
						}
#line 2553 "y.tab.c"
    break;

  case 36: /* var_declaration: type_specifier declaration_list SEMICOLON  */
#line 389 "1905072_parser.y"
                                                { 				
							vector<Segment*> child = {(yyvsp[-2].segment),(yyvsp[-1].segment),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"var_declaration");
							sem_anlz->declareVariables((yyvsp[-2].segment)->getCode(),(yyvsp[-1].segment)->getCode(),vars);
							freeArrayMemory(vars);
							freeMemory(child);
						}
#line 2565 "y.tab.c"
    break;

  case 37: /* var_declaration: type_specifier declaration_list error SEMICOLON  */
#line 397 "1905072_parser.y"
                                                { 			
							vector<Segment*> child = {(yyvsp[-3].segment),(yyvsp[-2].segment),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"var_declaration");
							sem_anlz->declareVariables((yyvsp[-3].segment)->getCode(),(yyvsp[-2].segment)->getCode(),vars);
							freeArrayMemory(vars);
							freeMemory(child);
						}
#line 2577 "y.tab.c"
    break;

  case 38: /* type_specifier: INT  */
#line 407 "1905072_parser.y"
                                                { 
							vector<Segment*> child = {(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"type_specifier");
							freeMemory(child);
						}
#line 2587 "y.tab.c"
    break;

  case 39: /* type_specifier: FLOAT  */
#line 413 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"type_specifier");
							freeMemory(child);
						}
#line 2597 "y.tab.c"
    break;

  case 40: /* type_specifier: VOID  */
#line 419 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"type_specifier");
							freeMemory(child);
						}
#line 2607 "y.tab.c"
    break;

  case 41: /* declaration_list: declaration_list COMMA ID  */
#line 427 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-2].segment),(yyvsp[-1].segment),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"declaration_list");

							Variable* tmp = new Variable("PRIMITIVE");
							tmp->setName((yyvsp[0].segment)->getCode());

							vars.push_back(tmp);
							freeMemory(child);
						}
#line 2622 "y.tab.c"
    break;

  case 42: /* declaration_list: declaration_list error COMMA ID  */
#line 438 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-3].segment),(yyvsp[-1].segment),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"declaration_list");

							Variable* tmp = new Variable("PRIMITIVE");
							tmp->setName((yyvsp[0].segment)->getCode());

							vars.push_back(tmp);
							freeMemory(child);
						}
#line 2637 "y.tab.c"
    break;

  case 43: /* declaration_list: declaration_list COMMA ID LTHIRD constant RTHIRD  */
#line 449 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-5].segment),(yyvsp[-4].segment),(yyvsp[-3].segment),(yyvsp[-2].segment),(yyvsp[-1].expression),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"declaration_list");

							Array* tmp = new Array((yyvsp[-3].segment)->getCode());
							if((yyvsp[-1].expression)->getDataType()=="float")
							{
								handleError(INVALID_ARRAY_SIZE, line_count, (yyvsp[-1].expression)->getCode());
							}
							else
							{
								tmp->setArraySize(stoi((yyvsp[-1].expression)->getCode()));
							}
							vars.push_back(tmp);

							freeMemory(child);
						}
#line 2659 "y.tab.c"
    break;

  case 44: /* declaration_list: declaration_list error COMMA ID LTHIRD constant RTHIRD  */
#line 467 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-6].segment),(yyvsp[-4].segment),(yyvsp[-3].segment),(yyvsp[-2].segment),(yyvsp[-1].expression),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"declaration_list");

							Array* tmp = new Array((yyvsp[-3].segment)->getCode());
							if((yyvsp[-1].expression)->getDataType() == "float")
							{
								handleError(INVALID_ARRAY_SIZE, line_count, (yyvsp[-1].expression)->getCode());
							}
							else
							{
								tmp->setArraySize(stoi((yyvsp[-1].expression)->getCode()));
							}
							vars.push_back(tmp);

							freeMemory(child);
						}
#line 2681 "y.tab.c"
    break;

  case 45: /* declaration_list: ID  */
#line 485 "1905072_parser.y"
                                                { 
							vector<Segment*> child = {(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"declaration_list");

							Variable* tmp = new Variable("PRIMITIVE");
							tmp->setName((yyvsp[0].segment)->getCode());
							vars.push_back(tmp);

							freeMemory(child);
						}
#line 2696 "y.tab.c"
    break;

  case 46: /* declaration_list: ID LTHIRD constant RTHIRD  */
#line 496 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-3].segment),(yyvsp[-2].segment),(yyvsp[-1].expression),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"declaration_list");

							Array* tmp = new Array((yyvsp[-3].segment)->getCode());
							if((yyvsp[-1].expression)->getDataType()=="float")
							{
								handleError(INVALID_ARRAY_SIZE, line_count, (yyvsp[-1].expression)->getCode());
							}
							else
							{
								tmp->setArraySize(stoi((yyvsp[-1].expression)->getCode()));
							}
							vars.push_back(tmp);

							freeMemory(child);
						}
#line 2718 "y.tab.c"
    break;

  case 47: /* statements: statement  */
#line 516 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"statements");
							freeMemory(child);
						}
#line 2728 "y.tab.c"
    break;

  case 48: /* statements: statements statement  */
#line 522 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-1].segment),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"statements");
							freeMemory(child);
						}
#line 2738 "y.tab.c"
    break;

  case 49: /* statements: statements error statement  */
#line 528 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-2].segment),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"statements");
							freeMemory(child);
						}
#line 2748 "y.tab.c"
    break;

  case 50: /* statement: var_declaration  */
#line 536 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"statement");
							freeMemory(child);
						}
#line 2758 "y.tab.c"
    break;

  case 51: /* statement: func_definition  */
#line 541 "1905072_parser.y"
                                                                  {
							vector<Segment*> child = {(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"statement");
							handleError(NESTED_FUNCTION, line_count);
							freeMemory(child);
						}
#line 2769 "y.tab.c"
    break;

  case 52: /* statement: func_declaration  */
#line 547 "1905072_parser.y"
                                                                   {
							vector<Segment*> child = {(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"statement");
							handleError(NESTED_FUNCTION, line_count);
							freeMemory(child);
						}
#line 2780 "y.tab.c"
    break;

  case 53: /* statement: expression_statement  */
#line 554 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"statement");
							freeMemory(child);
						}
#line 2790 "y.tab.c"
    break;

  case 54: /* statement: compound_statement  */
#line 560 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"statement");
							freeMemory(child);
						}
#line 2800 "y.tab.c"
    break;

  case 55: /* $@5: %empty  */
#line 566 "1905072_parser.y"
                                                { asm_gen->forLoopStart(); }
#line 2806 "y.tab.c"
    break;

  case 56: /* $@6: %empty  */
#line 568 "1905072_parser.y"
                                                { asm_gen->forLoopConditionCheck(); }
#line 2812 "y.tab.c"
    break;

  case 57: /* $@7: %empty  */
#line 570 "1905072_parser.y"
                                                { asm_gen->gotoNextStepInForLoop((yyvsp[0].expression)->getCode()); }
#line 2818 "y.tab.c"
    break;

  case 58: /* statement: FOR LPAREN expression_statement $@5 expression_statement $@6 expression $@7 RPAREN statement  */
#line 572 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-9].segment),(yyvsp[-8].segment),(yyvsp[-7].segment),(yyvsp[-5].segment),(yyvsp[-3].expression),(yyvsp[-1].segment),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"statement");
							asm_gen->endForLoop();
							freeMemory(child);
						}
#line 2829 "y.tab.c"
    break;

  case 59: /* statement: IF LPAREN expression RPAREN create_if_block statement  */
#line 579 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-5].segment),(yyvsp[-4].segment),(yyvsp[-3].expression),(yyvsp[-2].segment),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"statement");
							asm_gen->endIfBlock((yyvsp[-1].segment)->getCode());
							freeMemory(child);
							
						}
#line 2841 "y.tab.c"
    break;

  case 60: /* $@8: %empty  */
#line 587 "1905072_parser.y"
                                                { asm_gen->createElseBlock((yyvsp[-2].segment)->getCode()); }
#line 2847 "y.tab.c"
    break;

  case 61: /* statement: IF LPAREN expression RPAREN create_if_block statement ELSE $@8 statement  */
#line 589 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-8].segment),(yyvsp[-7].segment),(yyvsp[-6].expression),(yyvsp[-5].segment),(yyvsp[-3].segment),(yyvsp[-2].segment),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"statement");
							asm_gen->endIfElseBlock();
							freeMemory(child);
						}
#line 2858 "y.tab.c"
    break;

  case 62: /* $@9: %empty  */
#line 595 "1905072_parser.y"
                                                         { asm_gen->whileLoopStart(); }
#line 2864 "y.tab.c"
    break;

  case 63: /* $@10: %empty  */
#line 596 "1905072_parser.y"
                                                { asm_gen->whileLoopConditionCheck((yyvsp[0].expression)->getCode()); }
#line 2870 "y.tab.c"
    break;

  case 64: /* statement: WHILE $@9 LPAREN expression $@10 RPAREN statement  */
#line 597 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-6].segment),(yyvsp[-4].segment),(yyvsp[-3].expression),(yyvsp[-1].segment),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"statement");
							asm_gen->endWhileLoop();
							freeMemory(child);
						}
#line 2881 "y.tab.c"
    break;

  case 65: /* statement: PRINTLN LPAREN ID RPAREN SEMICOLON  */
#line 604 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-4].segment),(yyvsp[-3].segment),(yyvsp[-2].segment),(yyvsp[-1].segment),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"statement");	
							Identifier* id = (Identifier*)table->search((yyvsp[-2].segment)->getCode());	
							if(id == NULL)
							{
								handleError(UNDECLARED_VARIABLE, line_count, (yyvsp[-2].segment)->getCode());
							}
							else
							{
								asm_gen->printId(id);
							}
							freeMemory(child);
						}
#line 2900 "y.tab.c"
    break;

  case 66: /* statement: RETURN expression SEMICOLON  */
#line 619 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-2].segment),(yyvsp[-1].expression),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"statement");
							asm_gen->returnProcedure();
							freeMemory(child);
						}
#line 2911 "y.tab.c"
    break;

  case 67: /* statement: RETURN SEMICOLON  */
#line 625 "1905072_parser.y"
                                                                   {
							// New rule
							vector<Segment*> child = {(yyvsp[-1].segment),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"statement");
							asm_gen->returnProcedure();
							freeMemory(child);
						}
#line 2923 "y.tab.c"
    break;

  case 68: /* create_if_block: %empty  */
#line 635 "1905072_parser.y"
                                                {
								(yyval.segment) = asm_gen->createIfBlock();
						}
#line 2931 "y.tab.c"
    break;

  case 69: /* expression_statement: SEMICOLON  */
#line 641 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"expression_statement");
							freeMemory(child);
						}
#line 2941 "y.tab.c"
    break;

  case 70: /* expression_statement: expression SEMICOLON  */
#line 647 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-1].expression),(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"expression_statement");
							asm_gen->handleExtraExpressionPush((yyvsp[-1].expression)->getExpression());
							freeMemory(child);
						}
#line 2952 "y.tab.c"
    break;

  case 71: /* variable: ID  */
#line 656 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[0].segment)};
							(yyval.expression) = (Expression*) printRuleAndCode(child,"variable", true);
							// $$->setToken(new Variable("PRIMITIVE"));
							(yyval.expression)->setDataType(sem_anlz->callVariable((yyvsp[0].segment)->getCode()));
							// $$->getToken()->setDataType(callVariable($1->getCode()));
							freeMemory(child);
						}
#line 2965 "y.tab.c"
    break;

  case 72: /* variable: ID LTHIRD expression RTHIRD  */
#line 665 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-3].segment),(yyvsp[-2].segment),(yyvsp[-1].expression),(yyvsp[0].segment)};
							(yyval.expression) = (Expression*) printRuleAndCode(child,"variable",true);
							// $$->setToken(new Variable("ARRAY"));
							(yyval.expression)->setDataType(sem_anlz->callArray((yyvsp[-3].segment)->getCode(),(yyvsp[-1].expression)));
							// $$->getToken()->setDataType(callArray($1->getCode(),$3));
							freeMemory(child);
						}
#line 2978 "y.tab.c"
    break;

  case 73: /* expression: logic_expression  */
#line 676 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[0].expression)};
							(yyval.expression) = (Expression*) printRuleAndCode(child,"expression",true);
							(yyval.expression)->setDataType((yyvsp[0].expression)->getDataType());
							freeMemory(child);
						}
#line 2989 "y.tab.c"
    break;

  case 74: /* expression: variable ASSIGNOP logic_expression  */
#line 683 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-2].expression),(yyvsp[-1].segment),(yyvsp[0].expression)};
							(yyval.expression) = (Expression*) printRuleAndCode(child,"expression",true);
							// new Variable($1->getCode(),$1->getDataType());
							
							string var_name = "";
							for(char c: (yyvsp[-2].expression)->getCode())
							{
								if(c=='[') break;
								var_name += c;
							}
							Variable* var = (Variable*)table->search(var_name);

							(yyval.expression)->setDataType(sem_anlz->assignOp(var,(yyvsp[0].expression)));
							
							freeMemory(child);
						}
#line 3011 "y.tab.c"
    break;

  case 75: /* logic_expression: rel_expression  */
#line 703 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[0].expression)};
							(yyval.expression) = (Expression*) printRuleAndCode(child,"logic_expression",true);
							(yyval.expression)->setDataType((yyvsp[0].expression)->getDataType());
							freeMemory(child);
						}
#line 3022 "y.tab.c"
    break;

  case 76: /* logic_expression: rel_expression LOGICOP rel_expression  */
#line 710 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-2].expression),(yyvsp[-1].segment),(yyvsp[0].expression)};
							(yyval.expression) = (Expression*) printRuleAndCode(child,"logic_expression",true);
							(yyval.expression)->setDataType(sem_anlz->logicOp((yyvsp[-2].expression),(yyvsp[-1].segment)->getCode(),(yyvsp[0].expression)));
							freeMemory(child);
						}
#line 3033 "y.tab.c"
    break;

  case 77: /* rel_expression: simple_expression  */
#line 719 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[0].expression)};
							(yyval.expression) = (Expression*) printRuleAndCode(child,"rel_expression",true);
							(yyval.expression)->setDataType((yyvsp[0].expression)->getDataType());
							freeMemory(child);
						}
#line 3044 "y.tab.c"
    break;

  case 78: /* rel_expression: simple_expression RELOP simple_expression  */
#line 726 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-2].expression),(yyvsp[-1].segment),(yyvsp[0].expression)};
							(yyval.expression) = (Expression*) printRuleAndCode(child,"rel_expression",true);
							(yyval.expression)->setDataType(sem_anlz->relOp((yyvsp[-2].expression),(yyvsp[-1].segment)->getCode(),(yyvsp[0].expression)));
							freeMemory(child);
						}
#line 3055 "y.tab.c"
    break;

  case 79: /* simple_expression: term  */
#line 735 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[0].expression)};
							(yyval.expression) = (Expression*) printRuleAndCode(child,"simple_expression",true);
							(yyval.expression)->setDataType((yyvsp[0].expression)->getDataType());
							freeMemory(child);
						}
#line 3066 "y.tab.c"
    break;

  case 80: /* simple_expression: simple_expression ADDOP term  */
#line 742 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-2].expression),(yyvsp[-1].segment),(yyvsp[0].expression)};
							(yyval.expression) = (Expression*) printRuleAndCode(child,"simple_expression",true);
							(yyval.expression)->setDataType(sem_anlz->addOp((yyvsp[-2].expression),(yyvsp[-1].segment)->getCode(),(yyvsp[0].expression)));
							freeMemory(child);
						}
#line 3077 "y.tab.c"
    break;

  case 81: /* term: unary_expression  */
#line 751 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[0].expression)};
							(yyval.expression) = (Expression*) printRuleAndCode(child,"term",true);
							(yyval.expression)->setDataType((yyvsp[0].expression)->getDataType());
							freeMemory(child);
						}
#line 3088 "y.tab.c"
    break;

  case 82: /* term: term MULOP unary_expression  */
#line 758 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-2].expression),(yyvsp[-1].segment),(yyvsp[0].expression)};
							(yyval.expression) = (Expression*) printRuleAndCode(child,"term",true);
							(yyval.expression)->setDataType(sem_anlz->mulOp((yyvsp[-2].expression),(yyvsp[-1].segment)->getCode(),(yyvsp[0].expression)));
							freeMemory(child);
						}
#line 3099 "y.tab.c"
    break;

  case 83: /* unary_expression: ADDOP unary_expression  */
#line 767 "1905072_parser.y"
                                                { 
							vector<Segment*> child = {(yyvsp[-1].segment),(yyvsp[0].expression)};
							(yyval.expression) = (Expression*) printRuleAndCode({(yyvsp[-1].segment),(yyvsp[0].expression)},"unary_expression",true);
							(yyval.expression)->setDataType((yyvsp[0].expression)->getDataType());
							asm_gen->unaryOperation((yyvsp[-1].segment)->getCode(), (yyvsp[0].expression));
							freeMemory(child);
						}
#line 3111 "y.tab.c"
    break;

  case 84: /* unary_expression: NOT unary_expression  */
#line 775 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-1].segment),(yyvsp[0].expression)};
							(yyval.expression) = (Expression*) printRuleAndCode(child,"unary_expression",true);
							(yyval.expression)->setDataType((yyvsp[0].expression)->getDataType());
							asm_gen->notOperation((yyvsp[0].expression));
							freeMemory(child);
						}
#line 3123 "y.tab.c"
    break;

  case 85: /* unary_expression: factor  */
#line 783 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[0].expression)};
							(yyval.expression) = (Expression*) printRuleAndCode(child,"unary_expression",true);
							(yyval.expression)->setDataType((yyvsp[0].expression)->getDataType());
							freeMemory(child);
						}
#line 3134 "y.tab.c"
    break;

  case 86: /* factor: variable  */
#line 792 "1905072_parser.y"
                                                {
							asm_gen->popArrayFromStack("BX", new Variable((yyvsp[0].expression)->getCode(),(yyvsp[0].expression)->getDataType(), ((yyvsp[0].expression)->getCode().back()==']'?"ARRAY":"PRIMITIVE")));

							vector<Segment*> child = {(yyvsp[0].expression)};
							(yyval.expression) = (Expression*) printRuleAndCode(child,"factor",true);
							(yyval.expression)->setDataType((yyvsp[0].expression)->getDataType());
							freeMemory(child);
						}
#line 3147 "y.tab.c"
    break;

  case 87: /* factor: ID LPAREN argument_list RPAREN  */
#line 801 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-3].segment),(yyvsp[-2].segment),(yyvsp[-1].segment),(yyvsp[0].segment)};
							(yyval.expression) = (Expression*) printRuleAndCode(child,"factor",true);
							(yyval.expression)->setDataType(sem_anlz->callFunction((yyvsp[-3].segment)->getCode(), args));
							args.clear();
							freeMemory(child);
						}
#line 3159 "y.tab.c"
    break;

  case 88: /* factor: LPAREN expression RPAREN  */
#line 809 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-2].segment),(yyvsp[-1].expression),(yyvsp[0].segment)};
							(yyval.expression) = (Expression*) printRuleAndCode(child,"factor",true);
							(yyval.expression)->setDataType((yyvsp[-1].expression)->getDataType());
							freeMemory(child);
						}
#line 3170 "y.tab.c"
    break;

  case 89: /* factor: CONST_INT  */
#line 816 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[0].segment)};
							(yyval.expression) = (Expression*) printRuleAndCode(child,"factor", true);
							(yyval.expression)->setDataType("int");
							asm_gen->callConstant(new Constant((yyvsp[0].segment)->getCode(),"int"));
							// $$->setIdType("CONSTANT");
							freeMemory(child);
						}
#line 3183 "y.tab.c"
    break;

  case 90: /* factor: CONST_FLOAT  */
#line 825 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[0].segment)};
							(yyval.expression) =(Expression*)  printRuleAndCode(child,"factor", true);
							(yyval.expression)->setDataType("float");
							asm_gen->callConstant(new Constant((yyvsp[0].segment)->getCode(),"float"));
							// $$->setIdType("CONSTANT");
							freeMemory(child);
						}
#line 3196 "y.tab.c"
    break;

  case 91: /* factor: variable INCOP  */
#line 834 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-1].expression),(yyvsp[0].segment)};
							(yyval.expression) = (Expression*) printRuleAndCode(child,"factor",true);
							(yyval.expression)->setDataType((yyvsp[-1].expression)->getDataType());

							if((yyvsp[-1].expression)->getDataType()!="NULL")
							asm_gen->incrementOperation((Variable*)table->search((yyvsp[-1].expression)->getCode()));
							freeMemory(child);
						}
#line 3210 "y.tab.c"
    break;

  case 92: /* factor: variable DECOP  */
#line 844 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-1].expression),(yyvsp[0].segment)};
							(yyval.expression) = (Expression*) printRuleAndCode(child,"factor",true);
							(yyval.expression)->setDataType((yyvsp[-1].expression)->getDataType());
							if((yyvsp[-1].expression)->getDataType()!="NULL")
							asm_gen->decrementOperation((Variable*)table->search((yyvsp[-1].expression)->getCode()));
							freeMemory(child);
						}
#line 3223 "y.tab.c"
    break;

  case 93: /* argument_list: arguments  */
#line 855 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[0].segment)};
							(yyval.segment) = printRuleAndCode(child,"argument_list");
							freeMemory(child);
						}
#line 3233 "y.tab.c"
    break;

  case 94: /* argument_list: %empty  */
#line 861 "1905072_parser.y"
                                                { 
							vector<Segment*> child = {};
							(yyval.segment) = printRuleAndCode(child,"argument_list");
							freeMemory(child);
						}
#line 3243 "y.tab.c"
    break;

  case 95: /* arguments: arguments COMMA logic_expression  */
#line 869 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[-2].segment),(yyvsp[-1].segment),(yyvsp[0].expression)};
							(yyval.segment) = printRuleAndCode(child,"arguments");
							args.push_back((yyvsp[0].expression)->getDataType());
							freeMemory(child);
						}
#line 3254 "y.tab.c"
    break;

  case 96: /* arguments: logic_expression  */
#line 876 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[0].expression)};
							(yyval.segment) = printRuleAndCode(child,"arguments");

							args.push_back((yyvsp[0].expression)->getDataType());

							freeMemory(child);
						}
#line 3267 "y.tab.c"
    break;

  case 97: /* constant: CONST_INT  */
#line 887 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[0].segment)};
							(yyval.expression) = (Expression*) printRuleAndCode(child,"constant",true);
							(yyval.expression)->setDataType("int");
							// $$->setIdType("CONSTANT");
							freeMemory(child);
						}
#line 3279 "y.tab.c"
    break;

  case 98: /* constant: CONST_FLOAT  */
#line 895 "1905072_parser.y"
                                                {
							vector<Segment*> child = {(yyvsp[0].segment)};
							(yyval.expression) = (Expression*) printRuleAndCode(child,"constant",true);
							(yyval.expression)->setDataType("float");
							// $$->setIdType("CONSTANT");
							freeMemory(child);
						}
#line 3291 "y.tab.c"
    break;


#line 3295 "y.tab.c"

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

#line 902 "1905072_parser.y"

