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
#line 1 "src/parser.y"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <string>
#include "../include/SymbolTable.hpp"
#include "../include/Logger.hpp"
#include "../include/ErrorHandler.hpp"
#include "../include/SemanticAnalyzer.hpp"
#include "../include/Util.hpp"
#include "../include/ExtendedSymbol.hpp"
#include "../include/Tokenizer.hpp"
#include "../include/ParseTreeGenerator.hpp"
using namespace std;

int yylex(void);
extern FILE *yyin;
extern SemanticAnalyzer* sem_anlzr;
extern ofstream parseout;
extern ErrorHandler *error_hndlr;
extern ofstream logout;
extern ofstream errorout;

void yyerror(string error){
	// errorout << error_hndlr->handleSyntaxError(error, sem_anlzr->getLineCount()) << std::endl;
}

void syntax_error(string parent,string error_child){
	errorout << error_hndlr->handleSyntaxError(parent, error_child, sem_anlzr->getLineCount()) << std::endl;
}

void syntax_error(string parent){
	errorout << error_hndlr->handleSyntaxError(parent, sem_anlzr->getLineCount()) << std::endl;
}


#line 110 "parser.tab.c"

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
  YYSYMBOL_LSQUARE = 30,                   /* LSQUARE  */
  YYSYMBOL_RSQUARE = 31,                   /* RSQUARE  */
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
  YYSYMBOL_BITOP = 42,                     /* BITOP  */
  YYSYMBOL_YYACCEPT = 43,                  /* $accept  */
  YYSYMBOL_start = 44,                     /* start  */
  YYSYMBOL_program = 45,                   /* program  */
  YYSYMBOL_unit = 46,                      /* unit  */
  YYSYMBOL_func_declaration = 47,          /* func_declaration  */
  YYSYMBOL_func_definition = 48,           /* func_definition  */
  YYSYMBOL_49_1 = 49,                      /* $@1  */
  YYSYMBOL_50_2 = 50,                      /* $@2  */
  YYSYMBOL_51_3 = 51,                      /* $@3  */
  YYSYMBOL_52_4 = 52,                      /* $@4  */
  YYSYMBOL_parameter_list = 53,            /* parameter_list  */
  YYSYMBOL_compound_statement = 54,        /* compound_statement  */
  YYSYMBOL_create_scope = 55,              /* create_scope  */
  YYSYMBOL_var_declaration = 56,           /* var_declaration  */
  YYSYMBOL_type_specifier = 57,            /* type_specifier  */
  YYSYMBOL_declaration_list = 58,          /* declaration_list  */
  YYSYMBOL_statements = 59,                /* statements  */
  YYSYMBOL_statement = 60,                 /* statement  */
  YYSYMBOL_expression_statement = 61,      /* expression_statement  */
  YYSYMBOL_variable = 62,                  /* variable  */
  YYSYMBOL_expression = 63,                /* expression  */
  YYSYMBOL_logic_expression = 64,          /* logic_expression  */
  YYSYMBOL_rel_expression = 65,            /* rel_expression  */
  YYSYMBOL_simple_expression = 66,         /* simple_expression  */
  YYSYMBOL_term = 67,                      /* term  */
  YYSYMBOL_unary_expression = 68,          /* unary_expression  */
  YYSYMBOL_factor = 69,                    /* factor  */
  YYSYMBOL_argument_list = 70,             /* argument_list  */
  YYSYMBOL_arguments = 71                  /* arguments  */
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
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   186

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  79
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  133

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   297


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
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    64,    64,    74,    79,    86,    92,    98,   104,   113,
     128,   145,   160,   181,   180,   192,   191,   205,   204,   216,
     215,   231,   249,   267,   274,   298,   319,   337,   342,   349,
     361,   367,   373,   382,   398,   416,   423,   440,   446,   467,
     473,   480,   487,   493,   499,   505,   511,   517,   523,   530,
     538,   544,   552,   560,   567,   576,   583,   600,   607,   616,
     623,   632,   639,   648,   655,   664,   671,   678,   687,   694,
     701,   708,   715,   722,   729,   738,   746,   756,   762,   770
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
  "LCURL", "RCURL", "LSQUARE", "RSQUARE", "COMMA", "SEMICOLON", "ID",
  "CONST_INT", "CONST_FLOAT", "CONST_CHAR", "ADDOP", "MULOP", "LOGICOP",
  "RELOP", "BITOP", "$accept", "start", "program", "unit",
  "func_declaration", "func_definition", "$@1", "$@2", "$@3", "$@4",
  "parameter_list", "compound_statement", "create_scope",
  "var_declaration", "type_specifier", "declaration_list", "statements",
  "statement", "expression_statement", "variable", "expression",
  "logic_expression", "rel_expression", "simple_expression", "term",
  "unary_expression", "factor", "argument_list", "arguments", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-83)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-76)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      11,   -83,   -83,   -83,   -83,    25,    18,   -83,   -83,   -83,
     -83,    21,   -83,   -83,   -16,     5,    58,    22,    27,    35,
     -83,    46,    45,     7,    52,    56,   -83,    65,    72,   -83,
      70,    79,    78,    84,   -83,   -83,    74,   -83,    70,   -83,
     -83,    80,   -83,    70,    82,    83,   -83,    55,   -83,    70,
     -83,   -83,   -83,    89,   111,   119,   121,   146,    97,    97,
     -83,   -83,   -13,   -83,   -83,    97,   -83,   -83,   -83,   -83,
      91,   -83,   -83,   120,   115,   -83,   109,    39,   113,   -83,
     -83,   -83,   -83,    97,   133,    97,   -83,   117,     0,   -83,
     129,    97,    97,   -83,   -83,   -83,   -83,   -83,    97,   -83,
      97,    97,    97,    97,   131,   133,   137,   -83,   -83,   -83,
     147,    19,   123,   -83,   -83,   113,   135,   -83,   127,    97,
     127,   -83,   -83,    97,   -83,   171,   149,   -83,   -83,   127,
     127,   -83,   -83
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     8,    30,    31,    32,     0,     0,     4,     6,     7,
       5,     0,     1,     3,    35,     0,     0,     0,     0,     0,
      28,     0,    17,     0,    24,     0,    29,    33,    19,    11,
       0,     0,    13,     0,    23,    36,     0,    12,     0,    27,
      18,    15,     9,     0,    22,     0,    20,     0,    10,     0,
      14,    21,    34,     0,     0,     0,     0,     0,     0,     0,
      26,    50,    53,    71,    72,     0,    41,    40,    43,    39,
       0,    37,    42,    68,     0,    55,    57,    59,    61,    63,
      67,    16,    52,     0,     0,     0,    49,     0,    68,    66,
       0,    77,     0,    65,    25,    38,    73,    74,     0,    51,
       0,     0,     0,     0,     0,     0,     0,    48,    70,    79,
       0,     0,     0,    56,    58,    62,    60,    64,     0,     0,
       0,    69,    76,     0,    54,    45,     0,    47,    78,     0,
       0,    46,    44
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -83,   -83,   -83,   172,    47,    48,   -83,   -83,   -83,   -83,
     -83,    69,   -83,    76,    -1,   -83,   -83,   -68,   -79,   -58,
     -56,   -82,    77,    81,    85,   -54,   -83,   -83,   -83
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     5,     6,     7,    66,    67,    43,    49,    30,    38,
      23,    68,    47,    69,    11,    15,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,   110,   111
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      88,    87,    95,    90,    89,   105,    18,    88,    31,   109,
      16,    93,     1,    91,    17,    24,   113,    92,    -2,     1,
     122,    96,    97,     2,     3,    12,   119,   104,     4,   106,
       2,     3,    44,    88,    32,     4,   112,    19,    20,    33,
      88,   128,    88,    88,    88,    88,   -75,     8,     9,   117,
     125,   123,   127,     8,     9,    14,    53,    25,    54,    21,
      26,   131,   132,   126,    55,    88,    56,     2,     3,    27,
       2,     3,     4,    28,    57,     4,    10,   101,    29,    58,
     102,    59,    10,    39,    60,    22,    34,    35,    61,    62,
      63,    64,    53,    65,    54,    36,     2,     3,    39,    40,
      55,     4,    56,     2,     3,    37,    41,    46,     4,    45,
      57,    42,    50,    48,    52,    58,    51,    59,    81,    39,
      94,    58,    82,    59,    61,    62,    63,    64,    53,    65,
      54,    62,    63,    64,    53,    65,    55,    83,    56,     2,
       3,    96,    97,    98,     4,    84,    57,    85,    99,   100,
     107,    58,   103,    59,   124,    39,   108,    58,   118,    59,
      61,    62,    63,    64,   120,    65,    61,    62,    63,    64,
      58,    65,    59,   101,   121,   129,   130,   114,    13,    86,
      62,    63,    64,   116,    65,     0,   115
};

static const yytype_int16 yycheck[] =
{
      58,    57,    70,    59,    58,    84,     1,    65,     1,    91,
      26,    65,     1,    26,    30,    16,    98,    30,     0,     1,
       1,    21,    22,    12,    13,     0,   105,    83,    17,    85,
      12,    13,    33,    91,    27,    17,    92,    32,    33,    32,
      98,   123,   100,   101,   102,   103,    27,     0,     0,   103,
     118,    32,   120,     6,     6,    34,     1,    35,     3,     1,
      33,   129,   130,   119,     9,   123,    11,    12,    13,    34,
      12,    13,    17,    27,    19,    17,     0,    38,    33,    24,
      41,    26,     6,    28,    29,    27,    34,    31,    33,    34,
      35,    36,     1,    38,     3,    30,    12,    13,    28,    30,
       9,    17,    11,    12,    13,    33,    27,    38,    17,    35,
      19,    33,    43,    33,    31,    24,    34,    26,    49,    28,
      29,    24,    33,    26,    33,    34,    35,    36,     1,    38,
       3,    34,    35,    36,     1,    38,     9,    26,    11,    12,
      13,    21,    22,    23,    17,    26,    19,    26,    33,    40,
      33,    24,    39,    26,    31,    28,    27,    24,    27,    26,
      33,    34,    35,    36,    27,    38,    33,    34,    35,    36,
      24,    38,    26,    38,    27,     4,    27,   100,     6,    33,
      34,    35,    36,   102,    38,    -1,   101
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,    12,    13,    17,    44,    45,    46,    47,    48,
      56,    57,     0,    46,    34,    58,    26,    30,     1,    32,
      33,     1,    27,    53,    57,    35,    33,    34,    27,    33,
      51,     1,    27,    32,    34,    31,    30,    33,    52,    28,
      54,    27,    33,    49,    57,    35,    54,    55,    33,    50,
      54,    34,    31,     1,     3,     9,    11,    19,    24,    26,
      29,    33,    34,    35,    36,    38,    47,    48,    54,    56,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    54,    33,    26,    26,    26,    33,    63,    62,    68,
      63,    26,    30,    68,    29,    60,    21,    22,    23,    33,
      40,    38,    41,    39,    63,    61,    63,    33,    27,    64,
      70,    71,    63,    64,    65,    67,    66,    68,    27,    61,
      27,    27,     1,    32,    31,    60,    63,    60,    64,     4,
      27,    60,    60
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    43,    44,    45,    45,    46,    46,    46,    46,    47,
      47,    47,    47,    49,    48,    50,    48,    51,    48,    52,
      48,    53,    53,    53,    53,    54,    54,    55,    56,    56,
      57,    57,    57,    58,    58,    58,    58,    59,    59,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      61,    61,    61,    62,    62,    63,    63,    64,    64,    65,
      65,    66,    66,    67,    67,    68,    68,    68,    69,    69,
      69,    69,    69,    69,    69,    70,    70,    70,    71,    71
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     6,
       7,     5,     6,     0,     7,     0,     8,     0,     6,     0,
       7,     4,     3,     2,     1,     4,     3,     0,     3,     4,
       1,     1,     1,     3,     6,     1,     4,     1,     2,     1,
       1,     1,     1,     1,     7,     5,     7,     5,     3,     2,
       1,     2,     2,     1,     4,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     2,     2,     1,     1,     4,
       3,     1,     1,     2,     2,     1,     2,     0,     3,     1
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
  case 2: /* start: program  */
#line 65 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"start");
							cout<<"Code compiled successfully"<<endl;
							parseout<<ParseTreeGenerator::getTree((yyval.non_terminal));
							ParseTreeGenerator::deleteTree((yyval.non_terminal));
						}
#line 1545 "parser.tab.c"
    break;

  case 3: /* program: program unit  */
#line 75 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-1].non_terminal),(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"program");			 
						}
#line 1554 "parser.tab.c"
    break;

  case 4: /* program: unit  */
#line 80 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"program");
						}
#line 1563 "parser.tab.c"
    break;

  case 5: /* unit: var_declaration  */
#line 87 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"unit");
							
						}
#line 1573 "parser.tab.c"
    break;

  case 6: /* unit: func_declaration  */
#line 93 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"unit");
							
						}
#line 1583 "parser.tab.c"
    break;

  case 7: /* unit: func_definition  */
#line 99 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"unit");
							
						}
#line 1593 "parser.tab.c"
    break;

  case 8: /* unit: error  */
#line 104 "src/parser.y"
                                                        {
							vector<SymbolInfo*> child = {};
							SymbolInfo *s = ParseTreeGenerator::createErrorNode(sem_anlzr->getLineCount());
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"unit");
							syntax_error("unit");
						}
#line 1604 "parser.tab.c"
    break;

  case 9: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON  */
#line 114 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-5].non_terminal),(yyvsp[-4].terminal),(yyvsp[-3].terminal),(yyvsp[-2].params),(yyvsp[-1].terminal),(yyvsp[0].terminal)};
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"func_declaration");
							sem_anlzr->declareFunction((yyvsp[-5].non_terminal)->getSymbol(),(yyvsp[-4].terminal)->getSymbol(),(yyvsp[-2].params)->getParams());
							
						}
#line 1615 "parser.tab.c"
    break;

  case 10: /* func_declaration: type_specifier ID LPAREN parameter_list error RPAREN SEMICOLON  */
#line 129 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-6].non_terminal),(yyvsp[-5].terminal),(yyvsp[-4].terminal),(yyvsp[-3].params),(yyvsp[-1].terminal),(yyvsp[0].terminal)};
							SymbolInfo *s = ParseTreeGenerator::createErrorNode(sem_anlzr->getLineCount());
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"func_declaration");
							// sem_anlzr->declareFunction($1->getSymbol(),$2->getSymbol(),$4->getParams());
							syntax_error("function declaration","parameter list");
							
						}
#line 1628 "parser.tab.c"
    break;

  case 11: /* func_declaration: type_specifier ID LPAREN RPAREN SEMICOLON  */
#line 146 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-4].non_terminal),(yyvsp[-3].terminal),(yyvsp[-2].terminal),(yyvsp[-1].terminal),(yyvsp[0].terminal)};
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"func_declaration");
							sem_anlzr->declareFunction((yyvsp[-4].non_terminal)->getSymbol(),(yyvsp[-3].terminal)->getSymbol(),{});
							
						}
#line 1639 "parser.tab.c"
    break;

  case 12: /* func_declaration: type_specifier ID LPAREN error RPAREN SEMICOLON  */
#line 161 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-5].non_terminal),(yyvsp[-4].terminal),(yyvsp[-3].terminal),(yyvsp[-1].terminal),(yyvsp[0].terminal)};
							SymbolInfo *s = ParseTreeGenerator::createErrorNode(sem_anlzr->getLineCount());
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"func_declaration");
							// sem_anlzr->declareFunction($1->getSymbol(),$2->getSymbol(),{});
							syntax_error("function declaration","parameter list");
							
						}
#line 1652 "parser.tab.c"
    break;

  case 13: /* $@1: %empty  */
#line 181 "src/parser.y"
                                                {
							sem_anlzr->defineFunction((yyvsp[-4].non_terminal)->getSymbol(),(yyvsp[-3].terminal)->getSymbol(), (yyvsp[-1].params)->getParams());
						}
#line 1660 "parser.tab.c"
    break;

  case 14: /* func_definition: type_specifier ID LPAREN parameter_list RPAREN $@1 compound_statement  */
#line 185 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-6].non_terminal),(yyvsp[-5].terminal),(yyvsp[-4].terminal),(yyvsp[-3].params),(yyvsp[-2].terminal),(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"func_definition");
							sem_anlzr->endFunction();
							
						}
#line 1671 "parser.tab.c"
    break;

  case 15: /* $@2: %empty  */
#line 192 "src/parser.y"
                                                {
							// sem_anlzr->defineFunction($1->getSymbol(),$2->getSymbol(), $4->getParams());
							syntax_error("function definition","parameter list");
						}
#line 1680 "parser.tab.c"
    break;

  case 16: /* func_definition: type_specifier ID LPAREN parameter_list error RPAREN $@2 compound_statement  */
#line 197 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-7].non_terminal),(yyvsp[-6].terminal),(yyvsp[-5].terminal),(yyvsp[-4].params),(yyvsp[-2].terminal),(yyvsp[0].non_terminal)};
							SymbolInfo *s = ParseTreeGenerator::createErrorNode(sem_anlzr->getLineCount());
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"func_definition");
							sem_anlzr->endFunction();
							
						}
#line 1692 "parser.tab.c"
    break;

  case 17: /* $@3: %empty  */
#line 205 "src/parser.y"
                                                {
							sem_anlzr->defineFunction((yyvsp[-3].non_terminal)->getSymbol(),(yyvsp[-2].terminal)->getSymbol(), {});
						}
#line 1700 "parser.tab.c"
    break;

  case 18: /* func_definition: type_specifier ID LPAREN RPAREN $@3 compound_statement  */
#line 209 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-5].non_terminal),(yyvsp[-4].terminal),(yyvsp[-3].terminal),(yyvsp[-2].terminal),(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"func_definition");
							sem_anlzr->endFunction();
							
						}
#line 1711 "parser.tab.c"
    break;

  case 19: /* $@4: %empty  */
#line 216 "src/parser.y"
                                                {
							// sem_anlzr->defineFunction($1->getSymbol(),$2->getSymbol(), vector<Variable*>());
							syntax_error("function definition","parameter list");
						}
#line 1720 "parser.tab.c"
    break;

  case 20: /* func_definition: type_specifier ID LPAREN error RPAREN $@4 compound_statement  */
#line 221 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-6].non_terminal),(yyvsp[-5].terminal),(yyvsp[-4].terminal),(yyvsp[-2].terminal),(yyvsp[0].non_terminal)};
							SymbolInfo *s = ParseTreeGenerator::createErrorNode(sem_anlzr->getLineCount());
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"func_definition");
							sem_anlzr->endFunction();
							// freeMemory(child);
						}
#line 1732 "parser.tab.c"
    break;

  case 21: /* parameter_list: parameter_list COMMA type_specifier ID  */
#line 232 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-3].params),(yyvsp[-2].terminal),(yyvsp[-1].non_terminal),(yyvsp[0].terminal)};
							(yyval.params) = ParseTreeGenerator::createParameterList(child,"parameter_list");
							(yyval.params)->addParams((yyvsp[-3].params));
							(yyval.params)->addParam((yyvsp[-1].non_terminal)->getSymbol(),(yyvsp[0].terminal)->getSymbol());
							// freeMemory(child);
						}
#line 1744 "parser.tab.c"
    break;

  case 22: /* parameter_list: parameter_list COMMA type_specifier  */
#line 250 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-2].params),(yyvsp[-1].terminal),(yyvsp[0].non_terminal)};
							(yyval.params) = ParseTreeGenerator::createParameterList(child,"parameter_list");
							(yyval.params)->addParams((yyvsp[-2].params));
							(yyval.params)->addParam((yyvsp[0].non_terminal)->getSymbol());
							
						}
#line 1756 "parser.tab.c"
    break;

  case 23: /* parameter_list: type_specifier ID  */
#line 268 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-1].non_terminal),(yyvsp[0].terminal)};
							(yyval.params) = ParseTreeGenerator::createParameterList(child,"parameter_list");
							(yyval.params)->addParam((yyvsp[-1].non_terminal)->getSymbol(),(yyvsp[0].terminal)->getSymbol());
							
						}
#line 1767 "parser.tab.c"
    break;

  case 24: /* parameter_list: type_specifier  */
#line 275 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].non_terminal)};
							(yyval.params) = ParseTreeGenerator::createParameterList(child,"parameter_list");
							(yyval.params)->addParam((yyvsp[0].non_terminal)->getSymbol());
							
						}
#line 1778 "parser.tab.c"
    break;

  case 25: /* compound_statement: LCURL create_scope statements RCURL  */
#line 299 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-3].terminal),(yyvsp[-1].non_terminal),(yyvsp[0].terminal)};
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"compound_statement");
							sem_anlzr->endScope();
							
						}
#line 1789 "parser.tab.c"
    break;

  case 26: /* compound_statement: LCURL create_scope RCURL  */
#line 320 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-2].terminal),(yyvsp[0].terminal)};
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"compound_statement");
							sem_anlzr->endScope();
							
						}
#line 1800 "parser.tab.c"
    break;

  case 27: /* create_scope: %empty  */
#line 337 "src/parser.y"
                                                { 
							sem_anlzr->startScope();
						}
#line 1808 "parser.tab.c"
    break;

  case 28: /* var_declaration: type_specifier declaration_list SEMICOLON  */
#line 343 "src/parser.y"
                                                { 				
							vector<SymbolInfo*> child = {(yyvsp[-2].non_terminal),(yyvsp[-1].vars),(yyvsp[0].terminal)};
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"var_declaration");
							sem_anlzr->declareVariables((yyvsp[-2].non_terminal)->getSymbol(),(yyvsp[-1].vars)->getSymbol(),(yyvsp[-1].vars)->getDeclarations());
							
						}
#line 1819 "parser.tab.c"
    break;

  case 29: /* var_declaration: type_specifier declaration_list error SEMICOLON  */
#line 350 "src/parser.y"
                                                { 			
							vector<SymbolInfo*> child = {(yyvsp[-3].non_terminal),(yyvsp[-2].vars),(yyvsp[0].terminal)};
							SymbolInfo *s = ParseTreeGenerator::createErrorNode(sem_anlzr->getLineCount());
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"var_declaration");
							sem_anlzr->declareVariables((yyvsp[-3].non_terminal)->getSymbol(),(yyvsp[-2].vars)->getSymbol(),(yyvsp[-2].vars)->getDeclarations());
							syntax_error("variable declaration","declaration list");
							
						}
#line 1832 "parser.tab.c"
    break;

  case 30: /* type_specifier: INT  */
#line 362 "src/parser.y"
                                                { 
							vector<SymbolInfo*> child = {(yyvsp[0].terminal)};
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"type_specifier");
							
						}
#line 1842 "parser.tab.c"
    break;

  case 31: /* type_specifier: FLOAT  */
#line 368 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].terminal)};
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"type_specifier");
							
						}
#line 1852 "parser.tab.c"
    break;

  case 32: /* type_specifier: VOID  */
#line 374 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].terminal)};
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"type_specifier");
							
						}
#line 1862 "parser.tab.c"
    break;

  case 33: /* declaration_list: declaration_list COMMA ID  */
#line 383 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-2].vars),(yyvsp[-1].terminal),(yyvsp[0].terminal)};
							(yyval.vars) = ParseTreeGenerator::createDeclarationList(child,"declaration_list");
							(yyval.vars)->addVariables((yyvsp[-2].vars));
							(yyval.vars)->addVariable((yyvsp[0].terminal)->getSymbol());
							
						}
#line 1874 "parser.tab.c"
    break;

  case 34: /* declaration_list: declaration_list COMMA ID LSQUARE CONST_INT RSQUARE  */
#line 399 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-5].vars),(yyvsp[-4].terminal),(yyvsp[-3].terminal),(yyvsp[-2].terminal),(yyvsp[-1].terminal),(yyvsp[0].terminal)};
							(yyval.vars) = ParseTreeGenerator::createDeclarationList(child,"declaration_list");
							// sem_anlzr->checkArraySize($5);
							(yyval.vars)->addVariables((yyvsp[-5].vars));
							(yyval.vars)->addArray((yyvsp[-3].terminal)->getSymbol(),(yyvsp[-1].terminal)->getSymbol());
							
						}
#line 1887 "parser.tab.c"
    break;

  case 35: /* declaration_list: ID  */
#line 417 "src/parser.y"
                                                { 
							vector<SymbolInfo*> child = {(yyvsp[0].terminal)};
							(yyval.vars) = ParseTreeGenerator::createDeclarationList(child,"declaration_list");	
							(yyval.vars)->addVariable((yyvsp[0].terminal)->getSymbol());
							
						}
#line 1898 "parser.tab.c"
    break;

  case 36: /* declaration_list: ID LSQUARE CONST_INT RSQUARE  */
#line 424 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-3].terminal),(yyvsp[-2].terminal),(yyvsp[-1].terminal),(yyvsp[0].terminal)};
							(yyval.vars) = ParseTreeGenerator::createDeclarationList(child,"declaration_list");
							// sem_anlzr->checkArraySize($3);
							(yyval.vars)->addArray((yyvsp[-3].terminal)->getSymbol(),(yyvsp[-1].terminal)->getSymbol());
							
						}
#line 1910 "parser.tab.c"
    break;

  case 37: /* statements: statement  */
#line 441 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"statements");
							
						}
#line 1920 "parser.tab.c"
    break;

  case 38: /* statements: statements statement  */
#line 447 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-1].non_terminal),(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"statements");
							
						}
#line 1930 "parser.tab.c"
    break;

  case 39: /* statement: var_declaration  */
#line 468 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"statement");
							
						}
#line 1940 "parser.tab.c"
    break;

  case 40: /* statement: func_definition  */
#line 474 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"statement");
							sem_anlzr->handleInvalidFunctionScoping();
							
						}
#line 1951 "parser.tab.c"
    break;

  case 41: /* statement: func_declaration  */
#line 481 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"statement");
							sem_anlzr->handleInvalidFunctionScoping();
							
						}
#line 1962 "parser.tab.c"
    break;

  case 42: /* statement: expression_statement  */
#line 488 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"statement");
							
						}
#line 1972 "parser.tab.c"
    break;

  case 43: /* statement: compound_statement  */
#line 494 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"statement");
							
						}
#line 1982 "parser.tab.c"
    break;

  case 44: /* statement: FOR LPAREN expression_statement expression_statement expression RPAREN statement  */
#line 500 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-6].terminal),(yyvsp[-5].terminal),(yyvsp[-4].non_terminal),(yyvsp[-3].non_terminal),(yyvsp[-2].expression),(yyvsp[-1].terminal),(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"statement");
							
						}
#line 1992 "parser.tab.c"
    break;

  case 45: /* statement: IF LPAREN expression RPAREN statement  */
#line 506 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-4].terminal),(yyvsp[-3].terminal),(yyvsp[-2].expression),(yyvsp[-1].terminal),(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"statement");
							
						}
#line 2002 "parser.tab.c"
    break;

  case 46: /* statement: IF LPAREN expression RPAREN statement ELSE statement  */
#line 512 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-6].terminal),(yyvsp[-5].terminal),(yyvsp[-4].expression),(yyvsp[-3].terminal),(yyvsp[-2].non_terminal),(yyvsp[-1].terminal),(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"statement");
							
						}
#line 2012 "parser.tab.c"
    break;

  case 47: /* statement: WHILE LPAREN expression RPAREN statement  */
#line 518 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-4].terminal),(yyvsp[-3].terminal),(yyvsp[-2].expression),(yyvsp[-1].terminal),(yyvsp[0].non_terminal)};
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"statement");
							
						}
#line 2022 "parser.tab.c"
    break;

  case 48: /* statement: RETURN expression SEMICOLON  */
#line 524 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-2].terminal),(yyvsp[-1].expression),(yyvsp[0].terminal)};
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"statement");
							sem_anlzr->returnFunction((yyvsp[-1].expression));
							
						}
#line 2033 "parser.tab.c"
    break;

  case 49: /* statement: RETURN SEMICOLON  */
#line 530 "src/parser.y"
                                                                   {
							// New rule
							vector<SymbolInfo*> child = {(yyvsp[-1].terminal),(yyvsp[0].terminal)};
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"statement");
							
						}
#line 2044 "parser.tab.c"
    break;

  case 50: /* expression_statement: SEMICOLON  */
#line 539 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].terminal)};
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"expression_statement");
							
						}
#line 2054 "parser.tab.c"
    break;

  case 51: /* expression_statement: expression SEMICOLON  */
#line 545 "src/parser.y"
                                                {
						
							vector<SymbolInfo*> child = {(yyvsp[-1].expression),(yyvsp[0].terminal)};
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"expression_statement");
						
							
						}
#line 2066 "parser.tab.c"
    break;

  case 52: /* expression_statement: error SEMICOLON  */
#line 552 "src/parser.y"
                                                                  {
							vector<SymbolInfo*> child = {(yyvsp[0].terminal)};
							SymbolInfo *s = ParseTreeGenerator::createErrorNode(sem_anlzr->getLineCount());
							(yyval.non_terminal) = ParseTreeGenerator::createNonTerminal(child,"expression_statement");
							syntax_error("expression statement","expression");
						}
#line 2077 "parser.tab.c"
    break;

  case 53: /* variable: ID  */
#line 561 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].terminal)};
							(yyval.expression) = ParseTreeGenerator::createExpression(child,"variable");
							(yyval.expression)->setDataType(sem_anlzr->callVariable((yyvsp[0].terminal)->getSymbol()));
							
						}
#line 2088 "parser.tab.c"
    break;

  case 54: /* variable: ID LSQUARE expression RSQUARE  */
#line 568 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-3].terminal),(yyvsp[-2].terminal),(yyvsp[-1].expression),(yyvsp[0].terminal)};
							(yyval.expression) =  ParseTreeGenerator::createArrayCall(child,"variable");
							(yyval.expression)->setDataType(sem_anlzr->callArray((yyvsp[-3].terminal)->getSymbol(),(yyvsp[-1].expression)));
							
						}
#line 2099 "parser.tab.c"
    break;

  case 55: /* expression: logic_expression  */
#line 577 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].expression)};
							(yyval.expression) = ParseTreeGenerator::createExpression(child,"expression");
							(yyval.expression)->setDataType((yyvsp[0].expression)->getDataType());				
							
						}
#line 2110 "parser.tab.c"
    break;

  case 56: /* expression: variable ASSIGNOP logic_expression  */
#line 584 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-2].expression),(yyvsp[-1].terminal),(yyvsp[0].expression)};
							(yyval.expression) = ParseTreeGenerator::createExpression(child,"expression");
							(yyval.expression)->setDataType(sem_anlzr->assignOp((yyvsp[-2].expression),(yyvsp[0].expression)));
							
						}
#line 2121 "parser.tab.c"
    break;

  case 57: /* logic_expression: rel_expression  */
#line 601 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].expression)};
							(yyval.expression) = ParseTreeGenerator::createExpression(child,"logic_expression");
							(yyval.expression)->setDataType((yyvsp[0].expression)->getDataType());
							
						}
#line 2132 "parser.tab.c"
    break;

  case 58: /* logic_expression: rel_expression LOGICOP rel_expression  */
#line 608 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-2].expression),(yyvsp[-1].terminal),(yyvsp[0].expression)};
							(yyval.expression) = ParseTreeGenerator::createExpression(child,"logic_expression");
							(yyval.expression)->setDataType(sem_anlzr->logicOp((yyvsp[-2].expression),(yyvsp[-1].terminal)->getSymbol(),(yyvsp[0].expression)));
							
						}
#line 2143 "parser.tab.c"
    break;

  case 59: /* rel_expression: simple_expression  */
#line 617 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].expression)};
							(yyval.expression) = ParseTreeGenerator::createExpression(child,"rel_expression");
							(yyval.expression)->setDataType((yyvsp[0].expression)->getDataType());
							
						}
#line 2154 "parser.tab.c"
    break;

  case 60: /* rel_expression: simple_expression RELOP simple_expression  */
#line 624 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-2].expression),(yyvsp[-1].terminal),(yyvsp[0].expression)};
							(yyval.expression) = ParseTreeGenerator::createExpression(child,"rel_expression");
							(yyval.expression)->setDataType(sem_anlzr->relOp((yyvsp[-2].expression),(yyvsp[-1].terminal)->getSymbol(),(yyvsp[0].expression)));
							
						}
#line 2165 "parser.tab.c"
    break;

  case 61: /* simple_expression: term  */
#line 633 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].expression)};
							(yyval.expression) = ParseTreeGenerator::createExpression(child,"simple_expression");
							(yyval.expression)->setDataType((yyvsp[0].expression)->getDataType());
							
						}
#line 2176 "parser.tab.c"
    break;

  case 62: /* simple_expression: simple_expression ADDOP term  */
#line 640 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-2].expression),(yyvsp[-1].terminal),(yyvsp[0].expression)};
							(yyval.expression) = ParseTreeGenerator::createExpression(child,"simple_expression");
							(yyval.expression)->setDataType(sem_anlzr->addOp((yyvsp[-2].expression),(yyvsp[-1].terminal)->getSymbol(),(yyvsp[0].expression)));
							
						}
#line 2187 "parser.tab.c"
    break;

  case 63: /* term: unary_expression  */
#line 649 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].expression)};
							(yyval.expression) = ParseTreeGenerator::createExpression(child,"term");
							(yyval.expression)->setDataType((yyvsp[0].expression)->getDataType());
							
						}
#line 2198 "parser.tab.c"
    break;

  case 64: /* term: term MULOP unary_expression  */
#line 656 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-2].expression),(yyvsp[-1].terminal),(yyvsp[0].expression)};
							(yyval.expression) = ParseTreeGenerator::createExpression(child,"term");
							(yyval.expression)->setDataType(sem_anlzr->mulOp((yyvsp[-2].expression),(yyvsp[-1].terminal)->getSymbol(),(yyvsp[0].expression)));						
							
						}
#line 2209 "parser.tab.c"
    break;

  case 65: /* unary_expression: ADDOP unary_expression  */
#line 665 "src/parser.y"
                                                { 
							vector<SymbolInfo*> child = {(yyvsp[-1].terminal),(yyvsp[0].expression)};
							(yyval.expression) = ParseTreeGenerator::createExpression({(yyvsp[-1].terminal),(yyvsp[0].expression)},"unary_expression");
							(yyval.expression)->setDataType((yyvsp[0].expression)->getDataType());
							
						}
#line 2220 "parser.tab.c"
    break;

  case 66: /* unary_expression: NOT unary_expression  */
#line 672 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-1].terminal),(yyvsp[0].expression)};
							(yyval.expression) = ParseTreeGenerator::createExpression(child,"unary_expression");
							(yyval.expression)->setDataType((yyvsp[0].expression)->getDataType());
							
						}
#line 2231 "parser.tab.c"
    break;

  case 67: /* unary_expression: factor  */
#line 679 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].expression)};
							(yyval.expression) = ParseTreeGenerator::createExpression(child,"unary_expression");
							(yyval.expression)->setDataType((yyvsp[0].expression)->getDataType());
							
						}
#line 2242 "parser.tab.c"
    break;

  case 68: /* factor: variable  */
#line 688 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].expression)};
							(yyval.expression) = ParseTreeGenerator::createExpression(child,"factor");
							(yyval.expression)->setDataType((yyvsp[0].expression)->getDataType());
							
						}
#line 2253 "parser.tab.c"
    break;

  case 69: /* factor: ID LPAREN argument_list RPAREN  */
#line 695 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-3].terminal),(yyvsp[-2].terminal),(yyvsp[-1].args),(yyvsp[0].terminal)};
							(yyval.expression) = ParseTreeGenerator::createExpression(child,"factor");
							(yyval.expression)->setDataType(sem_anlzr->callFunction((yyvsp[-3].terminal)->getSymbol(), (yyvsp[-1].args)->getArgs()));
							
						}
#line 2264 "parser.tab.c"
    break;

  case 70: /* factor: LPAREN expression RPAREN  */
#line 702 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-2].terminal),(yyvsp[-1].expression),(yyvsp[0].terminal)};
							(yyval.expression) = ParseTreeGenerator::createExpression(child,"factor");
							(yyval.expression)->setDataType((yyvsp[-1].expression)->getDataType());
							
						}
#line 2275 "parser.tab.c"
    break;

  case 71: /* factor: CONST_INT  */
#line 709 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].terminal)};
							(yyval.expression) = ParseTreeGenerator::createExpression(child,"factor");
							(yyval.expression)->setDataType("INT");
							
						}
#line 2286 "parser.tab.c"
    break;

  case 72: /* factor: CONST_FLOAT  */
#line 716 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].terminal)};
							(yyval.expression) = ParseTreeGenerator::createExpression(child,"factor");
							(yyval.expression)->setDataType("FLOAT");
							
						}
#line 2297 "parser.tab.c"
    break;

  case 73: /* factor: variable INCOP  */
#line 723 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-1].expression),(yyvsp[0].terminal)};
							(yyval.expression) = ParseTreeGenerator::createExpression(child,"factor");
							(yyval.expression)->setDataType((yyvsp[-1].expression)->getDataType());	
							
						}
#line 2308 "parser.tab.c"
    break;

  case 74: /* factor: variable DECOP  */
#line 730 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-1].expression),(yyvsp[0].terminal)};
							(yyval.expression) = ParseTreeGenerator::createExpression(child,"factor");
							(yyval.expression)->setDataType((yyvsp[-1].expression)->getDataType());
							
						}
#line 2319 "parser.tab.c"
    break;

  case 75: /* argument_list: arguments  */
#line 739 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].args)};
							(yyval.args) = ParseTreeGenerator::createArgumentList(child,"argument_list");
							(yyval.args)->addArgs((yyvsp[0].args));
							
						}
#line 2330 "parser.tab.c"
    break;

  case 76: /* argument_list: arguments error  */
#line 747 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-1].args)};
							SymbolInfo *s = ParseTreeGenerator::createErrorNode(sem_anlzr->getLineCount());
							(yyval.args) = ParseTreeGenerator::createArgumentList(child,"argument_list");
							(yyval.args)->addArgs((yyvsp[-1].args));
							syntax_error("argument list","arguments");
							
						}
#line 2343 "parser.tab.c"
    break;

  case 77: /* argument_list: %empty  */
#line 756 "src/parser.y"
                                                { 
							vector<SymbolInfo*> child = {};
							(yyval.args) = ParseTreeGenerator::createArgumentList(child,"argument_list");			
						}
#line 2352 "parser.tab.c"
    break;

  case 78: /* arguments: arguments COMMA logic_expression  */
#line 763 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[-2].args),(yyvsp[-1].terminal),(yyvsp[0].expression)};
							(yyval.args) = ParseTreeGenerator::createArgumentList(child,"arguments");
							(yyval.args)->addArgs((yyvsp[-2].args));
							(yyval.args)->addArg((yyvsp[0].expression));
							
						}
#line 2364 "parser.tab.c"
    break;

  case 79: /* arguments: logic_expression  */
#line 771 "src/parser.y"
                                                {
							vector<SymbolInfo*> child = {(yyvsp[0].expression)};
							(yyval.args) = ParseTreeGenerator::createArgumentList(child,"arguments");
							(yyval.args)->addArg((yyvsp[0].expression));
						}
#line 2374 "parser.tab.c"
    break;


#line 2378 "parser.tab.c"

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

#line 781 "src/parser.y"


void runParser(FILE *fin)
{
	yyin = fin;
    yyparse();
}

// Arguments of argument list
// Parameter list of function definition/declaration
// Declaration list of var declaration
// Unit
