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
#include "1905072_SymbolInfo.hpp"
#include "1905072_SymbolTable.hpp"
#include "1905072_ScopeTable.hpp"
#include "1905072_Logger.hpp"
#include "1905072_Error_Handler.hpp"
#include "1905072_Semantic_Analyzer.hpp"
#include "1905072_Helper.hpp"
#include "1905072_Assembly_Generator.hpp"
#include "1905072_Symbol_Extended.hpp"
#include "1905072_Tokenizer.hpp"
using namespace std;

extern ofstream logout;
extern ofstream errout;
extern ofstream tokenout;
extern ofstream codeout;
extern ErrorHandler* err_hndlr;
Expression *last_exp;
int yylex(void);
extern int line_count;
extern int error_count;
extern int lexical_error_count;
extern int syntax_error_count;
extern int semantic_error_count;

extern SymbolTable *table;
extern AssemblyGenerator* asm_gen;
extern SemanticAnalyzer* sem_anlz;
bool in_function = false;
unsigned long sdbmHash(string str);
extern vector<string> data_segment;
void yyerror(string error){
	syntax_error_count++;
	err_hndlr->printError(error, line_count);
}

void erm_s(SymbolInfo* s) // erase memory of SymbolInfo pointer
{
    if(s!=NULL) delete s;
}

void erm_nt(NonTerminal* nt) // erase memory of SymbolInfo pointer
{
    if(nt!=NULL) delete nt;
}

void erm_t(Terminal* t) // erase memory of SymbolInfo pointer
{
    if(t!=NULL) delete t;
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

// void freeMemory(vector<NonTerminal*> symbols)
// {
// 	for(auto &i: symbols)
// 	{
// 		erm_nt(i);
// 	}
// }
// void freeMemory(vector<Expression*> symbols)
// {
// 	for(auto &i: symbols)
// 	{
// 		erm_e(i);
// 	}
// }
// void freeMemory(vector<Variable*> symbols)
// {
// 	for(auto &i: symbols)
// 	{
// 		erm_v(i);
// 	}
// }

// void freeArrayMemory(vector<Variable*> &symbols)
// {
// 	freeMemory(symbols);
// 	symbols.clear();
// }
// void freeArrayMemory(vector<Expression*> symbols)
// {
// 	freeMemory(symbols);
// 	symbols.clear();
// }

#line 180 "y.tab.c"

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
    THEN = 260,                    /* THEN  */
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
#define THEN 260
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
#line 112 "1905072_parser.y"

	Terminal *terminal;
	NonTerminal *non_terminal;
	Expression *expression;
	ArgumentList *args;
	ParameterList *params;
	DeclarationList *vars;

#line 324 "y.tab.c"

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
  YYSYMBOL_THEN = 5,                       /* THEN  */
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
  YYSYMBOL_create_if_block = 65,           /* create_if_block  */
  YYSYMBOL_expression_statement = 66,      /* expression_statement  */
  YYSYMBOL_variable = 67,                  /* variable  */
  YYSYMBOL_expression = 68,                /* expression  */
  YYSYMBOL_logic_expression = 69,          /* logic_expression  */
  YYSYMBOL_rel_expression = 70,            /* rel_expression  */
  YYSYMBOL_simple_expression = 71,         /* simple_expression  */
  YYSYMBOL_term = 72,                      /* term  */
  YYSYMBOL_unary_expression = 73,          /* unary_expression  */
  YYSYMBOL_factor = 74,                    /* factor  */
  YYSYMBOL_argument_list = 75,             /* argument_list  */
  YYSYMBOL_arguments = 76,                 /* arguments  */
  YYSYMBOL_constant = 77                   /* constant  */
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
#define YYLAST   333

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  97
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  162

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
       0,   151,   151,   161,   167,   175,   181,   187,   196,   204,
     212,   220,   228,   236,   244,   252,   264,   263,   279,   278,
     292,   291,   308,   307,   323,   332,   341,   350,   359,   367,
     377,   385,   393,   401,   409,   421,   432,   442,   453,   459,
     465,   474,   484,   493,   508,   523,   533,   548,   555,   562,
     570,   576,   582,   588,   594,   601,   605,   600,   615,   625,
     623,   637,   642,   636,   653,   674,   683,   695,   699,   705,
     714,   725,   743,   755,   769,   777,   792,   800,   815,   823,
     839,   847,   863,   875,   887,   897,   914,   932,   940,   948,
     956,   970,   985,   994,  1001,  1010,  1021,  1029
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
  "\"end of file\"", "error", "\"invalid token\"", "IF", "ELSE", "THEN",
  "SWITCH", "CASE", "DEFAULT", "FOR", "DO", "WHILE", "INT", "FLOAT",
  "DOUBLE", "CHAR", "STRING", "VOID", "BREAK", "RETURN", "CONTINUE",
  "INCOP", "DECOP", "ASSIGNOP", "NOT", "PRINTLN", "LPAREN", "RPAREN",
  "LCURL", "RCURL", "LTHIRD", "RTHIRD", "COMMA", "SEMICOLON", "ID",
  "CONST_INT", "CONST_FLOAT", "CONST_CHAR", "ADDOP", "MULOP", "LOGICOP",
  "RELOP", "$accept", "start", "program", "unit", "func_declaration",
  "func_definition", "$@1", "$@2", "$@3", "$@4", "parameter_list",
  "compound_statement", "create_scope", "var_declaration",
  "type_specifier", "declaration_list", "statements", "statement", "$@5",
  "$@6", "$@7", "$@8", "$@9", "create_if_block", "expression_statement",
  "variable", "expression", "logic_expression", "rel_expression",
  "simple_expression", "term", "unary_expression", "factor",
  "argument_list", "arguments", "constant", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-101)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-21)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      37,  -101,  -101,  -101,    14,    37,  -101,  -101,  -101,  -101,
     -26,  -101,  -101,     9,     5,    52,    39,    82,   -10,  -101,
      -1,     1,    15,    38,  -101,  -101,    58,    57,  -101,    68,
      67,  -101,  -101,    79,     0,     8,    37,  -101,  -101,    81,
      39,    84,    79,  -101,  -101,    18,    37,  -101,  -101,    79,
      92,    39,    85,  -101,  -101,   120,  -101,  -101,    79,    93,
    -101,  -101,    97,  -101,   220,   104,   108,  -101,   282,   -13,
     109,   -13,  -101,  -101,    64,  -101,  -101,   -13,  -101,  -101,
    -101,  -101,   156,  -101,  -101,    83,   105,  -101,    96,    61,
     101,  -101,  -101,  -101,  -101,  -101,  -101,   192,   -13,   295,
     115,  -101,   110,   103,  -101,   113,   123,   -13,   -13,  -101,
     248,  -101,  -101,  -101,  -101,   -13,  -101,   -13,   -13,   -13,
     -13,   276,  -101,   124,  -101,   -13,  -101,   125,  -101,  -101,
     133,   129,   111,  -101,  -101,  -101,  -101,   101,   126,  -101,
    -101,   295,  -101,   130,  -101,   -13,  -101,   276,   -13,   135,
    -101,  -101,   162,  -101,   276,  -101,   143,  -101,   276,   276,
    -101,  -101
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    38,    39,    40,     0,     2,     4,     6,     7,     5,
       0,     1,     3,    45,     0,     0,     0,     0,     0,    36,
       0,     0,     0,    29,    96,    97,     0,     0,    37,    41,
      22,    13,    12,     0,     0,     0,     0,    28,    46,    42,
       0,     0,     0,    35,    21,     0,     0,     9,     8,     0,
      26,     0,     0,    15,    23,     0,    11,    10,     0,    27,
      17,    24,     0,    43,     0,     0,     0,    61,     0,     0,
       0,     0,    33,    68,    70,    88,    89,     0,    52,    51,
      54,    50,     0,    47,    53,    85,     0,    72,    74,    76,
      78,    80,    84,    19,    25,    44,    34,     0,     0,     0,
       0,    66,     0,    85,    83,     0,     0,    93,     0,    82,
       0,    30,    48,    90,    91,     0,    69,     0,     0,     0,
       0,     0,    32,     0,    55,     0,    65,     0,    87,    95,
       0,    92,     0,    31,    49,    73,    75,    79,    77,    81,
      67,     0,    62,     0,    86,     0,    71,     0,     0,     0,
      64,    94,    58,    56,     0,    59,     0,    63,     0,     0,
      60,    57
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -101,  -101,  -101,   166,    63,    66,  -101,  -101,  -101,  -101,
    -101,    34,  -101,    73,    16,  -101,   112,   -77,  -101,  -101,
    -101,  -101,  -101,  -101,   -98,   -59,   -68,  -100,    55,    59,
      56,   -65,  -101,  -101,  -101,   -23
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     4,     5,     6,    78,    79,    49,    58,    33,    42,
      22,    80,    55,    81,    10,    14,    82,    83,   141,   156,
     158,   100,   149,   147,    84,    85,    86,    87,    88,    89,
      90,    91,    92,   130,   131,    26
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     102,   124,    31,   106,   104,   112,    17,   129,    13,    47,
     103,    69,   109,    71,    11,   135,    34,    52,   103,    56,
     112,    74,    75,    76,    29,    77,    30,    45,    62,   -20,
     123,    23,    46,   134,    32,    15,   -16,    18,    19,    16,
     132,    48,    35,   148,   134,   151,   -18,    36,   103,     1,
       2,    57,    50,    20,     3,   139,   103,   142,   103,   103,
     103,   103,    59,     7,     1,     2,     8,    44,     7,     3,
     152,     8,    37,     9,    24,    25,    54,   157,     9,    21,
     153,   160,   161,    60,   -14,    53,   103,   -14,   -14,    38,
     107,    39,    93,   -14,   108,   -14,   -14,   -14,    40,   118,
      41,   -14,   119,   -14,   113,   114,   115,    43,   -14,   -14,
     -14,    51,   -14,   -14,    27,    28,    63,   -14,   -14,   -14,
     -14,    64,   -14,    65,   113,   114,    61,    94,    95,    66,
      98,    67,     1,     2,    99,   105,   117,     3,   116,    68,
     120,   125,   146,   126,    69,    70,    71,   127,    43,    72,
     128,   140,   143,    73,    74,    75,    76,   110,    77,    65,
     144,   145,   154,   150,   118,    66,   155,    67,     1,     2,
     159,    12,   136,     3,   137,    68,    97,     0,   138,     0,
      69,    70,    71,     0,    43,   111,     0,     0,     0,    73,
      74,    75,    76,   121,    77,    65,     0,     0,     0,     0,
       0,    66,     0,    67,     1,     2,     0,     0,     0,     3,
       0,    68,     0,     0,     0,     0,    69,    70,    71,     0,
      43,   122,     0,    65,     0,    73,    74,    75,    76,    66,
      77,    67,     1,     2,     0,     0,     0,     3,     0,    68,
       0,     0,     0,     0,    69,    70,    71,     0,    43,    96,
       0,    65,     0,    73,    74,    75,    76,    66,    77,    67,
       1,     2,     0,     0,     0,     3,     0,    68,     0,     0,
       0,     0,    69,    70,    71,     0,    43,   133,     0,    65,
       0,    73,    74,    75,    76,    66,    77,    67,     1,     2,
       0,     0,     0,     3,     0,    68,     0,     0,     0,     0,
      69,    70,    71,     0,    43,     0,    69,     0,    71,    73,
      74,    75,    76,     0,    77,   101,    74,    75,    76,    69,
      77,    71,     0,     0,     0,     0,     0,     0,    73,    74,
      75,    76,     0,    77
};

static const yytype_int16 yycheck[] =
{
      68,    99,     1,    71,    69,    82,     1,   107,    34,     1,
      69,    24,    77,    26,     0,   115,     1,    40,    77,     1,
      97,    34,    35,    36,    34,    38,    27,    27,    51,    28,
      98,    15,    32,   110,    33,    26,    28,    32,    33,    30,
     108,    33,    27,   141,   121,   145,    28,    32,   107,    12,
      13,    33,    36,     1,    17,   120,   115,   125,   117,   118,
     119,   120,    46,     0,    12,    13,     0,    33,     5,    17,
     147,     5,    34,     0,    35,    36,    42,   154,     5,    27,
     148,   158,   159,    49,     0,     1,   145,     3,     4,    31,
      26,    34,    58,     9,    30,    11,    12,    13,    30,    38,
      33,    17,    41,    19,    21,    22,    23,    28,    24,    25,
      26,    30,    28,    29,    32,    33,    31,    33,    34,    35,
      36,     1,    38,     3,    21,    22,    34,    34,    31,     9,
      26,    11,    12,    13,    26,    26,    40,    17,    33,    19,
      39,    26,    31,    33,    24,    25,    26,    34,    28,    29,
      27,    27,    27,    33,    34,    35,    36,     1,    38,     3,
      27,    32,    27,    33,    38,     9,     4,    11,    12,    13,
      27,     5,   117,    17,   118,    19,    64,    -1,   119,    -1,
      24,    25,    26,    -1,    28,    29,    -1,    -1,    -1,    33,
      34,    35,    36,     1,    38,     3,    -1,    -1,    -1,    -1,
      -1,     9,    -1,    11,    12,    13,    -1,    -1,    -1,    17,
      -1,    19,    -1,    -1,    -1,    -1,    24,    25,    26,    -1,
      28,    29,    -1,     3,    -1,    33,    34,    35,    36,     9,
      38,    11,    12,    13,    -1,    -1,    -1,    17,    -1,    19,
      -1,    -1,    -1,    -1,    24,    25,    26,    -1,    28,    29,
      -1,     3,    -1,    33,    34,    35,    36,     9,    38,    11,
      12,    13,    -1,    -1,    -1,    17,    -1,    19,    -1,    -1,
      -1,    -1,    24,    25,    26,    -1,    28,    29,    -1,     3,
      -1,    33,    34,    35,    36,     9,    38,    11,    12,    13,
      -1,    -1,    -1,    17,    -1,    19,    -1,    -1,    -1,    -1,
      24,    25,    26,    -1,    28,    -1,    24,    -1,    26,    33,
      34,    35,    36,    -1,    38,    33,    34,    35,    36,    24,
      38,    26,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      35,    36,    -1,    38
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    12,    13,    17,    43,    44,    45,    46,    47,    55,
      56,     0,    45,    34,    57,    26,    30,     1,    32,    33,
       1,    27,    52,    56,    35,    36,    77,    32,    33,    34,
      27,     1,    33,    50,     1,    27,    32,    34,    31,    34,
      30,    33,    51,    28,    53,    27,    32,     1,    33,    48,
      56,    30,    77,     1,    53,    54,     1,    33,    49,    56,
      53,    34,    77,    31,     1,     3,     9,    11,    19,    24,
      25,    26,    29,    33,    34,    35,    36,    38,    46,    47,
      53,    55,    58,    59,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    53,    34,    31,    29,    58,    26,    26,
      63,    33,    68,    67,    73,    26,    68,    26,    30,    73,
       1,    29,    59,    21,    22,    23,    33,    40,    38,    41,
      39,     1,    29,    68,    66,    26,    33,    34,    27,    69,
      75,    76,    68,    29,    59,    69,    70,    72,    71,    73,
      27,    60,    68,    27,    27,    32,    31,    65,    66,    64,
      33,    69,    59,    68,    27,     4,    61,    59,    62,    27,
      59,    59
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    45,    45,    46,    46,
      46,    46,    46,    46,    46,    46,    48,    47,    49,    47,
      50,    47,    51,    47,    52,    52,    52,    52,    52,    52,
      53,    53,    53,    53,    53,    54,    55,    55,    56,    56,
      56,    57,    57,    57,    57,    57,    57,    58,    58,    58,
      59,    59,    59,    59,    59,    60,    61,    59,    59,    62,
      59,    63,    64,    59,    59,    59,    59,    65,    66,    66,
      67,    67,    68,    68,    69,    69,    70,    70,    71,    71,
      72,    72,    73,    73,    73,    74,    74,    74,    74,    74,
      74,    74,    75,    75,    76,    76,    77,    77
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     6,
       7,     7,     5,     5,     6,     7,     0,     7,     0,     8,
       0,     6,     0,     7,     4,     5,     3,     4,     2,     1,
       4,     5,     5,     3,     4,     0,     3,     4,     1,     1,
       1,     3,     4,     6,     7,     1,     4,     1,     2,     3,
       1,     1,     1,     1,     1,     0,     0,     9,     6,     0,
       9,     0,     0,     7,     5,     3,     2,     0,     1,     2,
       1,     4,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     2,     2,     1,     1,     4,     3,     1,     1,
       2,     2,     1,     0,     3,     1,     1,     1
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
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1536 "y.tab.c"
        break;

    case YYSYMBOL_ELSE: /* ELSE  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1542 "y.tab.c"
        break;

    case YYSYMBOL_THEN: /* THEN  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1548 "y.tab.c"
        break;

    case YYSYMBOL_SWITCH: /* SWITCH  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1554 "y.tab.c"
        break;

    case YYSYMBOL_CASE: /* CASE  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1560 "y.tab.c"
        break;

    case YYSYMBOL_DEFAULT: /* DEFAULT  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1566 "y.tab.c"
        break;

    case YYSYMBOL_FOR: /* FOR  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1572 "y.tab.c"
        break;

    case YYSYMBOL_DO: /* DO  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1578 "y.tab.c"
        break;

    case YYSYMBOL_WHILE: /* WHILE  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1584 "y.tab.c"
        break;

    case YYSYMBOL_INT: /* INT  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1590 "y.tab.c"
        break;

    case YYSYMBOL_FLOAT: /* FLOAT  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1596 "y.tab.c"
        break;

    case YYSYMBOL_DOUBLE: /* DOUBLE  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1602 "y.tab.c"
        break;

    case YYSYMBOL_CHAR: /* CHAR  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1608 "y.tab.c"
        break;

    case YYSYMBOL_STRING: /* STRING  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1614 "y.tab.c"
        break;

    case YYSYMBOL_VOID: /* VOID  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1620 "y.tab.c"
        break;

    case YYSYMBOL_BREAK: /* BREAK  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1626 "y.tab.c"
        break;

    case YYSYMBOL_RETURN: /* RETURN  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1632 "y.tab.c"
        break;

    case YYSYMBOL_CONTINUE: /* CONTINUE  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1638 "y.tab.c"
        break;

    case YYSYMBOL_INCOP: /* INCOP  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1644 "y.tab.c"
        break;

    case YYSYMBOL_DECOP: /* DECOP  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1650 "y.tab.c"
        break;

    case YYSYMBOL_ASSIGNOP: /* ASSIGNOP  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1656 "y.tab.c"
        break;

    case YYSYMBOL_NOT: /* NOT  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1662 "y.tab.c"
        break;

    case YYSYMBOL_PRINTLN: /* PRINTLN  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1668 "y.tab.c"
        break;

    case YYSYMBOL_LPAREN: /* LPAREN  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1674 "y.tab.c"
        break;

    case YYSYMBOL_RPAREN: /* RPAREN  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1680 "y.tab.c"
        break;

    case YYSYMBOL_LCURL: /* LCURL  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1686 "y.tab.c"
        break;

    case YYSYMBOL_RCURL: /* RCURL  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1692 "y.tab.c"
        break;

    case YYSYMBOL_LTHIRD: /* LTHIRD  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1698 "y.tab.c"
        break;

    case YYSYMBOL_RTHIRD: /* RTHIRD  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1704 "y.tab.c"
        break;

    case YYSYMBOL_COMMA: /* COMMA  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1710 "y.tab.c"
        break;

    case YYSYMBOL_SEMICOLON: /* SEMICOLON  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1716 "y.tab.c"
        break;

    case YYSYMBOL_ID: /* ID  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1722 "y.tab.c"
        break;

    case YYSYMBOL_CONST_INT: /* CONST_INT  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1728 "y.tab.c"
        break;

    case YYSYMBOL_CONST_FLOAT: /* CONST_FLOAT  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1734 "y.tab.c"
        break;

    case YYSYMBOL_CONST_CHAR: /* CONST_CHAR  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1740 "y.tab.c"
        break;

    case YYSYMBOL_ADDOP: /* ADDOP  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1746 "y.tab.c"
        break;

    case YYSYMBOL_MULOP: /* MULOP  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1752 "y.tab.c"
        break;

    case YYSYMBOL_LOGICOP: /* LOGICOP  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1758 "y.tab.c"
        break;

    case YYSYMBOL_RELOP: /* RELOP  */
#line 131 "1905072_parser.y"
            { erm_t(((*yyvaluep).terminal)); }
#line 1764 "y.tab.c"
        break;

    case YYSYMBOL_start: /* start  */
#line 132 "1905072_parser.y"
            { erm_nt(((*yyvaluep).non_terminal)); }
#line 1770 "y.tab.c"
        break;

    case YYSYMBOL_program: /* program  */
#line 132 "1905072_parser.y"
            { erm_nt(((*yyvaluep).non_terminal)); }
#line 1776 "y.tab.c"
        break;

    case YYSYMBOL_unit: /* unit  */
#line 132 "1905072_parser.y"
            { erm_nt(((*yyvaluep).non_terminal)); }
#line 1782 "y.tab.c"
        break;

    case YYSYMBOL_func_declaration: /* func_declaration  */
#line 132 "1905072_parser.y"
            { erm_nt(((*yyvaluep).non_terminal)); }
#line 1788 "y.tab.c"
        break;

    case YYSYMBOL_func_definition: /* func_definition  */
#line 132 "1905072_parser.y"
            { erm_nt(((*yyvaluep).non_terminal)); }
#line 1794 "y.tab.c"
        break;

    case YYSYMBOL_compound_statement: /* compound_statement  */
#line 132 "1905072_parser.y"
            { erm_nt(((*yyvaluep).non_terminal)); }
#line 1800 "y.tab.c"
        break;

    case YYSYMBOL_var_declaration: /* var_declaration  */
#line 132 "1905072_parser.y"
            { erm_nt(((*yyvaluep).non_terminal)); }
#line 1806 "y.tab.c"
        break;

    case YYSYMBOL_type_specifier: /* type_specifier  */
#line 132 "1905072_parser.y"
            { erm_nt(((*yyvaluep).non_terminal)); }
#line 1812 "y.tab.c"
        break;

    case YYSYMBOL_statements: /* statements  */
#line 132 "1905072_parser.y"
            { erm_nt(((*yyvaluep).non_terminal)); }
#line 1818 "y.tab.c"
        break;

    case YYSYMBOL_statement: /* statement  */
#line 132 "1905072_parser.y"
            { erm_nt(((*yyvaluep).non_terminal)); }
#line 1824 "y.tab.c"
        break;

    case YYSYMBOL_expression_statement: /* expression_statement  */
#line 132 "1905072_parser.y"
            { erm_nt(((*yyvaluep).non_terminal)); }
#line 1830 "y.tab.c"
        break;

    case YYSYMBOL_variable: /* variable  */
#line 133 "1905072_parser.y"
            { erm_e(((*yyvaluep).expression));  }
#line 1836 "y.tab.c"
        break;

    case YYSYMBOL_expression: /* expression  */
#line 133 "1905072_parser.y"
            { erm_e(((*yyvaluep).expression));  }
#line 1842 "y.tab.c"
        break;

    case YYSYMBOL_logic_expression: /* logic_expression  */
#line 133 "1905072_parser.y"
            { erm_e(((*yyvaluep).expression));  }
#line 1848 "y.tab.c"
        break;

    case YYSYMBOL_rel_expression: /* rel_expression  */
#line 133 "1905072_parser.y"
            { erm_e(((*yyvaluep).expression));  }
#line 1854 "y.tab.c"
        break;

    case YYSYMBOL_simple_expression: /* simple_expression  */
#line 133 "1905072_parser.y"
            { erm_e(((*yyvaluep).expression));  }
#line 1860 "y.tab.c"
        break;

    case YYSYMBOL_term: /* term  */
#line 133 "1905072_parser.y"
            { erm_e(((*yyvaluep).expression));  }
#line 1866 "y.tab.c"
        break;

    case YYSYMBOL_unary_expression: /* unary_expression  */
#line 133 "1905072_parser.y"
            { erm_e(((*yyvaluep).expression));  }
#line 1872 "y.tab.c"
        break;

    case YYSYMBOL_factor: /* factor  */
#line 133 "1905072_parser.y"
            { erm_e(((*yyvaluep).expression));  }
#line 1878 "y.tab.c"
        break;

    case YYSYMBOL_constant: /* constant  */
#line 133 "1905072_parser.y"
            { erm_e(((*yyvaluep).expression));  }
#line 1884 "y.tab.c"
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
#line 152 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"start");
							if( error_count == 0) asm_gen->endCode();
							cout<<"Code compiled successfully"<<endl;
							freeMemory(child);
						}
#line 2163 "y.tab.c"
    break;

  case 3: /* program: program unit  */
#line 162 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-1].non_terminal),(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"program");
							freeMemory(child);			 
						}
#line 2173 "y.tab.c"
    break;

  case 4: /* program: unit  */
#line 168 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"program");
							freeMemory(child);
						}
#line 2183 "y.tab.c"
    break;

  case 5: /* unit: var_declaration  */
#line 176 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"unit");
							freeMemory(child);
						}
#line 2193 "y.tab.c"
    break;

  case 6: /* unit: func_declaration  */
#line 182 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"unit");
							freeMemory(child);
						}
#line 2203 "y.tab.c"
    break;

  case 7: /* unit: func_definition  */
#line 188 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"unit");
							freeMemory(child);
						}
#line 2213 "y.tab.c"
    break;

  case 8: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON  */
#line 197 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-5].non_terminal),(yyvsp[-4].terminal),(yyvsp[-3].terminal),(yyvsp[-2].params),(yyvsp[-1].terminal),(yyvsp[0].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"func_declaration");
							sem_anlz->declareFunction((yyvsp[-5].non_terminal)->getSymbol(),(yyvsp[-4].terminal)->getSymbol(),(yyvsp[-2].params)->getParams());
							// freeArrayMemory(params);
							freeMemory(child);
						}
#line 2225 "y.tab.c"
    break;

  case 9: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN error  */
#line 205 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-5].non_terminal),(yyvsp[-4].terminal),(yyvsp[-3].terminal),(yyvsp[-2].params),(yyvsp[-1].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"func_declaration");
							sem_anlz->declareFunction((yyvsp[-5].non_terminal)->getSymbol(),(yyvsp[-4].terminal)->getSymbol(),(yyvsp[-2].params)->getParams());	
							// freeArrayMemory(params);
							freeMemory(child);
						}
#line 2237 "y.tab.c"
    break;

  case 10: /* func_declaration: type_specifier ID LPAREN parameter_list error RPAREN SEMICOLON  */
#line 213 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-6].non_terminal),(yyvsp[-5].terminal),(yyvsp[-4].terminal),(yyvsp[-3].params),(yyvsp[-1].terminal),(yyvsp[0].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"func_declaration");
							sem_anlz->declareFunction((yyvsp[-6].non_terminal)->getSymbol(),(yyvsp[-5].terminal)->getSymbol(),(yyvsp[-3].params)->getParams());
							// freeArrayMemory(params);
							freeMemory(child);
						}
#line 2249 "y.tab.c"
    break;

  case 11: /* func_declaration: type_specifier ID LPAREN parameter_list error RPAREN error  */
#line 221 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-6].non_terminal),(yyvsp[-5].terminal),(yyvsp[-4].terminal),(yyvsp[-3].params),(yyvsp[-1].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"func_declaration");
							sem_anlz->declareFunction((yyvsp[-6].non_terminal)->getSymbol(),(yyvsp[-5].terminal)->getSymbol(),(yyvsp[-3].params)->getParams());
							// freeArrayMemory(params);
							freeMemory(child);
						}
#line 2261 "y.tab.c"
    break;

  case 12: /* func_declaration: type_specifier ID LPAREN RPAREN SEMICOLON  */
#line 229 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-4].non_terminal),(yyvsp[-3].terminal),(yyvsp[-2].terminal),(yyvsp[-1].terminal),(yyvsp[0].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"func_declaration");
							sem_anlz->declareFunction((yyvsp[-4].non_terminal)->getSymbol(),(yyvsp[-3].terminal)->getSymbol(),{});
							// freeArrayMemory(params);
							freeMemory(child);
						}
#line 2273 "y.tab.c"
    break;

  case 13: /* func_declaration: type_specifier ID LPAREN RPAREN error  */
#line 237 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-4].non_terminal),(yyvsp[-3].terminal),(yyvsp[-2].terminal),(yyvsp[-1].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"func_declaration");
							sem_anlz->declareFunction((yyvsp[-4].non_terminal)->getSymbol(),(yyvsp[-3].terminal)->getSymbol(),{});
							// freeArrayMemory(params);
							freeMemory(child);
						}
#line 2285 "y.tab.c"
    break;

  case 14: /* func_declaration: type_specifier ID LPAREN error RPAREN SEMICOLON  */
#line 245 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-5].non_terminal),(yyvsp[-4].terminal),(yyvsp[-3].terminal),(yyvsp[-1].terminal),(yyvsp[0].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"func_declaration");
							sem_anlz->declareFunction((yyvsp[-5].non_terminal)->getSymbol(),(yyvsp[-4].terminal)->getSymbol(),{});
							// freeArrayMemory(params);
							freeMemory(child);
						}
#line 2297 "y.tab.c"
    break;

  case 15: /* func_declaration: type_specifier ID LPAREN error RPAREN SEMICOLON error  */
#line 253 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-6].non_terminal),(yyvsp[-5].terminal),(yyvsp[-4].terminal),(yyvsp[-2].terminal),(yyvsp[-1].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"func_declaration");
							sem_anlz->declareFunction((yyvsp[-6].non_terminal)->getSymbol(),(yyvsp[-5].terminal)->getSymbol(),{});
							// freeArrayMemory(params);
							freeMemory(child);
						}
#line 2309 "y.tab.c"
    break;

  case 16: /* $@1: %empty  */
#line 264 "1905072_parser.y"
                                                {
							//asm_gen->addComment($1->getSymbol()+" "+$2->getSymbol()+"("+$4->getSymbol()+")");
							sem_anlz->defineFunction((yyvsp[-4].non_terminal)->getSymbol(),(yyvsp[-3].terminal)->getSymbol(), (yyvsp[-1].params)->getParams());
						}
#line 2318 "y.tab.c"
    break;

  case 17: /* func_definition: type_specifier ID LPAREN parameter_list RPAREN $@1 compound_statement  */
#line 269 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-6].non_terminal),(yyvsp[-5].terminal),(yyvsp[-4].terminal),(yyvsp[-3].params),(yyvsp[-2].terminal),(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"func_definition");
							// in_function = false;
							// freeArrayMemory(params);
							sem_anlz->endFunction();
							asm_gen->endFunction((yyvsp[-5].terminal)->getSymbol());
							freeMemory(child);
						}
#line 2332 "y.tab.c"
    break;

  case 18: /* $@2: %empty  */
#line 279 "1905072_parser.y"
                                                {
							sem_anlz->defineFunction((yyvsp[-5].non_terminal)->getSymbol(),(yyvsp[-4].terminal)->getSymbol(), (yyvsp[-2].params)->getParams());
						}
#line 2340 "y.tab.c"
    break;

  case 19: /* func_definition: type_specifier ID LPAREN parameter_list error RPAREN $@2 compound_statement  */
#line 283 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-7].non_terminal),(yyvsp[-6].terminal),(yyvsp[-5].terminal),(yyvsp[-4].params),(yyvsp[-2].terminal),(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"func_definition");
							// in_function = false;
							// freeArrayMemory(params);
							sem_anlz->endFunction();
							freeMemory(child);
						}
#line 2353 "y.tab.c"
    break;

  case 20: /* $@3: %empty  */
#line 292 "1905072_parser.y"
                                                {
							//asm_gen->addComment($1->getSymbol()+" "+$2->getSymbol()+"()");
							sem_anlz->defineFunction((yyvsp[-3].non_terminal)->getSymbol(),(yyvsp[-2].terminal)->getSymbol(), vector<Variable*>());
						}
#line 2362 "y.tab.c"
    break;

  case 21: /* func_definition: type_specifier ID LPAREN RPAREN $@3 compound_statement  */
#line 297 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-5].non_terminal),(yyvsp[-4].terminal),(yyvsp[-3].terminal),(yyvsp[-2].terminal),(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"func_definition");
							// in_function = false;
							// freeArrayMemory(params);
							sem_anlz->endFunction();
							asm_gen->endFunction((yyvsp[-4].terminal)->getSymbol());
							
							freeMemory(child);
						}
#line 2377 "y.tab.c"
    break;

  case 22: /* $@4: %empty  */
#line 308 "1905072_parser.y"
                                                {
							sem_anlz->defineFunction((yyvsp[-4].non_terminal)->getSymbol(),(yyvsp[-3].terminal)->getSymbol(), vector<Variable*>());
						}
#line 2385 "y.tab.c"
    break;

  case 23: /* func_definition: type_specifier ID LPAREN error RPAREN $@4 compound_statement  */
#line 312 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-6].non_terminal),(yyvsp[-5].terminal),(yyvsp[-4].terminal),(yyvsp[-2].terminal),(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"func_definition");
							// in_function = false;
							// freeArrayMemory(params);
							sem_anlz->endFunction();
							freeMemory(child);
						}
#line 2398 "y.tab.c"
    break;

  case 24: /* parameter_list: parameter_list COMMA type_specifier ID  */
#line 324 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-3].params),(yyvsp[-2].terminal),(yyvsp[-1].non_terminal),(yyvsp[0].terminal)};
							(yyval.params) = createParameterList(child,"parameter_list");

							(yyval.params)->addParams((yyvsp[-3].params));
							(yyval.params)->addParam((yyvsp[-1].non_terminal)->getSymbol(),(yyvsp[0].terminal)->getSymbol());
							freeMemory(child);
						}
#line 2411 "y.tab.c"
    break;

  case 25: /* parameter_list: parameter_list error COMMA type_specifier ID  */
#line 333 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-4].params),(yyvsp[-2].terminal),(yyvsp[-1].non_terminal),(yyvsp[0].terminal)};
							(yyval.params) = createParameterList(child,"parameter_list");

							(yyval.params)->addParams((yyvsp[-4].params));
							(yyval.params)->addParam((yyvsp[-1].non_terminal)->getSymbol(),(yyvsp[0].terminal)->getSymbol());
							freeMemory(child);
						}
#line 2424 "y.tab.c"
    break;

  case 26: /* parameter_list: parameter_list COMMA type_specifier  */
#line 342 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-2].params),(yyvsp[-1].terminal),(yyvsp[0].non_terminal)};
							(yyval.params) = createParameterList(child,"parameter_list");

							(yyval.params)->addParams((yyvsp[-2].params));
							(yyval.params)->addParam((yyvsp[0].non_terminal)->getSymbol());
							freeMemory(child);
						}
#line 2437 "y.tab.c"
    break;

  case 27: /* parameter_list: parameter_list error COMMA type_specifier  */
#line 351 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-3].params),(yyvsp[-1].terminal),(yyvsp[0].non_terminal)};
							(yyval.params) = createParameterList(child,"parameter_list");

							(yyval.params)->addParams((yyvsp[-3].params));
							(yyval.params)->addParam((yyvsp[0].non_terminal)->getSymbol());
							freeMemory(child);
						}
#line 2450 "y.tab.c"
    break;

  case 28: /* parameter_list: type_specifier ID  */
#line 360 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-1].non_terminal),(yyvsp[0].terminal)};
							(yyval.params) = createParameterList(child,"parameter_list");

							(yyval.params)->addParam((yyvsp[-1].non_terminal)->getSymbol(),(yyvsp[0].terminal)->getSymbol());
							freeMemory(child);
						}
#line 2462 "y.tab.c"
    break;

  case 29: /* parameter_list: type_specifier  */
#line 368 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].non_terminal)};
							(yyval.params) = createParameterList(child,"parameter_list");

							(yyval.params)->addParam((yyvsp[0].non_terminal)->getSymbol());
							freeMemory(child);
						}
#line 2474 "y.tab.c"
    break;

  case 30: /* compound_statement: LCURL create_scope statements RCURL  */
#line 378 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-3].terminal),(yyvsp[-1].non_terminal),(yyvsp[0].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"compound_statement");
							table->printAllScope();
							table->exitScope();
							freeMemory(child);
						}
#line 2486 "y.tab.c"
    break;

  case 31: /* compound_statement: LCURL create_scope statements error RCURL  */
#line 386 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-4].terminal),(yyvsp[-2].non_terminal),(yyvsp[0].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"compound_statement");
							table->printAllScope();
							table->exitScope();
							freeMemory(child);
						}
#line 2498 "y.tab.c"
    break;

  case 32: /* compound_statement: LCURL create_scope error statements RCURL  */
#line 394 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-4].terminal),(yyvsp[-1].non_terminal),(yyvsp[0].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"compound_statement");
							table->printAllScope();
							table->exitScope();
							freeMemory(child);
						}
#line 2510 "y.tab.c"
    break;

  case 33: /* compound_statement: LCURL create_scope RCURL  */
#line 402 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-2].terminal),(yyvsp[0].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"compound_statement");
							table->printAllScope();
							table->exitScope();
							freeMemory(child);
						}
#line 2522 "y.tab.c"
    break;

  case 34: /* compound_statement: LCURL create_scope error RCURL  */
#line 410 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-3].terminal),(yyvsp[0].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"compound_statement");
							table->printAllScope();
							table->exitScope();
							freeMemory(child);
						}
#line 2534 "y.tab.c"
    break;

  case 35: /* create_scope: %empty  */
#line 421 "1905072_parser.y"
                                                { 
							table->enterScope(); 
							if(in_function)
							{	
								sem_anlz->declareFunctionParams();
								asm_gen->createFunctionScope();	
								in_function = false;
							}
						}
#line 2548 "y.tab.c"
    break;

  case 36: /* var_declaration: type_specifier declaration_list SEMICOLON  */
#line 433 "1905072_parser.y"
                                                { 				
							vector<SymbolInfo*> child = {(yyvsp[-2].non_terminal),(yyvsp[-1].vars),(yyvsp[0].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"var_declaration");

							//asm_gen->addComment($$->getSymbol());
							sem_anlz->declareVariables((yyvsp[-2].non_terminal)->getSymbol(),(yyvsp[-1].vars)->getSymbol(),(yyvsp[-1].vars)->getDeclarations());
							// freeArrayMemory(vars);
							freeMemory(child);
						}
#line 2562 "y.tab.c"
    break;

  case 37: /* var_declaration: type_specifier declaration_list error SEMICOLON  */
#line 443 "1905072_parser.y"
                                                { 			
							vector<SymbolInfo*> child = {(yyvsp[-3].non_terminal),(yyvsp[-2].vars),(yyvsp[0].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"var_declaration");
							sem_anlz->declareVariables((yyvsp[-3].non_terminal)->getSymbol(),(yyvsp[-2].vars)->getSymbol(),(yyvsp[-2].vars)->getDeclarations());
							// freeArrayMemory(vars);
							freeMemory(child);
						}
#line 2574 "y.tab.c"
    break;

  case 38: /* type_specifier: INT  */
#line 454 "1905072_parser.y"
                                                { 
							vector<SymbolInfo*> child = {(yyvsp[0].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"type_specifier");
							freeMemory(child);
						}
#line 2584 "y.tab.c"
    break;

  case 39: /* type_specifier: FLOAT  */
#line 460 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"type_specifier");
							freeMemory(child);
						}
#line 2594 "y.tab.c"
    break;

  case 40: /* type_specifier: VOID  */
#line 466 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"type_specifier");
							freeMemory(child);
						}
#line 2604 "y.tab.c"
    break;

  case 41: /* declaration_list: declaration_list COMMA ID  */
#line 475 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-2].vars),(yyvsp[-1].terminal),(yyvsp[0].terminal)};
							(yyval.vars) = createDeclarationList(child,"declaration_list");
							
							(yyval.vars)->addVariables((yyvsp[-2].vars));
							(yyval.vars)->addVariable((yyvsp[0].terminal)->getSymbol());

							freeMemory(child);
						}
#line 2618 "y.tab.c"
    break;

  case 42: /* declaration_list: declaration_list error COMMA ID  */
#line 485 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-3].vars),(yyvsp[-1].terminal),(yyvsp[0].terminal)};
							(yyval.vars) = createDeclarationList(child,"declaration_list");

							(yyval.vars)->addVariables((yyvsp[-3].vars));
							(yyval.vars)->addVariable((yyvsp[0].terminal)->getSymbol());
							freeMemory(child);
						}
#line 2631 "y.tab.c"
    break;

  case 43: /* declaration_list: declaration_list COMMA ID LTHIRD constant RTHIRD  */
#line 494 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-5].vars),(yyvsp[-4].terminal),(yyvsp[-3].terminal),(yyvsp[-2].terminal),(yyvsp[-1].expression),(yyvsp[0].terminal)};
							(yyval.vars) = createDeclarationList(child,"declaration_list");

							if((yyvsp[-1].expression)->getDataType()=="float")
							{
								err_hndlr->handleSemanticError(INVALID_ARRAY_SIZE, line_count, (yyvsp[-1].expression)->getSymbol());
							}

							(yyval.vars)->addVariables((yyvsp[-5].vars));
							(yyval.vars)->addArray((yyvsp[-3].terminal)->getSymbol(),(yyvsp[-1].expression)->getSymbol());

							freeMemory(child);
						}
#line 2650 "y.tab.c"
    break;

  case 44: /* declaration_list: declaration_list error COMMA ID LTHIRD constant RTHIRD  */
#line 509 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-6].vars),(yyvsp[-4].terminal),(yyvsp[-3].terminal),(yyvsp[-2].terminal),(yyvsp[-1].expression),(yyvsp[0].terminal)};
							(yyval.vars) = createDeclarationList(child,"declaration_list");

							if((yyvsp[-1].expression)->getDataType() == "float")
							{
								err_hndlr->handleSemanticError(INVALID_ARRAY_SIZE, line_count, (yyvsp[-1].expression)->getSymbol());
							}

							(yyval.vars)->addVariables((yyvsp[-6].vars));
							(yyval.vars)->addArray((yyvsp[-3].terminal)->getSymbol(),(yyvsp[-1].expression)->getSymbol());

							freeMemory(child);
						}
#line 2669 "y.tab.c"
    break;

  case 45: /* declaration_list: ID  */
#line 524 "1905072_parser.y"
                                                { 
							vector<SymbolInfo*> child = {(yyvsp[0].terminal)};
							(yyval.vars) = createDeclarationList(child,"declaration_list");
							
							
							(yyval.vars)->addVariable((yyvsp[0].terminal)->getSymbol());

							freeMemory(child);
						}
#line 2683 "y.tab.c"
    break;

  case 46: /* declaration_list: ID LTHIRD constant RTHIRD  */
#line 534 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-3].terminal),(yyvsp[-2].terminal),(yyvsp[-1].expression),(yyvsp[0].terminal)};
							(yyval.vars) = createDeclarationList(child,"declaration_list");

							if((yyvsp[-1].expression)->getDataType()=="float")
							{
								err_hndlr->handleSemanticError(INVALID_ARRAY_SIZE, line_count, (yyvsp[-1].expression)->getSymbol());
							}

							(yyval.vars)->addArray((yyvsp[-3].terminal)->getSymbol(),(yyvsp[-1].expression)->getSymbol());
							freeMemory(child);
						}
#line 2700 "y.tab.c"
    break;

  case 47: /* statements: statement  */
#line 549 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"statements");
							asm_gen->resetTmpVar();
							freeMemory(child);
						}
#line 2711 "y.tab.c"
    break;

  case 48: /* statements: statements statement  */
#line 556 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-1].non_terminal),(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"statements");
							asm_gen->resetTmpVar();
							freeMemory(child);
						}
#line 2722 "y.tab.c"
    break;

  case 49: /* statements: statements error statement  */
#line 563 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-2].non_terminal),(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"statements");
							freeMemory(child);
						}
#line 2732 "y.tab.c"
    break;

  case 50: /* statement: var_declaration  */
#line 571 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"statement");
							freeMemory(child);
						}
#line 2742 "y.tab.c"
    break;

  case 51: /* statement: func_definition  */
#line 576 "1905072_parser.y"
                                                                  {
							vector<SymbolInfo*> child = {(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"statement");
							err_hndlr->handleSemanticError(NESTED_FUNCTION, line_count);
							freeMemory(child);
						}
#line 2753 "y.tab.c"
    break;

  case 52: /* statement: func_declaration  */
#line 582 "1905072_parser.y"
                                                                   {
							vector<SymbolInfo*> child = {(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"statement");
							err_hndlr->handleSemanticError(NESTED_FUNCTION, line_count);
							freeMemory(child);
						}
#line 2764 "y.tab.c"
    break;

  case 53: /* statement: expression_statement  */
#line 589 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"statement");
							freeMemory(child);
						}
#line 2774 "y.tab.c"
    break;

  case 54: /* statement: compound_statement  */
#line 595 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"statement");
							freeMemory(child);
						}
#line 2784 "y.tab.c"
    break;

  case 55: /* $@5: %empty  */
#line 601 "1905072_parser.y"
                                                { 
							asm_gen->forLoopStart(); 
						}
#line 2792 "y.tab.c"
    break;

  case 56: /* $@6: %empty  */
#line 605 "1905072_parser.y"
                                                { 
							asm_gen->gotoNextStepInForLoop(); 
						}
#line 2800 "y.tab.c"
    break;

  case 57: /* statement: FOR LPAREN expression_statement $@5 expression_statement expression $@6 RPAREN statement  */
#line 609 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-8].terminal),(yyvsp[-7].terminal),(yyvsp[-6].non_terminal),(yyvsp[-4].non_terminal),(yyvsp[-3].expression),(yyvsp[-1].terminal),(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"statement");
							asm_gen->endForLoop();
							freeMemory(child);
						}
#line 2811 "y.tab.c"
    break;

  case 58: /* statement: IF LPAREN expression RPAREN create_if_block statement  */
#line 617 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-5].terminal),(yyvsp[-4].terminal),(yyvsp[-3].expression),(yyvsp[-2].terminal),(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"statement");
							asm_gen->endIfBlock();
							freeMemory(child);
						}
#line 2822 "y.tab.c"
    break;

  case 59: /* $@7: %empty  */
#line 625 "1905072_parser.y"
                                                { 
							// //asm_gen->addComment("else");
							asm_gen->createElseBlock(); 
						}
#line 2831 "y.tab.c"
    break;

  case 60: /* statement: IF LPAREN expression RPAREN create_if_block statement ELSE $@7 statement  */
#line 630 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-8].terminal),(yyvsp[-7].terminal),(yyvsp[-6].expression),(yyvsp[-5].terminal),(yyvsp[-3].non_terminal),(yyvsp[-2].terminal),(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"statement");
							asm_gen->endIfElseBlock();
							freeMemory(child);
						}
#line 2842 "y.tab.c"
    break;

  case 61: /* $@8: %empty  */
#line 637 "1905072_parser.y"
                                                { 
							//asm_gen->addComment($1->getSymbol());
							asm_gen->whileLoopStart(); 
						}
#line 2851 "y.tab.c"
    break;

  case 62: /* $@9: %empty  */
#line 642 "1905072_parser.y"
                                                { 
							//asm_gen->addComment($4->getSymbol());
							asm_gen->whileLoopConditionCheck((yyvsp[0].expression)); 
						}
#line 2860 "y.tab.c"
    break;

  case 63: /* statement: WHILE $@8 LPAREN expression $@9 RPAREN statement  */
#line 647 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-6].terminal),(yyvsp[-4].terminal),(yyvsp[-3].expression),(yyvsp[-1].terminal),(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"statement");
							asm_gen->endWhileLoop();
							freeMemory(child);
						}
#line 2871 "y.tab.c"
    break;

  case 64: /* statement: PRINTLN LPAREN ID RPAREN SEMICOLON  */
#line 654 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-4].terminal),(yyvsp[-3].terminal),(yyvsp[-2].terminal),(yyvsp[-1].terminal),(yyvsp[0].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"statement");	
							Identifier* id = (Identifier*)table->search((yyvsp[-2].terminal)->getSymbol());	
							if(id == NULL)
							{
								err_hndlr->handleSemanticError(UNDECLARED_VARIABLE, line_count, (yyvsp[-2].terminal)->getSymbol());
							}
							else if(id->getIdentity()=="FUNCTION")
							{
								err_hndlr->handleSemanticError(UNDECLARED_VARIABLE, line_count, (yyvsp[-2].terminal)->getSymbol());
							}
							else
							{
								Variable*  var = (Variable*) id;
								//asm_gen->addComment($$->getSymbol());
								asm_gen->printId(var);
							}
							freeMemory(child);
						}
#line 2896 "y.tab.c"
    break;

  case 65: /* statement: RETURN expression SEMICOLON  */
#line 675 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-2].terminal),(yyvsp[-1].expression),(yyvsp[0].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"statement");
							sem_anlz->returnFunction((yyvsp[-1].expression));
							//asm_gen->addComment($$->getSymbol());
							asm_gen->returnFunction((yyvsp[-1].expression));
							freeMemory(child);
						}
#line 2909 "y.tab.c"
    break;

  case 66: /* statement: RETURN SEMICOLON  */
#line 683 "1905072_parser.y"
                                                                   {
							// New rule
							vector<SymbolInfo*> child = {(yyvsp[-1].terminal),(yyvsp[0].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"statement");
							//asm_gen->addComment($$->getSymbol());
							asm_gen->returnFunction();
							freeMemory(child);
						}
#line 2922 "y.tab.c"
    break;

  case 67: /* create_if_block: %empty  */
#line 695 "1905072_parser.y"
                                                {
							asm_gen->createIfBlock(last_exp);
						}
#line 2930 "y.tab.c"
    break;

  case 68: /* expression_statement: SEMICOLON  */
#line 700 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"expression_statement");
							freeMemory(child);
						}
#line 2940 "y.tab.c"
    break;

  case 69: /* expression_statement: expression SEMICOLON  */
#line 706 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-1].expression),(yyvsp[0].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"expression_statement");
							asm_gen->forLoopConditionCheck((yyvsp[-1].expression));
							freeMemory(child);
						}
#line 2951 "y.tab.c"
    break;

  case 70: /* variable: ID  */
#line 715 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].terminal)};
							(yyval.expression) = createExpression(child,"variable");
							(yyval.expression)->setDataType(sem_anlz->callVariable((yyvsp[0].terminal)->getSymbol()));
							if((yyval.expression)->getDataType()!="NULL")
							{
								(yyval.expression)->setTmpVar(asm_gen->callVariable((yyvsp[0].terminal)->getSymbol()));
							}
							freeMemory(child);
						}
#line 2966 "y.tab.c"
    break;

  case 71: /* variable: ID LTHIRD expression RTHIRD  */
#line 726 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-3].terminal),(yyvsp[-2].terminal),(yyvsp[-1].expression),(yyvsp[0].terminal)};
							(yyval.expression) = createArrayCall(child,"variable");

							(yyval.expression)->setDataType(sem_anlz->callArray((yyvsp[-3].terminal)->getSymbol(),(yyvsp[-1].expression)));
							if((yyval.expression)->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								// $3->setTmpVar(asm_gen->evaluateArrayIndex($3));
								(yyval.expression)->setTmpVar(asm_gen->callArray((yyvsp[-3].terminal)->getSymbol(),(yyvsp[-1].expression)));
								((ArrayCall*)(yyval.expression))->setIndex((yyvsp[-1].expression)->getTmpVar());
							}
							// logout<<$$->getExpression()<<" "<<line_count<<endl;
							freeMemory(child);
						}
#line 2986 "y.tab.c"
    break;

  case 72: /* expression: logic_expression  */
#line 744 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].expression)};
							
							(yyval.expression) = createExpression(child,"expression");
							(yyval.expression)->setDataType((yyvsp[0].expression)->getDataType());
							(yyval.expression)->setTmpVar((yyvsp[0].expression)->getTmpVar());

							last_exp = new Expression((yyvsp[0].expression)); // For IF condition
							
							freeMemory(child);
						}
#line 3002 "y.tab.c"
    break;

  case 73: /* expression: variable ASSIGNOP logic_expression  */
#line 756 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-2].expression),(yyvsp[-1].terminal),(yyvsp[0].expression)};
							(yyval.expression) = createExpression(child,"expression");
							(yyval.expression)->setDataType(sem_anlz->assignOp((yyvsp[-2].expression),(yyvsp[0].expression)));
							if((yyval.expression)->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								(yyval.expression)->setTmpVar(asm_gen->assignOp((yyvsp[-2].expression),(yyvsp[0].expression)));
							}
							freeMemory(child);
						}
#line 3018 "y.tab.c"
    break;

  case 74: /* logic_expression: rel_expression  */
#line 770 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].expression)};
							(yyval.expression) = createExpression(child,"logic_expression");
							(yyval.expression)->setDataType((yyvsp[0].expression)->getDataType());
							(yyval.expression)->setTmpVar((yyvsp[0].expression)->getTmpVar());
							freeMemory(child);
						}
#line 3030 "y.tab.c"
    break;

  case 75: /* logic_expression: rel_expression LOGICOP rel_expression  */
#line 778 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-2].expression),(yyvsp[-1].terminal),(yyvsp[0].expression)};
							(yyval.expression) = createExpression(child,"logic_expression");
							(yyval.expression)->setDataType(sem_anlz->logicOp((yyvsp[-2].expression),(yyvsp[-1].terminal)->getSymbol(),(yyvsp[0].expression)));
							if((yyval.expression)->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								(yyval.expression)->setTmpVar(asm_gen->logicOp((yyvsp[-2].expression),(yyvsp[-1].terminal)->getSymbol(),(yyvsp[0].expression)));
							}
							
							freeMemory(child);
						}
#line 3047 "y.tab.c"
    break;

  case 76: /* rel_expression: simple_expression  */
#line 793 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].expression)};
							(yyval.expression) = createExpression(child,"rel_expression");
							(yyval.expression)->setDataType((yyvsp[0].expression)->getDataType());
							(yyval.expression)->setTmpVar((yyvsp[0].expression)->getTmpVar());
							freeMemory(child);
						}
#line 3059 "y.tab.c"
    break;

  case 77: /* rel_expression: simple_expression RELOP simple_expression  */
#line 801 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-2].expression),(yyvsp[-1].terminal),(yyvsp[0].expression)};
							(yyval.expression) = createExpression(child,"rel_expression");
							(yyval.expression)->setDataType(sem_anlz->relOp((yyvsp[-2].expression),(yyvsp[-1].terminal)->getSymbol(),(yyvsp[0].expression)));
							if((yyval.expression)->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								(yyval.expression)->setTmpVar(asm_gen->relOp((yyvsp[-2].expression),(yyvsp[-1].terminal)->getSymbol(),(yyvsp[0].expression)));
							}
							
							freeMemory(child);
						}
#line 3076 "y.tab.c"
    break;

  case 78: /* simple_expression: term  */
#line 816 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].expression)};
							(yyval.expression) = createExpression(child,"simple_expression");
							(yyval.expression)->setDataType((yyvsp[0].expression)->getDataType());
							(yyval.expression)->setTmpVar((yyvsp[0].expression)->getTmpVar());
							freeMemory(child);
						}
#line 3088 "y.tab.c"
    break;

  case 79: /* simple_expression: simple_expression ADDOP term  */
#line 824 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-2].expression),(yyvsp[-1].terminal),(yyvsp[0].expression)};
							(yyval.expression) = createExpression(child,"simple_expression");

							(yyval.expression)->setDataType(sem_anlz->addOp((yyvsp[-2].expression),(yyvsp[-1].terminal)->getSymbol(),(yyvsp[0].expression)));
							if((yyval.expression)->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								(yyval.expression)->setTmpVar(asm_gen->addOp((yyvsp[-2].expression),(yyvsp[-1].terminal)->getSymbol(),(yyvsp[0].expression)));
							}
							
							freeMemory(child);
						}
#line 3106 "y.tab.c"
    break;

  case 80: /* term: unary_expression  */
#line 840 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].expression)};
							(yyval.expression) = createExpression(child,"term");
							(yyval.expression)->setDataType((yyvsp[0].expression)->getDataType());
							(yyval.expression)->setTmpVar((yyvsp[0].expression)->getTmpVar());
							freeMemory(child);
						}
#line 3118 "y.tab.c"
    break;

  case 81: /* term: term MULOP unary_expression  */
#line 848 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-2].expression),(yyvsp[-1].terminal),(yyvsp[0].expression)};
							(yyval.expression) = createExpression(child,"term");

							(yyval.expression)->setDataType(sem_anlz->mulOp((yyvsp[-2].expression),(yyvsp[-1].terminal)->getSymbol(),(yyvsp[0].expression)));
							if((yyval.expression)->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								(yyval.expression)->setTmpVar(asm_gen->mulOp((yyvsp[-2].expression),(yyvsp[-1].terminal)->getSymbol(),(yyvsp[0].expression)));
							}
							
							freeMemory(child);
						}
#line 3136 "y.tab.c"
    break;

  case 82: /* unary_expression: ADDOP unary_expression  */
#line 864 "1905072_parser.y"
                                                { 
							vector<SymbolInfo*> child = {(yyvsp[-1].terminal),(yyvsp[0].expression)};
							(yyval.expression) = createExpression({(yyvsp[-1].terminal),(yyvsp[0].expression)},"unary_expression");
							(yyval.expression)->setDataType((yyvsp[0].expression)->getDataType());
							if((yyval.expression)->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								(yyval.expression)->setTmpVar(asm_gen->unaryOperation((yyvsp[-1].terminal)->getSymbol(), (yyvsp[0].expression)));
							}
							freeMemory(child);
						}
#line 3152 "y.tab.c"
    break;

  case 83: /* unary_expression: NOT unary_expression  */
#line 876 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-1].terminal),(yyvsp[0].expression)};
							(yyval.expression) = createExpression(child,"unary_expression");
							(yyval.expression)->setDataType((yyvsp[0].expression)->getDataType());
							if((yyval.expression)->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								(yyval.expression)->setTmpVar(asm_gen->notOperation((yyvsp[0].expression)));
							}
							freeMemory(child);
						}
#line 3168 "y.tab.c"
    break;

  case 84: /* unary_expression: factor  */
#line 888 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].expression)};
							(yyval.expression) = createExpression(child,"unary_expression");
							(yyval.expression)->setDataType((yyvsp[0].expression)->getDataType());
							(yyval.expression)->setTmpVar((yyvsp[0].expression)->getTmpVar());
							freeMemory(child);
						}
#line 3180 "y.tab.c"
    break;

  case 85: /* factor: variable  */
#line 898 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].expression)};
							(yyval.expression) = createExpression(child,"factor");
							(yyval.expression)->setDataType((yyvsp[0].expression)->getDataType());

							if((yyvsp[0].expression)->getExpType() == "ARRAY_CALL")
							{
								asm_gen->moveIndex((ArrayCall*)(yyvsp[0].expression));
								(yyval.expression)->setTmpVar(asm_gen->arrayToFactor((yyvsp[0].expression)));
							}
							else
							{
								(yyval.expression)->setTmpVar((yyvsp[0].expression)->getTmpVar());
							}
							freeMemory(child);
						}
#line 3201 "y.tab.c"
    break;

  case 86: /* factor: ID LPAREN argument_list RPAREN  */
#line 915 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-3].terminal),(yyvsp[-2].terminal),(yyvsp[-1].args),(yyvsp[0].terminal)};
							(yyval.expression) = createExpression(child,"factor");
							(yyval.expression)->setDataType(sem_anlz->callFunction((yyvsp[-3].terminal)->getSymbol(), (yyvsp[-1].args)->getArgs()));

							if((yyval.expression)->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								(yyval.expression)->setTmpVar(
									asm_gen->callFunction((Function*)table->search((yyvsp[-3].terminal)->getSymbol()),(yyvsp[-1].args)->getArgs())
								);
							}
							

							// freeArrayMemory(args);
							freeMemory(child);
						}
#line 3223 "y.tab.c"
    break;

  case 87: /* factor: LPAREN expression RPAREN  */
#line 933 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-2].terminal),(yyvsp[-1].expression),(yyvsp[0].terminal)};
							(yyval.expression) = createExpression(child,"factor");
							(yyval.expression)->setDataType((yyvsp[-1].expression)->getDataType());
							(yyval.expression)->setTmpVar((yyvsp[-1].expression)->getTmpVar());
							freeMemory(child);
						}
#line 3235 "y.tab.c"
    break;

  case 88: /* factor: CONST_INT  */
#line 941 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].terminal)};
							(yyval.expression) = createExpression(child,"factor");
							(yyval.expression)->setDataType("int");
							(yyval.expression)->setTmpVar((yyvsp[0].terminal)->getSymbol());
							freeMemory(child);
						}
#line 3247 "y.tab.c"
    break;

  case 89: /* factor: CONST_FLOAT  */
#line 949 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].terminal)};
							(yyval.expression) = createExpression(child,"factor");
							(yyval.expression)->setDataType("float");
							(yyval.expression)->setTmpVar((yyvsp[0].terminal)->getSymbol());
							freeMemory(child);
						}
#line 3259 "y.tab.c"
    break;

  case 90: /* factor: variable INCOP  */
#line 957 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-1].expression),(yyvsp[0].terminal)};
							(yyval.expression) = createExpression(child,"factor");
							(yyval.expression)->setDataType((yyvsp[-1].expression)->getDataType());

							if((yyvsp[-1].expression)->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								asm_gen->incrementOperation((yyvsp[-1].expression));
							}	
							(yyval.expression)->setTmpVar((yyvsp[-1].expression)->getTmpVar());
							freeMemory(child);
						}
#line 3277 "y.tab.c"
    break;

  case 91: /* factor: variable DECOP  */
#line 971 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-1].expression),(yyvsp[0].terminal)};
							(yyval.expression) = createExpression(child,"factor");
							(yyval.expression)->setDataType((yyvsp[-1].expression)->getDataType());
							if((yyvsp[-1].expression)->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								asm_gen->decrementOperation((yyvsp[-1].expression));
							}
							(yyval.expression)->setTmpVar((yyvsp[-1].expression)->getTmpVar());
							freeMemory(child);
						}
#line 3294 "y.tab.c"
    break;

  case 92: /* argument_list: arguments  */
#line 986 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].args)};
							(yyval.args) = createArgumentList(child,"argument_list");

							(yyval.args)->addArgs((yyvsp[0].args));
							freeMemory(child);
						}
#line 3306 "y.tab.c"
    break;

  case 93: /* argument_list: %empty  */
#line 994 "1905072_parser.y"
                                                { 
							vector<SymbolInfo*> child = {};
							(yyval.args) = createArgumentList(child,"argument_list");
							freeMemory(child);
						}
#line 3316 "y.tab.c"
    break;

  case 94: /* arguments: arguments COMMA logic_expression  */
#line 1002 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-2].args),(yyvsp[-1].terminal),(yyvsp[0].expression)};
							(yyval.args) = createArgumentList(child,"arguments");

							(yyval.args)->addArgs((yyvsp[-2].args));
							(yyval.args)->addArg((yyvsp[0].expression));
							freeMemory(child);
						}
#line 3329 "y.tab.c"
    break;

  case 95: /* arguments: logic_expression  */
#line 1011 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].expression)};
							(yyval.args) = createArgumentList(child,"arguments");

							(yyval.args)->addArg((yyvsp[0].expression));
							freeMemory(child);
						}
#line 3341 "y.tab.c"
    break;

  case 96: /* constant: CONST_INT  */
#line 1022 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].terminal)};
							(yyval.expression) = createExpression(child,"constant");
							(yyval.expression)->setDataType("int");
							(yyval.expression)->setTmpVar((yyvsp[0].terminal)->getSymbol());
							freeMemory(child);
						}
#line 3353 "y.tab.c"
    break;

  case 97: /* constant: CONST_FLOAT  */
#line 1030 "1905072_parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].terminal)};
							(yyval.expression) = createExpression(child,"constant");
							(yyval.expression)->setDataType("float");
							(yyval.expression)->setTmpVar((yyvsp[0].terminal)->getSymbol());
							freeMemory(child);
						}
#line 3365 "y.tab.c"
    break;


#line 3369 "y.tab.c"

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

#line 1037 "1905072_parser.y"

