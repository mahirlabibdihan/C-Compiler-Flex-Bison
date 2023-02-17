
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
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


/* Line 189 of yacc.c  */
#line 183 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IF = 258,
     ELSE = 259,
     THEN = 260,
     SWITCH = 261,
     CASE = 262,
     DEFAULT = 263,
     FOR = 264,
     DO = 265,
     WHILE = 266,
     INT = 267,
     FLOAT = 268,
     DOUBLE = 269,
     CHAR = 270,
     STRING = 271,
     VOID = 272,
     BREAK = 273,
     RETURN = 274,
     CONTINUE = 275,
     INCOP = 276,
     DECOP = 277,
     ASSIGNOP = 278,
     NOT = 279,
     PRINTLN = 280,
     LPAREN = 281,
     RPAREN = 282,
     LCURL = 283,
     RCURL = 284,
     LTHIRD = 285,
     RTHIRD = 286,
     COMMA = 287,
     SEMICOLON = 288,
     ID = 289,
     CONST_INT = 290,
     CONST_FLOAT = 291,
     CONST_CHAR = 292,
     ADDOP = 293,
     MULOP = 294,
     LOGICOP = 295,
     RELOP = 296
   };
#endif
/* Tokens.  */
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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 112 "1905072_parser.y"

	Terminal *terminal;
	NonTerminal *non_terminal;
	Expression *expression;
	ArgumentList *args;
	ParameterList *params;
	DeclarationList *vars;



/* Line 214 of yacc.c  */
#line 312 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 324 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

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
/* YYNRULES -- Number of states.  */
#define YYNSTATES  162

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   296

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    16,    23,
      30,    38,    46,    52,    58,    65,    73,    74,    82,    83,
      92,    93,   100,   101,   109,   114,   120,   124,   129,   132,
     134,   139,   145,   151,   155,   160,   161,   165,   170,   172,
     174,   176,   180,   185,   192,   200,   202,   207,   209,   212,
     216,   218,   220,   222,   224,   226,   227,   228,   238,   245,
     246,   256,   257,   258,   266,   272,   276,   279,   280,   282,
     285,   287,   292,   294,   298,   300,   304,   306,   310,   312,
     316,   318,   322,   325,   328,   330,   332,   337,   341,   343,
     345,   348,   351,   353,   354,   358,   360,   362
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      43,     0,    -1,    44,    -1,    44,    45,    -1,    45,    -1,
      55,    -1,    46,    -1,    47,    -1,    56,    34,    26,    52,
      27,    33,    -1,    56,    34,    26,    52,    27,     1,    -1,
      56,    34,    26,    52,     1,    27,    33,    -1,    56,    34,
      26,    52,     1,    27,     1,    -1,    56,    34,    26,    27,
      33,    -1,    56,    34,    26,    27,     1,    -1,    56,    34,
      26,     1,    27,    33,    -1,    56,    34,    26,     1,    27,
      33,     1,    -1,    -1,    56,    34,    26,    52,    27,    48,
      53,    -1,    -1,    56,    34,    26,    52,     1,    27,    49,
      53,    -1,    -1,    56,    34,    26,    27,    50,    53,    -1,
      -1,    56,    34,    26,     1,    27,    51,    53,    -1,    52,
      32,    56,    34,    -1,    52,     1,    32,    56,    34,    -1,
      52,    32,    56,    -1,    52,     1,    32,    56,    -1,    56,
      34,    -1,    56,    -1,    28,    54,    58,    29,    -1,    28,
      54,    58,     1,    29,    -1,    28,    54,     1,    58,    29,
      -1,    28,    54,    29,    -1,    28,    54,     1,    29,    -1,
      -1,    56,    57,    33,    -1,    56,    57,     1,    33,    -1,
      12,    -1,    13,    -1,    17,    -1,    57,    32,    34,    -1,
      57,     1,    32,    34,    -1,    57,    32,    34,    30,    77,
      31,    -1,    57,     1,    32,    34,    30,    77,    31,    -1,
      34,    -1,    34,    30,    77,    31,    -1,    59,    -1,    58,
      59,    -1,    58,     1,    59,    -1,    55,    -1,    47,    -1,
      46,    -1,    66,    -1,    53,    -1,    -1,    -1,     9,    26,
      66,    60,    66,    68,    61,    27,    59,    -1,     3,    26,
      68,    27,    65,    59,    -1,    -1,     3,    26,    68,    27,
      65,    59,     4,    62,    59,    -1,    -1,    -1,    11,    63,
      26,    68,    64,    27,    59,    -1,    25,    26,    34,    27,
      33,    -1,    19,    68,    33,    -1,    19,    33,    -1,    -1,
      33,    -1,    68,    33,    -1,    34,    -1,    34,    30,    68,
      31,    -1,    69,    -1,    67,    23,    69,    -1,    70,    -1,
      70,    40,    70,    -1,    71,    -1,    71,    41,    71,    -1,
      72,    -1,    71,    38,    72,    -1,    73,    -1,    72,    39,
      73,    -1,    38,    73,    -1,    24,    73,    -1,    74,    -1,
      67,    -1,    34,    26,    75,    27,    -1,    26,    68,    27,
      -1,    35,    -1,    36,    -1,    67,    21,    -1,    67,    22,
      -1,    76,    -1,    -1,    76,    32,    69,    -1,    69,    -1,
      35,    -1,    36,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
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

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "THEN", "SWITCH", "CASE",
  "DEFAULT", "FOR", "DO", "WHILE", "INT", "FLOAT", "DOUBLE", "CHAR",
  "STRING", "VOID", "BREAK", "RETURN", "CONTINUE", "INCOP", "DECOP",
  "ASSIGNOP", "NOT", "PRINTLN", "LPAREN", "RPAREN", "LCURL", "RCURL",
  "LTHIRD", "RTHIRD", "COMMA", "SEMICOLON", "ID", "CONST_INT",
  "CONST_FLOAT", "CONST_CHAR", "ADDOP", "MULOP", "LOGICOP", "RELOP",
  "$accept", "start", "program", "unit", "func_declaration",
  "func_definition", "$@1", "$@2", "$@3", "$@4", "parameter_list",
  "compound_statement", "create_scope", "var_declaration",
  "type_specifier", "declaration_list", "statements", "statement", "$@5",
  "$@6", "$@7", "$@8", "$@9", "create_if_block", "expression_statement",
  "variable", "expression", "logic_expression", "rel_expression",
  "simple_expression", "term", "unary_expression", "factor",
  "argument_list", "arguments", "constant", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
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

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
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

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
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

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,    78,    79,    49,    58,    33,    42,
      22,    80,    55,    81,    10,    14,    82,    83,   141,   156,
     158,   100,   149,   147,    84,    85,    86,    87,    88,    89,
      90,    91,    92,   130,   131,    26
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -101
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

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -101,  -101,  -101,   166,    63,    66,  -101,  -101,  -101,  -101,
    -101,    34,  -101,    73,    16,  -101,   112,   -77,  -101,  -101,
    -101,  -101,  -101,  -101,   -98,   -59,   -68,  -100,    55,    59,
      56,   -65,  -101,  -101,  -101,   -23
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -21
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

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
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

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {
      case 3: /* "IF" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1417 "y.tab.c"
	break;
      case 4: /* "ELSE" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1426 "y.tab.c"
	break;
      case 5: /* "THEN" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1435 "y.tab.c"
	break;
      case 6: /* "SWITCH" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1444 "y.tab.c"
	break;
      case 7: /* "CASE" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1453 "y.tab.c"
	break;
      case 8: /* "DEFAULT" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1462 "y.tab.c"
	break;
      case 9: /* "FOR" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1471 "y.tab.c"
	break;
      case 10: /* "DO" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1480 "y.tab.c"
	break;
      case 11: /* "WHILE" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1489 "y.tab.c"
	break;
      case 12: /* "INT" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1498 "y.tab.c"
	break;
      case 13: /* "FLOAT" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1507 "y.tab.c"
	break;
      case 14: /* "DOUBLE" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1516 "y.tab.c"
	break;
      case 15: /* "CHAR" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1525 "y.tab.c"
	break;
      case 16: /* "STRING" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1534 "y.tab.c"
	break;
      case 17: /* "VOID" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1543 "y.tab.c"
	break;
      case 18: /* "BREAK" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1552 "y.tab.c"
	break;
      case 19: /* "RETURN" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1561 "y.tab.c"
	break;
      case 20: /* "CONTINUE" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1570 "y.tab.c"
	break;
      case 21: /* "INCOP" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1579 "y.tab.c"
	break;
      case 22: /* "DECOP" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1588 "y.tab.c"
	break;
      case 23: /* "ASSIGNOP" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1597 "y.tab.c"
	break;
      case 24: /* "NOT" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1606 "y.tab.c"
	break;
      case 25: /* "PRINTLN" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1615 "y.tab.c"
	break;
      case 26: /* "LPAREN" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1624 "y.tab.c"
	break;
      case 27: /* "RPAREN" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1633 "y.tab.c"
	break;
      case 28: /* "LCURL" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1642 "y.tab.c"
	break;
      case 29: /* "RCURL" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1651 "y.tab.c"
	break;
      case 30: /* "LTHIRD" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1660 "y.tab.c"
	break;
      case 31: /* "RTHIRD" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1669 "y.tab.c"
	break;
      case 32: /* "COMMA" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1678 "y.tab.c"
	break;
      case 33: /* "SEMICOLON" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1687 "y.tab.c"
	break;
      case 34: /* "ID" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1696 "y.tab.c"
	break;
      case 35: /* "CONST_INT" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1705 "y.tab.c"
	break;
      case 36: /* "CONST_FLOAT" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1714 "y.tab.c"
	break;
      case 37: /* "CONST_CHAR" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1723 "y.tab.c"
	break;
      case 38: /* "ADDOP" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1732 "y.tab.c"
	break;
      case 39: /* "MULOP" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1741 "y.tab.c"
	break;
      case 40: /* "LOGICOP" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1750 "y.tab.c"
	break;
      case 41: /* "RELOP" */

/* Line 1000 of yacc.c  */
#line 131 "1905072_parser.y"
	{ erm_t((yyvaluep->terminal)); };

/* Line 1000 of yacc.c  */
#line 1759 "y.tab.c"
	break;
      case 43: /* "start" */

/* Line 1000 of yacc.c  */
#line 132 "1905072_parser.y"
	{ erm_nt((yyvaluep->non_terminal)); };

/* Line 1000 of yacc.c  */
#line 1768 "y.tab.c"
	break;
      case 44: /* "program" */

/* Line 1000 of yacc.c  */
#line 132 "1905072_parser.y"
	{ erm_nt((yyvaluep->non_terminal)); };

/* Line 1000 of yacc.c  */
#line 1777 "y.tab.c"
	break;
      case 45: /* "unit" */

/* Line 1000 of yacc.c  */
#line 132 "1905072_parser.y"
	{ erm_nt((yyvaluep->non_terminal)); };

/* Line 1000 of yacc.c  */
#line 1786 "y.tab.c"
	break;
      case 46: /* "func_declaration" */

/* Line 1000 of yacc.c  */
#line 132 "1905072_parser.y"
	{ erm_nt((yyvaluep->non_terminal)); };

/* Line 1000 of yacc.c  */
#line 1795 "y.tab.c"
	break;
      case 47: /* "func_definition" */

/* Line 1000 of yacc.c  */
#line 132 "1905072_parser.y"
	{ erm_nt((yyvaluep->non_terminal)); };

/* Line 1000 of yacc.c  */
#line 1804 "y.tab.c"
	break;
      case 53: /* "compound_statement" */

/* Line 1000 of yacc.c  */
#line 132 "1905072_parser.y"
	{ erm_nt((yyvaluep->non_terminal)); };

/* Line 1000 of yacc.c  */
#line 1813 "y.tab.c"
	break;
      case 55: /* "var_declaration" */

/* Line 1000 of yacc.c  */
#line 132 "1905072_parser.y"
	{ erm_nt((yyvaluep->non_terminal)); };

/* Line 1000 of yacc.c  */
#line 1822 "y.tab.c"
	break;
      case 56: /* "type_specifier" */

/* Line 1000 of yacc.c  */
#line 132 "1905072_parser.y"
	{ erm_nt((yyvaluep->non_terminal)); };

/* Line 1000 of yacc.c  */
#line 1831 "y.tab.c"
	break;
      case 58: /* "statements" */

/* Line 1000 of yacc.c  */
#line 132 "1905072_parser.y"
	{ erm_nt((yyvaluep->non_terminal)); };

/* Line 1000 of yacc.c  */
#line 1840 "y.tab.c"
	break;
      case 59: /* "statement" */

/* Line 1000 of yacc.c  */
#line 132 "1905072_parser.y"
	{ erm_nt((yyvaluep->non_terminal)); };

/* Line 1000 of yacc.c  */
#line 1849 "y.tab.c"
	break;
      case 66: /* "expression_statement" */

/* Line 1000 of yacc.c  */
#line 132 "1905072_parser.y"
	{ erm_nt((yyvaluep->non_terminal)); };

/* Line 1000 of yacc.c  */
#line 1858 "y.tab.c"
	break;
      case 67: /* "variable" */

/* Line 1000 of yacc.c  */
#line 133 "1905072_parser.y"
	{ erm_e((yyvaluep->expression));  };

/* Line 1000 of yacc.c  */
#line 1867 "y.tab.c"
	break;
      case 68: /* "expression" */

/* Line 1000 of yacc.c  */
#line 133 "1905072_parser.y"
	{ erm_e((yyvaluep->expression));  };

/* Line 1000 of yacc.c  */
#line 1876 "y.tab.c"
	break;
      case 69: /* "logic_expression" */

/* Line 1000 of yacc.c  */
#line 133 "1905072_parser.y"
	{ erm_e((yyvaluep->expression));  };

/* Line 1000 of yacc.c  */
#line 1885 "y.tab.c"
	break;
      case 70: /* "rel_expression" */

/* Line 1000 of yacc.c  */
#line 133 "1905072_parser.y"
	{ erm_e((yyvaluep->expression));  };

/* Line 1000 of yacc.c  */
#line 1894 "y.tab.c"
	break;
      case 71: /* "simple_expression" */

/* Line 1000 of yacc.c  */
#line 133 "1905072_parser.y"
	{ erm_e((yyvaluep->expression));  };

/* Line 1000 of yacc.c  */
#line 1903 "y.tab.c"
	break;
      case 72: /* "term" */

/* Line 1000 of yacc.c  */
#line 133 "1905072_parser.y"
	{ erm_e((yyvaluep->expression));  };

/* Line 1000 of yacc.c  */
#line 1912 "y.tab.c"
	break;
      case 73: /* "unary_expression" */

/* Line 1000 of yacc.c  */
#line 133 "1905072_parser.y"
	{ erm_e((yyvaluep->expression));  };

/* Line 1000 of yacc.c  */
#line 1921 "y.tab.c"
	break;
      case 74: /* "factor" */

/* Line 1000 of yacc.c  */
#line 133 "1905072_parser.y"
	{ erm_e((yyvaluep->expression));  };

/* Line 1000 of yacc.c  */
#line 1930 "y.tab.c"
	break;
      case 77: /* "constant" */

/* Line 1000 of yacc.c  */
#line 133 "1905072_parser.y"
	{ erm_e((yyvaluep->expression));  };

/* Line 1000 of yacc.c  */
#line 1939 "y.tab.c"
	break;

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 152 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (1)].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"start");
							if( error_count == 0) asm_gen->endCode();
							cout<<"Code compiled successfully"<<endl;
							freeMemory(child);
						}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 162 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (2)].non_terminal),(yyvsp[(2) - (2)].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"program");
							freeMemory(child);			 
						}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 168 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (1)].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"program");
							freeMemory(child);
						}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 176 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (1)].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"unit");
							freeMemory(child);
						}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 182 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (1)].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"unit");
							freeMemory(child);
						}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 188 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (1)].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"unit");
							freeMemory(child);
						}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 197 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (6)].non_terminal),(yyvsp[(2) - (6)].terminal),(yyvsp[(3) - (6)].terminal),(yyvsp[(4) - (6)].params),(yyvsp[(5) - (6)].terminal),(yyvsp[(6) - (6)].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"func_declaration");
							sem_anlz->declareFunction((yyvsp[(1) - (6)].non_terminal)->getSymbol(),(yyvsp[(2) - (6)].terminal)->getSymbol(),(yyvsp[(4) - (6)].params)->getParams());
							// freeArrayMemory(params);
							freeMemory(child);
						}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 205 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (6)].non_terminal),(yyvsp[(2) - (6)].terminal),(yyvsp[(3) - (6)].terminal),(yyvsp[(4) - (6)].params),(yyvsp[(5) - (6)].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"func_declaration");
							sem_anlz->declareFunction((yyvsp[(1) - (6)].non_terminal)->getSymbol(),(yyvsp[(2) - (6)].terminal)->getSymbol(),(yyvsp[(4) - (6)].params)->getParams());	
							// freeArrayMemory(params);
							freeMemory(child);
						}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 213 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (7)].non_terminal),(yyvsp[(2) - (7)].terminal),(yyvsp[(3) - (7)].terminal),(yyvsp[(4) - (7)].params),(yyvsp[(6) - (7)].terminal),(yyvsp[(7) - (7)].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"func_declaration");
							sem_anlz->declareFunction((yyvsp[(1) - (7)].non_terminal)->getSymbol(),(yyvsp[(2) - (7)].terminal)->getSymbol(),(yyvsp[(4) - (7)].params)->getParams());
							// freeArrayMemory(params);
							freeMemory(child);
						}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 221 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (7)].non_terminal),(yyvsp[(2) - (7)].terminal),(yyvsp[(3) - (7)].terminal),(yyvsp[(4) - (7)].params),(yyvsp[(6) - (7)].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"func_declaration");
							sem_anlz->declareFunction((yyvsp[(1) - (7)].non_terminal)->getSymbol(),(yyvsp[(2) - (7)].terminal)->getSymbol(),(yyvsp[(4) - (7)].params)->getParams());
							// freeArrayMemory(params);
							freeMemory(child);
						}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 229 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (5)].non_terminal),(yyvsp[(2) - (5)].terminal),(yyvsp[(3) - (5)].terminal),(yyvsp[(4) - (5)].terminal),(yyvsp[(5) - (5)].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"func_declaration");
							sem_anlz->declareFunction((yyvsp[(1) - (5)].non_terminal)->getSymbol(),(yyvsp[(2) - (5)].terminal)->getSymbol(),{});
							// freeArrayMemory(params);
							freeMemory(child);
						}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 237 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (5)].non_terminal),(yyvsp[(2) - (5)].terminal),(yyvsp[(3) - (5)].terminal),(yyvsp[(4) - (5)].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"func_declaration");
							sem_anlz->declareFunction((yyvsp[(1) - (5)].non_terminal)->getSymbol(),(yyvsp[(2) - (5)].terminal)->getSymbol(),{});
							// freeArrayMemory(params);
							freeMemory(child);
						}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 245 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (6)].non_terminal),(yyvsp[(2) - (6)].terminal),(yyvsp[(3) - (6)].terminal),(yyvsp[(5) - (6)].terminal),(yyvsp[(6) - (6)].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"func_declaration");
							sem_anlz->declareFunction((yyvsp[(1) - (6)].non_terminal)->getSymbol(),(yyvsp[(2) - (6)].terminal)->getSymbol(),{});
							// freeArrayMemory(params);
							freeMemory(child);
						}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 253 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (7)].non_terminal),(yyvsp[(2) - (7)].terminal),(yyvsp[(3) - (7)].terminal),(yyvsp[(5) - (7)].terminal),(yyvsp[(6) - (7)].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"func_declaration");
							sem_anlz->declareFunction((yyvsp[(1) - (7)].non_terminal)->getSymbol(),(yyvsp[(2) - (7)].terminal)->getSymbol(),{});
							// freeArrayMemory(params);
							freeMemory(child);
						}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 264 "1905072_parser.y"
    {
							//asm_gen->addComment($1->getSymbol()+" "+$2->getSymbol()+"("+$4->getSymbol()+")");
							sem_anlz->defineFunction((yyvsp[(1) - (5)].non_terminal)->getSymbol(),(yyvsp[(2) - (5)].terminal)->getSymbol(), (yyvsp[(4) - (5)].params)->getParams());
						}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 269 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (7)].non_terminal),(yyvsp[(2) - (7)].terminal),(yyvsp[(3) - (7)].terminal),(yyvsp[(4) - (7)].params),(yyvsp[(5) - (7)].terminal),(yyvsp[(7) - (7)].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"func_definition");
							// in_function = false;
							// freeArrayMemory(params);
							sem_anlz->endFunction();
							asm_gen->endFunction((yyvsp[(2) - (7)].terminal)->getSymbol());
							freeMemory(child);
						}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 279 "1905072_parser.y"
    {
							sem_anlz->defineFunction((yyvsp[(1) - (6)].non_terminal)->getSymbol(),(yyvsp[(2) - (6)].terminal)->getSymbol(), (yyvsp[(4) - (6)].params)->getParams());
						}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 283 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (8)].non_terminal),(yyvsp[(2) - (8)].terminal),(yyvsp[(3) - (8)].terminal),(yyvsp[(4) - (8)].params),(yyvsp[(6) - (8)].terminal),(yyvsp[(8) - (8)].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"func_definition");
							// in_function = false;
							// freeArrayMemory(params);
							sem_anlz->endFunction();
							freeMemory(child);
						}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 292 "1905072_parser.y"
    {
							//asm_gen->addComment($1->getSymbol()+" "+$2->getSymbol()+"()");
							sem_anlz->defineFunction((yyvsp[(1) - (4)].non_terminal)->getSymbol(),(yyvsp[(2) - (4)].terminal)->getSymbol(), vector<Variable*>());
						}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 297 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (6)].non_terminal),(yyvsp[(2) - (6)].terminal),(yyvsp[(3) - (6)].terminal),(yyvsp[(4) - (6)].terminal),(yyvsp[(6) - (6)].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"func_definition");
							// in_function = false;
							// freeArrayMemory(params);
							sem_anlz->endFunction();
							asm_gen->endFunction((yyvsp[(2) - (6)].terminal)->getSymbol());
							
							freeMemory(child);
						}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 308 "1905072_parser.y"
    {
							sem_anlz->defineFunction((yyvsp[(1) - (5)].non_terminal)->getSymbol(),(yyvsp[(2) - (5)].terminal)->getSymbol(), vector<Variable*>());
						}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 312 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (7)].non_terminal),(yyvsp[(2) - (7)].terminal),(yyvsp[(3) - (7)].terminal),(yyvsp[(5) - (7)].terminal),(yyvsp[(7) - (7)].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"func_definition");
							// in_function = false;
							// freeArrayMemory(params);
							sem_anlz->endFunction();
							freeMemory(child);
						}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 324 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (4)].params),(yyvsp[(2) - (4)].terminal),(yyvsp[(3) - (4)].non_terminal),(yyvsp[(4) - (4)].terminal)};
							(yyval.params) = createParameterList(child,"parameter_list");

							(yyval.params)->addParams((yyvsp[(1) - (4)].params));
							(yyval.params)->addParam((yyvsp[(3) - (4)].non_terminal)->getSymbol(),(yyvsp[(4) - (4)].terminal)->getSymbol());
							freeMemory(child);
						}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 333 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (5)].params),(yyvsp[(3) - (5)].terminal),(yyvsp[(4) - (5)].non_terminal),(yyvsp[(5) - (5)].terminal)};
							(yyval.params) = createParameterList(child,"parameter_list");

							(yyval.params)->addParams((yyvsp[(1) - (5)].params));
							(yyval.params)->addParam((yyvsp[(4) - (5)].non_terminal)->getSymbol(),(yyvsp[(5) - (5)].terminal)->getSymbol());
							freeMemory(child);
						}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 342 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (3)].params),(yyvsp[(2) - (3)].terminal),(yyvsp[(3) - (3)].non_terminal)};
							(yyval.params) = createParameterList(child,"parameter_list");

							(yyval.params)->addParams((yyvsp[(1) - (3)].params));
							(yyval.params)->addParam((yyvsp[(3) - (3)].non_terminal)->getSymbol());
							freeMemory(child);
						}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 351 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (4)].params),(yyvsp[(3) - (4)].terminal),(yyvsp[(4) - (4)].non_terminal)};
							(yyval.params) = createParameterList(child,"parameter_list");

							(yyval.params)->addParams((yyvsp[(1) - (4)].params));
							(yyval.params)->addParam((yyvsp[(4) - (4)].non_terminal)->getSymbol());
							freeMemory(child);
						}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 360 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (2)].non_terminal),(yyvsp[(2) - (2)].terminal)};
							(yyval.params) = createParameterList(child,"parameter_list");

							(yyval.params)->addParam((yyvsp[(1) - (2)].non_terminal)->getSymbol(),(yyvsp[(2) - (2)].terminal)->getSymbol());
							freeMemory(child);
						}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 368 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (1)].non_terminal)};
							(yyval.params) = createParameterList(child,"parameter_list");

							(yyval.params)->addParam((yyvsp[(1) - (1)].non_terminal)->getSymbol());
							freeMemory(child);
						}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 378 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (4)].terminal),(yyvsp[(3) - (4)].non_terminal),(yyvsp[(4) - (4)].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"compound_statement");
							table->printAllScope();
							table->exitScope();
							freeMemory(child);
						}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 386 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (5)].terminal),(yyvsp[(3) - (5)].non_terminal),(yyvsp[(5) - (5)].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"compound_statement");
							table->printAllScope();
							table->exitScope();
							freeMemory(child);
						}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 394 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (5)].terminal),(yyvsp[(4) - (5)].non_terminal),(yyvsp[(5) - (5)].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"compound_statement");
							table->printAllScope();
							table->exitScope();
							freeMemory(child);
						}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 402 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (3)].terminal),(yyvsp[(3) - (3)].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"compound_statement");
							table->printAllScope();
							table->exitScope();
							freeMemory(child);
						}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 410 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (4)].terminal),(yyvsp[(4) - (4)].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"compound_statement");
							table->printAllScope();
							table->exitScope();
							freeMemory(child);
						}
    break;

  case 35:

/* Line 1455 of yacc.c  */
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
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 433 "1905072_parser.y"
    { 				
							vector<SymbolInfo*> child = {(yyvsp[(1) - (3)].non_terminal),(yyvsp[(2) - (3)].vars),(yyvsp[(3) - (3)].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"var_declaration");

							//asm_gen->addComment($$->getSymbol());
							sem_anlz->declareVariables((yyvsp[(1) - (3)].non_terminal)->getSymbol(),(yyvsp[(2) - (3)].vars)->getSymbol(),(yyvsp[(2) - (3)].vars)->getDeclarations());
							// freeArrayMemory(vars);
							freeMemory(child);
						}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 443 "1905072_parser.y"
    { 			
							vector<SymbolInfo*> child = {(yyvsp[(1) - (4)].non_terminal),(yyvsp[(2) - (4)].vars),(yyvsp[(4) - (4)].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"var_declaration");
							sem_anlz->declareVariables((yyvsp[(1) - (4)].non_terminal)->getSymbol(),(yyvsp[(2) - (4)].vars)->getSymbol(),(yyvsp[(2) - (4)].vars)->getDeclarations());
							// freeArrayMemory(vars);
							freeMemory(child);
						}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 454 "1905072_parser.y"
    { 
							vector<SymbolInfo*> child = {(yyvsp[(1) - (1)].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"type_specifier");
							freeMemory(child);
						}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 460 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (1)].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"type_specifier");
							freeMemory(child);
						}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 466 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (1)].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"type_specifier");
							freeMemory(child);
						}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 475 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (3)].vars),(yyvsp[(2) - (3)].terminal),(yyvsp[(3) - (3)].terminal)};
							(yyval.vars) = createDeclarationList(child,"declaration_list");
							
							(yyval.vars)->addVariables((yyvsp[(1) - (3)].vars));
							(yyval.vars)->addVariable((yyvsp[(3) - (3)].terminal)->getSymbol());

							freeMemory(child);
						}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 485 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (4)].vars),(yyvsp[(3) - (4)].terminal),(yyvsp[(4) - (4)].terminal)};
							(yyval.vars) = createDeclarationList(child,"declaration_list");

							(yyval.vars)->addVariables((yyvsp[(1) - (4)].vars));
							(yyval.vars)->addVariable((yyvsp[(4) - (4)].terminal)->getSymbol());
							freeMemory(child);
						}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 494 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (6)].vars),(yyvsp[(2) - (6)].terminal),(yyvsp[(3) - (6)].terminal),(yyvsp[(4) - (6)].terminal),(yyvsp[(5) - (6)].expression),(yyvsp[(6) - (6)].terminal)};
							(yyval.vars) = createDeclarationList(child,"declaration_list");

							if((yyvsp[(5) - (6)].expression)->getDataType()=="float")
							{
								err_hndlr->handleSemanticError(INVALID_ARRAY_SIZE, line_count, (yyvsp[(5) - (6)].expression)->getSymbol());
							}

							(yyval.vars)->addVariables((yyvsp[(1) - (6)].vars));
							(yyval.vars)->addArray((yyvsp[(3) - (6)].terminal)->getSymbol(),(yyvsp[(5) - (6)].expression)->getSymbol());

							freeMemory(child);
						}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 509 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (7)].vars),(yyvsp[(3) - (7)].terminal),(yyvsp[(4) - (7)].terminal),(yyvsp[(5) - (7)].terminal),(yyvsp[(6) - (7)].expression),(yyvsp[(7) - (7)].terminal)};
							(yyval.vars) = createDeclarationList(child,"declaration_list");

							if((yyvsp[(6) - (7)].expression)->getDataType() == "float")
							{
								err_hndlr->handleSemanticError(INVALID_ARRAY_SIZE, line_count, (yyvsp[(6) - (7)].expression)->getSymbol());
							}

							(yyval.vars)->addVariables((yyvsp[(1) - (7)].vars));
							(yyval.vars)->addArray((yyvsp[(4) - (7)].terminal)->getSymbol(),(yyvsp[(6) - (7)].expression)->getSymbol());

							freeMemory(child);
						}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 524 "1905072_parser.y"
    { 
							vector<SymbolInfo*> child = {(yyvsp[(1) - (1)].terminal)};
							(yyval.vars) = createDeclarationList(child,"declaration_list");
							
							
							(yyval.vars)->addVariable((yyvsp[(1) - (1)].terminal)->getSymbol());

							freeMemory(child);
						}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 534 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (4)].terminal),(yyvsp[(2) - (4)].terminal),(yyvsp[(3) - (4)].expression),(yyvsp[(4) - (4)].terminal)};
							(yyval.vars) = createDeclarationList(child,"declaration_list");

							if((yyvsp[(3) - (4)].expression)->getDataType()=="float")
							{
								err_hndlr->handleSemanticError(INVALID_ARRAY_SIZE, line_count, (yyvsp[(3) - (4)].expression)->getSymbol());
							}

							(yyval.vars)->addArray((yyvsp[(1) - (4)].terminal)->getSymbol(),(yyvsp[(3) - (4)].expression)->getSymbol());
							freeMemory(child);
						}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 549 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (1)].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"statements");
							asm_gen->resetTmpVar();
							freeMemory(child);
						}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 556 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (2)].non_terminal),(yyvsp[(2) - (2)].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"statements");
							asm_gen->resetTmpVar();
							freeMemory(child);
						}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 563 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (3)].non_terminal),(yyvsp[(3) - (3)].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"statements");
							freeMemory(child);
						}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 571 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (1)].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"statement");
							freeMemory(child);
						}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 576 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (1)].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"statement");
							err_hndlr->handleSemanticError(NESTED_FUNCTION, line_count);
							freeMemory(child);
						}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 582 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (1)].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"statement");
							err_hndlr->handleSemanticError(NESTED_FUNCTION, line_count);
							freeMemory(child);
						}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 589 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (1)].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"statement");
							freeMemory(child);
						}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 595 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (1)].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"statement");
							freeMemory(child);
						}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 601 "1905072_parser.y"
    { 
							asm_gen->forLoopStart(); 
						}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 605 "1905072_parser.y"
    { 
							asm_gen->gotoNextStepInForLoop(); 
						}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 609 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (9)].terminal),(yyvsp[(2) - (9)].terminal),(yyvsp[(3) - (9)].non_terminal),(yyvsp[(5) - (9)].non_terminal),(yyvsp[(6) - (9)].expression),(yyvsp[(8) - (9)].terminal),(yyvsp[(9) - (9)].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"statement");
							asm_gen->endForLoop();
							freeMemory(child);
						}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 617 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (6)].terminal),(yyvsp[(2) - (6)].terminal),(yyvsp[(3) - (6)].expression),(yyvsp[(4) - (6)].terminal),(yyvsp[(6) - (6)].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"statement");
							asm_gen->endIfBlock();
							freeMemory(child);
						}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 625 "1905072_parser.y"
    { 
							// //asm_gen->addComment("else");
							asm_gen->createElseBlock(); 
						}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 630 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (9)].terminal),(yyvsp[(2) - (9)].terminal),(yyvsp[(3) - (9)].expression),(yyvsp[(4) - (9)].terminal),(yyvsp[(6) - (9)].non_terminal),(yyvsp[(7) - (9)].terminal),(yyvsp[(9) - (9)].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"statement");
							asm_gen->endIfElseBlock();
							freeMemory(child);
						}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 637 "1905072_parser.y"
    { 
							//asm_gen->addComment($1->getSymbol());
							asm_gen->whileLoopStart(); 
						}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 642 "1905072_parser.y"
    { 
							//asm_gen->addComment($4->getSymbol());
							asm_gen->whileLoopConditionCheck((yyvsp[(4) - (4)].expression)); 
						}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 647 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (7)].terminal),(yyvsp[(3) - (7)].terminal),(yyvsp[(4) - (7)].expression),(yyvsp[(6) - (7)].terminal),(yyvsp[(7) - (7)].non_terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"statement");
							asm_gen->endWhileLoop();
							freeMemory(child);
						}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 654 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (5)].terminal),(yyvsp[(2) - (5)].terminal),(yyvsp[(3) - (5)].terminal),(yyvsp[(4) - (5)].terminal),(yyvsp[(5) - (5)].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"statement");	
							Identifier* id = (Identifier*)table->search((yyvsp[(3) - (5)].terminal)->getSymbol());	
							if(id == NULL)
							{
								err_hndlr->handleSemanticError(UNDECLARED_VARIABLE, line_count, (yyvsp[(3) - (5)].terminal)->getSymbol());
							}
							else if(id->getIdentity()=="FUNCTION")
							{
								err_hndlr->handleSemanticError(UNDECLARED_VARIABLE, line_count, (yyvsp[(3) - (5)].terminal)->getSymbol());
							}
							else
							{
								Variable*  var = (Variable*) id;
								//asm_gen->addComment($$->getSymbol());
								asm_gen->printId(var);
							}
							freeMemory(child);
						}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 675 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (3)].terminal),(yyvsp[(2) - (3)].expression),(yyvsp[(3) - (3)].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"statement");
							sem_anlz->returnFunction((yyvsp[(2) - (3)].expression));
							//asm_gen->addComment($$->getSymbol());
							asm_gen->returnFunction((yyvsp[(2) - (3)].expression));
							freeMemory(child);
						}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 683 "1905072_parser.y"
    {
							// New rule
							vector<SymbolInfo*> child = {(yyvsp[(1) - (2)].terminal),(yyvsp[(2) - (2)].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"statement");
							//asm_gen->addComment($$->getSymbol());
							asm_gen->returnFunction();
							freeMemory(child);
						}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 695 "1905072_parser.y"
    {
							asm_gen->createIfBlock(last_exp);
						}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 700 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (1)].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"expression_statement");
							freeMemory(child);
						}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 706 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (2)].expression),(yyvsp[(2) - (2)].terminal)};
							(yyval.non_terminal) = createNonTerminal(child,"expression_statement");
							asm_gen->forLoopConditionCheck((yyvsp[(1) - (2)].expression));
							freeMemory(child);
						}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 715 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (1)].terminal)};
							(yyval.expression) = createExpression(child,"variable");
							(yyval.expression)->setDataType(sem_anlz->callVariable((yyvsp[(1) - (1)].terminal)->getSymbol()));
							if((yyval.expression)->getDataType()!="NULL")
							{
								(yyval.expression)->setTmpVar(asm_gen->callVariable((yyvsp[(1) - (1)].terminal)->getSymbol()));
							}
							freeMemory(child);
						}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 726 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (4)].terminal),(yyvsp[(2) - (4)].terminal),(yyvsp[(3) - (4)].expression),(yyvsp[(4) - (4)].terminal)};
							(yyval.expression) = createArrayCall(child,"variable");

							(yyval.expression)->setDataType(sem_anlz->callArray((yyvsp[(1) - (4)].terminal)->getSymbol(),(yyvsp[(3) - (4)].expression)));
							if((yyval.expression)->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								// $3->setTmpVar(asm_gen->evaluateArrayIndex($3));
								(yyval.expression)->setTmpVar(asm_gen->callArray((yyvsp[(1) - (4)].terminal)->getSymbol(),(yyvsp[(3) - (4)].expression)));
								((ArrayCall*)(yyval.expression))->setIndex((yyvsp[(3) - (4)].expression)->getTmpVar());
							}
							// logout<<$$->getExpression()<<" "<<line_count<<endl;
							freeMemory(child);
						}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 744 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (1)].expression)};
							
							(yyval.expression) = createExpression(child,"expression");
							(yyval.expression)->setDataType((yyvsp[(1) - (1)].expression)->getDataType());
							(yyval.expression)->setTmpVar((yyvsp[(1) - (1)].expression)->getTmpVar());

							last_exp = new Expression((yyvsp[(1) - (1)].expression)); // For IF condition
							
							freeMemory(child);
						}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 756 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (3)].expression),(yyvsp[(2) - (3)].terminal),(yyvsp[(3) - (3)].expression)};
							(yyval.expression) = createExpression(child,"expression");
							(yyval.expression)->setDataType(sem_anlz->assignOp((yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression)));
							if((yyval.expression)->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								(yyval.expression)->setTmpVar(asm_gen->assignOp((yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression)));
							}
							freeMemory(child);
						}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 770 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (1)].expression)};
							(yyval.expression) = createExpression(child,"logic_expression");
							(yyval.expression)->setDataType((yyvsp[(1) - (1)].expression)->getDataType());
							(yyval.expression)->setTmpVar((yyvsp[(1) - (1)].expression)->getTmpVar());
							freeMemory(child);
						}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 778 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (3)].expression),(yyvsp[(2) - (3)].terminal),(yyvsp[(3) - (3)].expression)};
							(yyval.expression) = createExpression(child,"logic_expression");
							(yyval.expression)->setDataType(sem_anlz->logicOp((yyvsp[(1) - (3)].expression),(yyvsp[(2) - (3)].terminal)->getSymbol(),(yyvsp[(3) - (3)].expression)));
							if((yyval.expression)->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								(yyval.expression)->setTmpVar(asm_gen->logicOp((yyvsp[(1) - (3)].expression),(yyvsp[(2) - (3)].terminal)->getSymbol(),(yyvsp[(3) - (3)].expression)));
							}
							
							freeMemory(child);
						}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 793 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (1)].expression)};
							(yyval.expression) = createExpression(child,"rel_expression");
							(yyval.expression)->setDataType((yyvsp[(1) - (1)].expression)->getDataType());
							(yyval.expression)->setTmpVar((yyvsp[(1) - (1)].expression)->getTmpVar());
							freeMemory(child);
						}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 801 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (3)].expression),(yyvsp[(2) - (3)].terminal),(yyvsp[(3) - (3)].expression)};
							(yyval.expression) = createExpression(child,"rel_expression");
							(yyval.expression)->setDataType(sem_anlz->relOp((yyvsp[(1) - (3)].expression),(yyvsp[(2) - (3)].terminal)->getSymbol(),(yyvsp[(3) - (3)].expression)));
							if((yyval.expression)->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								(yyval.expression)->setTmpVar(asm_gen->relOp((yyvsp[(1) - (3)].expression),(yyvsp[(2) - (3)].terminal)->getSymbol(),(yyvsp[(3) - (3)].expression)));
							}
							
							freeMemory(child);
						}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 816 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (1)].expression)};
							(yyval.expression) = createExpression(child,"simple_expression");
							(yyval.expression)->setDataType((yyvsp[(1) - (1)].expression)->getDataType());
							(yyval.expression)->setTmpVar((yyvsp[(1) - (1)].expression)->getTmpVar());
							freeMemory(child);
						}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 824 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (3)].expression),(yyvsp[(2) - (3)].terminal),(yyvsp[(3) - (3)].expression)};
							(yyval.expression) = createExpression(child,"simple_expression");

							(yyval.expression)->setDataType(sem_anlz->addOp((yyvsp[(1) - (3)].expression),(yyvsp[(2) - (3)].terminal)->getSymbol(),(yyvsp[(3) - (3)].expression)));
							if((yyval.expression)->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								(yyval.expression)->setTmpVar(asm_gen->addOp((yyvsp[(1) - (3)].expression),(yyvsp[(2) - (3)].terminal)->getSymbol(),(yyvsp[(3) - (3)].expression)));
							}
							
							freeMemory(child);
						}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 840 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (1)].expression)};
							(yyval.expression) = createExpression(child,"term");
							(yyval.expression)->setDataType((yyvsp[(1) - (1)].expression)->getDataType());
							(yyval.expression)->setTmpVar((yyvsp[(1) - (1)].expression)->getTmpVar());
							freeMemory(child);
						}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 848 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (3)].expression),(yyvsp[(2) - (3)].terminal),(yyvsp[(3) - (3)].expression)};
							(yyval.expression) = createExpression(child,"term");

							(yyval.expression)->setDataType(sem_anlz->mulOp((yyvsp[(1) - (3)].expression),(yyvsp[(2) - (3)].terminal)->getSymbol(),(yyvsp[(3) - (3)].expression)));
							if((yyval.expression)->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								(yyval.expression)->setTmpVar(asm_gen->mulOp((yyvsp[(1) - (3)].expression),(yyvsp[(2) - (3)].terminal)->getSymbol(),(yyvsp[(3) - (3)].expression)));
							}
							
							freeMemory(child);
						}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 864 "1905072_parser.y"
    { 
							vector<SymbolInfo*> child = {(yyvsp[(1) - (2)].terminal),(yyvsp[(2) - (2)].expression)};
							(yyval.expression) = createExpression({(yyvsp[(1) - (2)].terminal),(yyvsp[(2) - (2)].expression)},"unary_expression");
							(yyval.expression)->setDataType((yyvsp[(2) - (2)].expression)->getDataType());
							if((yyval.expression)->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								(yyval.expression)->setTmpVar(asm_gen->unaryOperation((yyvsp[(1) - (2)].terminal)->getSymbol(), (yyvsp[(2) - (2)].expression)));
							}
							freeMemory(child);
						}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 876 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (2)].terminal),(yyvsp[(2) - (2)].expression)};
							(yyval.expression) = createExpression(child,"unary_expression");
							(yyval.expression)->setDataType((yyvsp[(2) - (2)].expression)->getDataType());
							if((yyval.expression)->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								(yyval.expression)->setTmpVar(asm_gen->notOperation((yyvsp[(2) - (2)].expression)));
							}
							freeMemory(child);
						}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 888 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (1)].expression)};
							(yyval.expression) = createExpression(child,"unary_expression");
							(yyval.expression)->setDataType((yyvsp[(1) - (1)].expression)->getDataType());
							(yyval.expression)->setTmpVar((yyvsp[(1) - (1)].expression)->getTmpVar());
							freeMemory(child);
						}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 898 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (1)].expression)};
							(yyval.expression) = createExpression(child,"factor");
							(yyval.expression)->setDataType((yyvsp[(1) - (1)].expression)->getDataType());

							if((yyvsp[(1) - (1)].expression)->getExpType() == "ARRAY_CALL")
							{
								asm_gen->moveIndex((ArrayCall*)(yyvsp[(1) - (1)].expression));
								(yyval.expression)->setTmpVar(asm_gen->arrayToFactor((yyvsp[(1) - (1)].expression)));
							}
							else
							{
								(yyval.expression)->setTmpVar((yyvsp[(1) - (1)].expression)->getTmpVar());
							}
							freeMemory(child);
						}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 915 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (4)].terminal),(yyvsp[(2) - (4)].terminal),(yyvsp[(3) - (4)].args),(yyvsp[(4) - (4)].terminal)};
							(yyval.expression) = createExpression(child,"factor");
							(yyval.expression)->setDataType(sem_anlz->callFunction((yyvsp[(1) - (4)].terminal)->getSymbol(), (yyvsp[(3) - (4)].args)->getArgs()));

							if((yyval.expression)->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								(yyval.expression)->setTmpVar(
									asm_gen->callFunction((Function*)table->search((yyvsp[(1) - (4)].terminal)->getSymbol()),(yyvsp[(3) - (4)].args)->getArgs())
								);
							}
							

							// freeArrayMemory(args);
							freeMemory(child);
						}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 933 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (3)].terminal),(yyvsp[(2) - (3)].expression),(yyvsp[(3) - (3)].terminal)};
							(yyval.expression) = createExpression(child,"factor");
							(yyval.expression)->setDataType((yyvsp[(2) - (3)].expression)->getDataType());
							(yyval.expression)->setTmpVar((yyvsp[(2) - (3)].expression)->getTmpVar());
							freeMemory(child);
						}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 941 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (1)].terminal)};
							(yyval.expression) = createExpression(child,"factor");
							(yyval.expression)->setDataType("int");
							(yyval.expression)->setTmpVar((yyvsp[(1) - (1)].terminal)->getSymbol());
							freeMemory(child);
						}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 949 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (1)].terminal)};
							(yyval.expression) = createExpression(child,"factor");
							(yyval.expression)->setDataType("float");
							(yyval.expression)->setTmpVar((yyvsp[(1) - (1)].terminal)->getSymbol());
							freeMemory(child);
						}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 957 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (2)].expression),(yyvsp[(2) - (2)].terminal)};
							(yyval.expression) = createExpression(child,"factor");
							(yyval.expression)->setDataType((yyvsp[(1) - (2)].expression)->getDataType());

							if((yyvsp[(1) - (2)].expression)->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								asm_gen->incrementOperation((yyvsp[(1) - (2)].expression));
							}	
							(yyval.expression)->setTmpVar((yyvsp[(1) - (2)].expression)->getTmpVar());
							freeMemory(child);
						}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 971 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (2)].expression),(yyvsp[(2) - (2)].terminal)};
							(yyval.expression) = createExpression(child,"factor");
							(yyval.expression)->setDataType((yyvsp[(1) - (2)].expression)->getDataType());
							if((yyvsp[(1) - (2)].expression)->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								asm_gen->decrementOperation((yyvsp[(1) - (2)].expression));
							}
							(yyval.expression)->setTmpVar((yyvsp[(1) - (2)].expression)->getTmpVar());
							freeMemory(child);
						}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 986 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (1)].args)};
							(yyval.args) = createArgumentList(child,"argument_list");

							(yyval.args)->addArgs((yyvsp[(1) - (1)].args));
							freeMemory(child);
						}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 994 "1905072_parser.y"
    { 
							vector<SymbolInfo*> child = {};
							(yyval.args) = createArgumentList(child,"argument_list");
							freeMemory(child);
						}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 1002 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (3)].args),(yyvsp[(2) - (3)].terminal),(yyvsp[(3) - (3)].expression)};
							(yyval.args) = createArgumentList(child,"arguments");

							(yyval.args)->addArgs((yyvsp[(1) - (3)].args));
							(yyval.args)->addArg((yyvsp[(3) - (3)].expression));
							freeMemory(child);
						}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 1011 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (1)].expression)};
							(yyval.args) = createArgumentList(child,"arguments");

							(yyval.args)->addArg((yyvsp[(1) - (1)].expression));
							freeMemory(child);
						}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 1022 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (1)].terminal)};
							(yyval.expression) = createExpression(child,"constant");
							(yyval.expression)->setDataType("int");
							(yyval.expression)->setTmpVar((yyvsp[(1) - (1)].terminal)->getSymbol());
							freeMemory(child);
						}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 1030 "1905072_parser.y"
    {
							vector<SymbolInfo*> child = {(yyvsp[(1) - (1)].terminal)};
							(yyval.expression) = createExpression(child,"constant");
							(yyval.expression)->setDataType("float");
							(yyval.expression)->setTmpVar((yyvsp[(1) - (1)].terminal)->getSymbol());
							freeMemory(child);
						}
    break;



/* Line 1455 of yacc.c  */
#line 3554 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 1037 "1905072_parser.y"


