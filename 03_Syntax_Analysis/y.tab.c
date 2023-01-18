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
#include "../01_Symbol_Table/1905072_SymbolTable.h"
#include "../01_Symbol_Table/1905072_SymbolInfo.h"
#include "../01_Symbol_Table/1905072_ScopeTable.h"
#include "1905072_Logger.h"
#include "1905072_Node.h"

using namespace std;

ofstream logout;
ofstream errout;
ofstream tokenout;

int yyparse(void);
int yylex(void);
extern FILE *yyin;
extern int yylineno;
// SymbolTable *table;
int line_count;
int error_count;
SymbolTable *table;
unsigned long sdbmHash(string str)
{
    unsigned long hash = 0;
    for (auto ch : str)
    {
        int c = ch;
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}

void ScopeTable::print()
{
    logout << "ScopeTable # " << id << endl;
    for (int i = 0; i < n_buckets; i++)
    {
        SymbolInfo *cur = hash_table[i];
        if (cur == nullptr)
        {
            continue;
        }
        logout << " " << i << " --> ";

        while (cur != nullptr)
        {
            logout << "< " << cur->getName() << " : " << cur->getType() << "> ";
            cur = cur->getNext();
        }
        logout << endl;
    }
    logout << endl;
}

void yyerror(string s){
	logout<<"Error at line "<<line_count<<": "<<s<<"\n"<<endl;
	errout<<"Error at line "<<line_count<<": "<<s<<"\n"<<endl;
    error_count++;
}



#line 139 "y.tab.c"

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
#line 71 "1905072_parser.y"

    SymbolInfo* symbol;
	Node* node;

#line 279 "y.tab.c"

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
  YYSYMBOL_LCURL_2 = 54,                   /* LCURL_2  */
  YYSYMBOL_var_declaration = 55,           /* var_declaration  */
  YYSYMBOL_type_specifier = 56,            /* type_specifier  */
  YYSYMBOL_declaration_list = 57,          /* declaration_list  */
  YYSYMBOL_statements = 58,                /* statements  */
  YYSYMBOL_statement = 59,                 /* statement  */
  YYSYMBOL_expression_statement = 60,      /* expression_statement  */
  YYSYMBOL_variable = 61,                  /* variable  */
  YYSYMBOL_expression = 62,                /* expression  */
  YYSYMBOL_logic_expression = 63,          /* logic_expression  */
  YYSYMBOL_rel_expression = 64,            /* rel_expression  */
  YYSYMBOL_simple_expression = 65,         /* simple_expression  */
  YYSYMBOL_term = 66,                      /* term  */
  YYSYMBOL_unary_expression = 67,          /* unary_expression  */
  YYSYMBOL_factor = 68,                    /* factor  */
  YYSYMBOL_argument_list = 69,             /* argument_list  */
  YYSYMBOL_arguments = 70                  /* arguments  */
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
#define YYLAST   269

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  86
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
       0,    91,    91,    98,   105,   114,   121,   128,   137,   149,
     161,   173,   185,   196,   207,   218,   231,   231,   243,   243,
     255,   255,   266,   266,   280,   287,   294,   301,   308,   315,
     325,   335,   345,   355,   365,   377,   379,   390,   403,   410,
     417,   426,   435,   444,   453,   462,   470,   480,   487,   494,
     503,   510,   517,   524,   535,   542,   553,   560,   567,   576,
     583,   592,   599,   608,   615,   624,   631,   640,   647,   656,
     663,   672,   679,   688,   695,   702,   711,   718,   725,   732,
     739,   746,   753,   762,   770,   776,   783
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
  "parameter_list", "compound_statement", "LCURL_2", "var_declaration",
  "type_specifier", "declaration_list", "statements", "statement",
  "expression_statement", "variable", "expression", "logic_expression",
  "rel_expression", "simple_expression", "term", "unary_expression",
  "factor", "argument_list", "arguments", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-89)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-21)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      77,   -89,   -89,   -89,    32,    77,   -89,   -89,   -89,   -89,
     -21,   -89,   -89,    41,    13,    96,    14,     7,    17,   -89,
      36,    15,    37,    31,    54,    48,   -89,    68,    66,   -89,
     -89,    82,    -1,    29,    77,   -89,   -89,    87,    83,   252,
      82,   -89,   -89,    67,    33,    77,   -89,   -89,    82,   100,
      86,    99,   -89,   -89,   167,   120,   123,   127,   109,   109,
     128,   109,   -89,   -89,    81,   -89,   -89,   109,   -89,   -89,
     121,   103,   -89,   -89,    51,   124,   -89,   122,   -13,   130,
     -89,   -89,   -89,   -89,    82,   125,   -89,   -89,   129,   -89,
     -89,   139,   109,   -14,   109,   133,   104,   -89,   137,   134,
     109,   109,   -89,   151,   195,   -89,   -89,   -89,   -89,   109,
     -89,   109,   109,   109,   109,   -89,   -89,   -89,   223,   -89,
     155,   -14,   156,   -89,   158,   -89,   -89,   160,   157,   159,
     -89,   -89,   -89,   -89,   130,   150,   -89,   223,   109,   223,
     161,   -89,   109,   -89,   193,   172,   -89,   -89,   -89,   223,
     223,   -89,   -89
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    38,    39,    40,     0,     2,     4,     6,     7,     5,
       0,     1,     3,    45,     0,     0,     0,     0,     0,    36,
       0,     0,     0,    29,     0,     0,    37,    41,    22,    13,
      12,     0,     0,     0,     0,    28,    46,    42,     0,     0,
       0,    35,    21,     0,     0,     0,     9,     8,     0,    26,
       0,     0,    15,    23,     0,     0,     0,     0,     0,     0,
       0,     0,    33,    59,    61,    79,    80,     0,    52,    50,
       0,     0,    47,    51,    76,     0,    63,    65,    67,    69,
      71,    75,    11,    10,     0,    27,    17,    24,     0,    43,
      34,     0,     0,     0,     0,     0,    76,    74,     0,     0,
      84,     0,    73,    45,     0,    30,    48,    81,    82,     0,
      60,     0,     0,     0,     0,    19,    25,    44,     0,    32,
       0,     0,     0,    58,     0,    78,    86,     0,    83,     0,
      31,    49,    64,    66,    70,    68,    72,     0,     0,     0,
       0,    77,     0,    62,    54,     0,    56,    57,    85,     0,
       0,    55,    53
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -89,   -89,   -89,   204,   -89,   -89,   -89,   -89,   -89,   -89,
     -89,   -25,   -89,   119,     2,   -89,   162,   -62,   -88,   -59,
     -57,   -82,   102,    97,   105,   -56,   -89,   -89,   -89
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     4,     5,     6,     7,     8,    48,    84,    31,    40,
      22,    68,    43,    69,    70,    14,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,   127,   128
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      96,    95,    10,    97,    99,   121,    42,    10,    96,   106,
      59,   102,    61,    13,    17,    53,    29,    23,   126,    63,
      64,    65,    66,    86,    67,   112,    44,   132,   113,   106,
      46,    45,    11,   138,    82,   120,    49,   122,    32,    25,
      26,    96,   131,   -20,   129,    18,    19,    85,    30,    24,
      96,    27,    96,    96,    96,    96,   131,   -16,   136,   115,
     148,   -18,    47,    28,    33,    35,    83,    15,    54,    34,
      55,    16,   107,   108,   109,   144,    56,   146,    57,     1,
       2,   145,    37,    96,     3,    36,    58,   151,   152,     1,
       2,    59,    60,    61,     3,    41,    62,    20,    38,    39,
      63,    64,    65,    66,   104,    67,    55,   100,     1,     2,
      41,   101,    56,     3,    57,     1,     2,    50,    51,     9,
       3,    88,    58,    21,     9,   107,   108,    59,    60,    61,
      89,    41,   105,    59,    87,    61,    63,    64,    65,    66,
     118,    67,    55,    64,    65,    66,    92,    67,    56,    93,
      57,     1,     2,    94,    98,   103,     3,   110,    58,   116,
     117,   125,   111,    59,    60,    61,   123,    41,   119,   114,
      55,   124,    63,    64,    65,    66,    56,    67,    57,     1,
       2,    16,   137,   139,     3,   140,    58,   141,   112,   142,
     143,    59,    60,    61,   147,    41,    90,   149,    55,   150,
      63,    64,    65,    66,    56,    67,    57,     1,     2,    12,
     135,     0,     3,   133,    58,     0,    91,   134,     0,    59,
      60,    61,     0,    41,   130,     0,    55,     0,    63,    64,
      65,    66,    56,    67,    57,     1,     2,     0,     0,     0,
       3,     0,    58,     0,     0,     0,     0,    59,    60,    61,
       0,    41,   -14,    52,     0,     0,    63,    64,    65,    66,
       0,    67,     0,     0,   -14,   -14,     0,     0,     0,   -14
};

static const yytype_int16 yycheck[] =
{
      59,    58,     0,    59,    61,    93,    31,     5,    67,    71,
      24,    67,    26,    34,     1,    40,     1,    15,   100,    33,
      34,    35,    36,    48,    38,    38,    27,   109,    41,    91,
       1,    32,     0,   121,     1,    92,    34,    94,     1,    32,
      33,   100,   104,    28,   101,    32,    33,    45,    33,    35,
     109,    34,   111,   112,   113,   114,   118,    28,   114,    84,
     142,    28,    33,    27,    27,    34,    33,    26,     1,    32,
       3,    30,    21,    22,    23,   137,     9,   139,    11,    12,
      13,   138,    34,   142,    17,    31,    19,   149,   150,    12,
      13,    24,    25,    26,    17,    28,    29,     1,    30,    33,
      33,    34,    35,    36,     1,    38,     3,    26,    12,    13,
      28,    30,     9,    17,    11,    12,    13,    30,    35,     0,
      17,    35,    19,    27,     5,    21,    22,    24,    25,    26,
      31,    28,    29,    24,    34,    26,    33,    34,    35,    36,
       1,    38,     3,    34,    35,    36,    26,    38,     9,    26,
      11,    12,    13,    26,    26,    34,    17,    33,    19,    34,
      31,    27,    40,    24,    25,    26,    33,    28,    29,    39,
       3,    34,    33,    34,    35,    36,     9,    38,    11,    12,
      13,    30,    27,    27,    17,    27,    19,    27,    38,    32,
      31,    24,    25,    26,    33,    28,    29,     4,     3,    27,
      33,    34,    35,    36,     9,    38,    11,    12,    13,     5,
     113,    -1,    17,   111,    19,    -1,    54,   112,    -1,    24,
      25,    26,    -1,    28,    29,    -1,     3,    -1,    33,    34,
      35,    36,     9,    38,    11,    12,    13,    -1,    -1,    -1,
      17,    -1,    19,    -1,    -1,    -1,    -1,    24,    25,    26,
      -1,    28,     0,     1,    -1,    -1,    33,    34,    35,    36,
      -1,    38,    -1,    -1,    12,    13,    -1,    -1,    -1,    17
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    12,    13,    17,    43,    44,    45,    46,    47,    55,
      56,     0,    45,    34,    57,    26,    30,     1,    32,    33,
       1,    27,    52,    56,    35,    32,    33,    34,    27,     1,
      33,    50,     1,    27,    32,    34,    31,    34,    30,    33,
      51,    28,    53,    54,    27,    32,     1,    33,    48,    56,
      30,    35,     1,    53,     1,     3,     9,    11,    19,    24,
      25,    26,    29,    33,    34,    35,    36,    38,    53,    55,
      56,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,     1,    33,    49,    56,    53,    34,    35,    31,
      29,    58,    26,    26,    26,    62,    61,    67,    26,    62,
      26,    30,    67,    34,     1,    29,    59,    21,    22,    23,
      33,    40,    38,    41,    39,    53,    34,    31,     1,    29,
      62,    60,    62,    33,    34,    27,    63,    69,    70,    62,
      29,    59,    63,    64,    66,    65,    67,    27,    60,    27,
      27,    27,    32,    31,    59,    62,    59,    33,    63,     4,
      27,    59,    59
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    45,    45,    46,    46,
      46,    46,    46,    46,    46,    46,    48,    47,    49,    47,
      50,    47,    51,    47,    52,    52,    52,    52,    52,    52,
      53,    53,    53,    53,    53,    54,    55,    55,    56,    56,
      56,    57,    57,    57,    57,    57,    57,    58,    58,    58,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    60,
      60,    61,    61,    62,    62,    63,    63,    64,    64,    65,
      65,    66,    66,    67,    67,    67,    68,    68,    68,    68,
      68,    68,    68,    69,    69,    70,    70
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     6,
       7,     7,     5,     5,     6,     7,     0,     7,     0,     8,
       0,     6,     0,     7,     4,     5,     3,     4,     2,     1,
       3,     4,     4,     2,     3,     1,     3,     4,     1,     1,
       1,     3,     4,     6,     7,     1,     4,     1,     2,     3,
       1,     1,     1,     7,     5,     7,     5,     5,     3,     1,
       2,     1,     4,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     2,     2,     1,     1,     4,     3,     1,
       1,     2,     2,     1,     0,     3,     1
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
#line 92 "1905072_parser.y"
                {
			printRule("start","program");
			cout<<"Code compiled successfully"<<endl;
		}
#line 1727 "y.tab.c"
    break;

  case 3: /* program: program unit  */
#line 99 "1905072_parser.y"
                {
			printRule("program","program unit");
			(yyval.node) = new Node();
            (yyval.node)->setCode((yyvsp[-1].node)->getCode()+"\n\n"+(yyvsp[0].node)->getCode());
            printCode((yyval.node)->getCode()); 
		}
#line 1738 "y.tab.c"
    break;

  case 4: /* program: unit  */
#line 106 "1905072_parser.y"
                {
			printRule("program","unit");
			(yyval.node) = new Node();
            (yyval.node)->setCode((yyvsp[0].node)->getCode());
            printCode((yyval.node)->getCode()); 
		}
#line 1749 "y.tab.c"
    break;

  case 5: /* unit: var_declaration  */
#line 115 "1905072_parser.y"
                {
			printRule("unit","var_declaration");
			(yyval.node) = new Node();
            (yyval.node)->setCode((yyvsp[0].node)->getCode());
            printCode((yyval.node)->getCode()); 
		}
#line 1760 "y.tab.c"
    break;

  case 6: /* unit: func_declaration  */
#line 122 "1905072_parser.y"
                {
			printRule("unit","func_declaration");
			(yyval.node) = new Node();
            (yyval.node)->setCode((yyvsp[0].node)->getCode());
            printCode((yyval.node)->getCode()); 
		}
#line 1771 "y.tab.c"
    break;

  case 7: /* unit: func_definition  */
#line 129 "1905072_parser.y"
                {
			printRule("unit","func_definition");	
			(yyval.node) = new Node();
            (yyval.node)->setCode((yyvsp[0].node)->getCode());
            printCode((yyval.node)->getCode()); 
		}
#line 1782 "y.tab.c"
    break;

  case 8: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON  */
#line 138 "1905072_parser.y"
                                        {
						printRule("func_declaration","type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
						(yyval.node) = new Node();
						(yyval.node)->setCode(
							(yyvsp[-5].node)->getCode()+" "+
							(yyvsp[-4].symbol)->getName()+"("+
							(yyvsp[-2].node)->getCode()+")"+";"
						);
						table->insert(*(yyvsp[-4].symbol));
						printCode((yyval.node)->getCode());
					}
#line 1798 "y.tab.c"
    break;

  case 9: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN error  */
#line 150 "1905072_parser.y"
                                        {
						printRule("func_declaration","type_specifier ID LPAREN parameter_list RPAREN");
						(yyval.node) = new Node();
						(yyval.node)->setCode(
							(yyvsp[-5].node)->getCode()+" "+
							(yyvsp[-4].symbol)->getName()+"("+
							(yyvsp[-2].node)->getCode()+")"
						);
						table->insert(*(yyvsp[-4].symbol));
						printCode((yyval.node)->getCode());
					}
#line 1814 "y.tab.c"
    break;

  case 10: /* func_declaration: type_specifier ID LPAREN parameter_list error RPAREN SEMICOLON  */
#line 162 "1905072_parser.y"
                                        {
						printRule("func_declaration","type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
						(yyval.node) = new Node();
						(yyval.node)->setCode(
							(yyvsp[-6].node)->getCode()+" "+
							(yyvsp[-5].symbol)->getName()+"("+
							(yyvsp[-3].node)->getCode()+")"+";"
						);
						table->insert(*(yyvsp[-5].symbol));
						printCode((yyval.node)->getCode());
					}
#line 1830 "y.tab.c"
    break;

  case 11: /* func_declaration: type_specifier ID LPAREN parameter_list error RPAREN error  */
#line 174 "1905072_parser.y"
                                        {
						printRule("func_declaration","type_specifier ID LPAREN parameter_list RPAREN");
						(yyval.node) = new Node();
						(yyval.node)->setCode(
							(yyvsp[-6].node)->getCode()+" "+
							(yyvsp[-5].symbol)->getName()+"("+
							(yyvsp[-3].node)->getCode()+")"
						);
						table->insert(*(yyvsp[-5].symbol));
						printCode((yyval.node)->getCode());
					}
#line 1846 "y.tab.c"
    break;

  case 12: /* func_declaration: type_specifier ID LPAREN RPAREN SEMICOLON  */
#line 186 "1905072_parser.y"
                                        {
						printRule("func_declaration","type_specifier ID LPAREN RPAREN SEMICOLON");
						(yyval.node) = new Node();
						(yyval.node)->setCode(
							(yyvsp[-4].node)->getCode()+" "+
							(yyvsp[-3].symbol)->getName()+"("+")"+";"
						);
						table->insert(*(yyvsp[-3].symbol));
						printCode((yyval.node)->getCode());
					}
#line 1861 "y.tab.c"
    break;

  case 13: /* func_declaration: type_specifier ID LPAREN RPAREN error  */
#line 197 "1905072_parser.y"
                                        {
						printRule("func_declaration","type_specifier ID LPAREN RPAREN");
						(yyval.node) = new Node();
						(yyval.node)->setCode(
							(yyvsp[-4].node)->getCode()+" "+
							(yyvsp[-3].symbol)->getName()+"("+")"
						);
						table->insert(*(yyvsp[-3].symbol));
						printCode((yyval.node)->getCode());
					}
#line 1876 "y.tab.c"
    break;

  case 14: /* func_declaration: type_specifier ID LPAREN error RPAREN SEMICOLON  */
#line 208 "1905072_parser.y"
                                        {
						printRule("func_declaration","type_specifier ID LPAREN RPAREN SEMICOLON");
						(yyval.node) = new Node();
						(yyval.node)->setCode(
							(yyvsp[-5].node)->getCode()+" "+
							(yyvsp[-4].symbol)->getName()+"("+")"+";"
						);
						table->insert(*(yyvsp[-4].symbol));
						printCode((yyval.node)->getCode());
					}
#line 1891 "y.tab.c"
    break;

  case 15: /* func_declaration: type_specifier ID LPAREN error RPAREN SEMICOLON error  */
#line 219 "1905072_parser.y"
                                        {
						printRule("func_declaration","type_specifier ID LPAREN RPAREN");
						(yyval.node) = new Node();
						(yyval.node)->setCode(
							(yyvsp[-6].node)->getCode()+" "+
							(yyvsp[-5].symbol)->getName()+"("+")"
						);
						table->insert(*(yyvsp[-5].symbol));
						printCode((yyval.node)->getCode());
					}
#line 1906 "y.tab.c"
    break;

  case 16: /* $@1: %empty  */
#line 231 "1905072_parser.y"
                                                                 {table->insert(*(yyvsp[-3].symbol));}
#line 1912 "y.tab.c"
    break;

  case 17: /* func_definition: type_specifier ID LPAREN parameter_list RPAREN $@1 compound_statement  */
#line 232 "1905072_parser.y"
                                {
					printRule("func_definition","func_defintype_specifier ID LPAREN parameter_list RPAREN compound_statement");
					(yyval.node) = new Node();
					(yyval.node)->setCode(
						(yyvsp[-6].node)->getCode()+" "+
						(yyvsp[-5].symbol)->getName()+"("+
						(yyvsp[-3].node)->getCode()+")"+
						(yyvsp[0].node)->getCode()
					);
					printCode((yyval.node)->getCode());
				}
#line 1928 "y.tab.c"
    break;

  case 18: /* $@2: %empty  */
#line 243 "1905072_parser.y"
                                                                                       {table->insert(*(yyvsp[-4].symbol));}
#line 1934 "y.tab.c"
    break;

  case 19: /* func_definition: type_specifier ID LPAREN parameter_list error RPAREN $@2 compound_statement  */
#line 244 "1905072_parser.y"
                                {
					printRule("func_definition","func_defintype_specifier ID LPAREN parameter_list RPAREN compound_statement");
					(yyval.node) = new Node();
					(yyval.node)->setCode(
						(yyvsp[-7].node)->getCode()+" "+
						(yyvsp[-6].symbol)->getName()+"("+
						(yyvsp[-4].node)->getCode()+")"+
						(yyvsp[0].node)->getCode()
					);
					printCode((yyval.node)->getCode());
				}
#line 1950 "y.tab.c"
    break;

  case 20: /* $@3: %empty  */
#line 255 "1905072_parser.y"
                                                                  {table->insert(*(yyvsp[-2].symbol));}
#line 1956 "y.tab.c"
    break;

  case 21: /* func_definition: type_specifier ID LPAREN RPAREN $@3 compound_statement  */
#line 256 "1905072_parser.y"
                                {
					printRule("func_definition","type_specifier ID LPAREN RPAREN compound_statement");
					(yyval.node) = new Node();
					(yyval.node)->setCode(
						(yyvsp[-5].node)->getCode()+" "+
						(yyvsp[-4].symbol)->getName()+"()"+
						(yyvsp[0].node)->getCode()
					);
					printCode((yyval.node)->getCode());
				}
#line 1971 "y.tab.c"
    break;

  case 22: /* $@4: %empty  */
#line 266 "1905072_parser.y"
                                                                        {table->insert(*(yyvsp[-3].symbol));}
#line 1977 "y.tab.c"
    break;

  case 23: /* func_definition: type_specifier ID LPAREN error RPAREN $@4 compound_statement  */
#line 267 "1905072_parser.y"
                                {
					printRule("func_definition","type_specifier ID LPAREN RPAREN compound_statement");
					(yyval.node) = new Node();
					(yyval.node)->setCode(
						(yyvsp[-6].node)->getCode()+" "+
						(yyvsp[-5].symbol)->getName()+"()"+
						(yyvsp[0].node)->getCode()
					);
					printCode((yyval.node)->getCode());
				}
#line 1992 "y.tab.c"
    break;

  case 24: /* parameter_list: parameter_list COMMA type_specifier ID  */
#line 281 "1905072_parser.y"
                                {
					printRule("parameter_list","parameter_list COMMA type_specifier ID");
					(yyval.node) = new Node();
					(yyval.node)->setCode((yyvsp[-3].node)->getCode()+","+(yyvsp[-1].node)->getCode()+" "+(yyvsp[0].symbol)->getName());
					printCode((yyval.node)->getCode());
				}
#line 2003 "y.tab.c"
    break;

  case 25: /* parameter_list: parameter_list error COMMA type_specifier ID  */
#line 288 "1905072_parser.y"
                                {
					printRule("parameter_list","parameter_list COMMA type_specifier ID");
					(yyval.node) = new Node();
					(yyval.node)->setCode((yyvsp[-4].node)->getCode()+","+(yyvsp[-1].node)->getCode()+" "+(yyvsp[0].symbol)->getName());
					printCode((yyval.node)->getCode());
				}
#line 2014 "y.tab.c"
    break;

  case 26: /* parameter_list: parameter_list COMMA type_specifier  */
#line 295 "1905072_parser.y"
                                {
					printRule("parameter_list","parameter_list COMMA type_specifier ID");
					(yyval.node) = new Node();
					(yyval.node)->setCode((yyvsp[-2].node)->getCode()+","+(yyvsp[0].node)->getCode());
					printCode((yyval.node)->getCode());
				}
#line 2025 "y.tab.c"
    break;

  case 27: /* parameter_list: parameter_list error COMMA type_specifier  */
#line 302 "1905072_parser.y"
                                {
					printRule("parameter_list","parameter_list COMMA type_specifier ID");
					(yyval.node) = new Node();
					(yyval.node)->setCode((yyvsp[-3].node)->getCode()+","+(yyvsp[0].node)->getCode());
					printCode((yyval.node)->getCode());
				}
#line 2036 "y.tab.c"
    break;

  case 28: /* parameter_list: type_specifier ID  */
#line 309 "1905072_parser.y"
                                {
					printRule("parameter_list","type_specifier ID");
					(yyval.node) = new Node();
					(yyval.node)->setCode((yyvsp[-1].node)->getCode()+" "+(yyvsp[0].symbol)->getName());
					printCode((yyval.node)->getCode());
				}
#line 2047 "y.tab.c"
    break;

  case 29: /* parameter_list: type_specifier  */
#line 316 "1905072_parser.y"
                                {
					printRule("parameter_list","type_specifier");
					(yyval.node) = new Node();
					(yyval.node)->setCode((yyvsp[0].node)->getCode());
					printCode((yyval.node)->getCode());
				}
#line 2058 "y.tab.c"
    break;

  case 30: /* compound_statement: LCURL_2 statements RCURL  */
#line 326 "1905072_parser.y"
                                                {
							printRule("compound_statement","LCURL statements RCURL");
							(yyval.node) = new Node();
							(yyval.node)->setCode("{\n" + (yyvsp[-1].node)->getCode() + "\n}"); 
							printCode((yyval.node)->getCode());

							table->printAllScope();
							table->exitScope();
						}
#line 2072 "y.tab.c"
    break;

  case 31: /* compound_statement: LCURL_2 statements error RCURL  */
#line 336 "1905072_parser.y"
                                                {
							printRule("compound_statement","LCURL statements RCURL");
							(yyval.node) = new Node();
							(yyval.node)->setCode("{\n" + (yyvsp[-2].node)->getCode() + "\n}"); 
							printCode((yyval.node)->getCode());

							table->printAllScope();
							table->exitScope();
						}
#line 2086 "y.tab.c"
    break;

  case 32: /* compound_statement: LCURL_2 error statements RCURL  */
#line 346 "1905072_parser.y"
                                                {
							printRule("compound_statement","LCURL statements RCURL");
							(yyval.node) = new Node();
							(yyval.node)->setCode("{\n" + (yyvsp[-1].node)->getCode() + "\n}"); 
							printCode((yyval.node)->getCode());

							table->printAllScope();
							table->exitScope();
						}
#line 2100 "y.tab.c"
    break;

  case 33: /* compound_statement: LCURL_2 RCURL  */
#line 356 "1905072_parser.y"
                                                {
							printRule("compound_statement","LCURL RCURL");
							(yyval.node) = new Node();
							(yyval.node)->setCode("{}"); 
							printCode((yyval.node)->getCode());

							table->printAllScope();
							table->exitScope();
						}
#line 2114 "y.tab.c"
    break;

  case 34: /* compound_statement: LCURL_2 error RCURL  */
#line 366 "1905072_parser.y"
                                                {
							printRule("compound_statement","LCURL RCURL");
							(yyval.node) = new Node();
							(yyval.node)->setCode("{}"); 
							printCode((yyval.node)->getCode());

							table->printAllScope();
							table->exitScope();
						}
#line 2128 "y.tab.c"
    break;

  case 35: /* LCURL_2: LCURL  */
#line 377 "1905072_parser.y"
                      { table->enterScope(); }
#line 2134 "y.tab.c"
    break;

  case 36: /* var_declaration: type_specifier declaration_list SEMICOLON  */
#line 380 "1905072_parser.y"
                                { 
					printRule("var_declaration","type_specifier declaration_list SEMICOLON"); 					
					(yyval.node) = new Node();
					(yyval.node)->setCode((yyvsp[-2].node)->getCode()+" "+(yyvsp[-1].node)->getCode()+";");
					for(auto i:(yyvsp[-1].node)->getList())
					{
						table->insert(*i);
					}
					printCode((yyval.node)->getCode());
				}
#line 2149 "y.tab.c"
    break;

  case 37: /* var_declaration: type_specifier declaration_list error SEMICOLON  */
#line 391 "1905072_parser.y"
                                { 
					printRule("var_declaration","type_specifier declaration_list SEMICOLON"); 					
					(yyval.node) = new Node();
					(yyval.node)->setCode((yyvsp[-3].node)->getCode()+" "+(yyvsp[-2].node)->getCode()+";");
					for(auto i:(yyvsp[-2].node)->getList())
					{
						table->insert(*i);
					}
					printCode((yyval.node)->getCode());
				}
#line 2164 "y.tab.c"
    break;

  case 38: /* type_specifier: INT  */
#line 404 "1905072_parser.y"
                                { 
					printRule("type_specifier","INT"); 
					(yyval.node) = new Node();
					(yyval.node)->setCode("int"); 
					printCode((yyval.node)->getCode());
				}
#line 2175 "y.tab.c"
    break;

  case 39: /* type_specifier: FLOAT  */
#line 411 "1905072_parser.y"
                                {
					printRule("type_specifier","FLOAT"); 
					(yyval.node) = new Node();
					(yyval.node)->setCode("float"); 
					printCode((yyval.node)->getCode());
				}
#line 2186 "y.tab.c"
    break;

  case 40: /* type_specifier: VOID  */
#line 418 "1905072_parser.y"
                                {
					printRule("type_specifier","VOID"); 
					(yyval.node) = new Node();
					(yyval.node)->setCode("void"); 
					printCode((yyval.node)->getCode());
				}
#line 2197 "y.tab.c"
    break;

  case 41: /* declaration_list: declaration_list COMMA ID  */
#line 427 "1905072_parser.y"
                                        {
						printRule("declaration_list","declaration_list COMMA ID");
						(yyval.node) = new Node();
						(yyval.node)->setCode((yyvsp[-2].node)->getCode()+","+(yyvsp[0].symbol)->getName());
						(yyval.node)->setList((yyvsp[-2].node)->getList());
						(yyval.node)->getList().push_back((yyvsp[0].symbol));
						printCode((yyval.node)->getCode());
					}
#line 2210 "y.tab.c"
    break;

  case 42: /* declaration_list: declaration_list error COMMA ID  */
#line 436 "1905072_parser.y"
                                        {
						printRule("declaration_list","declaration_list COMMA ID");
						(yyval.node) = new Node();
						(yyval.node)->setCode((yyvsp[-3].node)->getCode()+","+(yyvsp[0].symbol)->getName());
						(yyval.node)->setList((yyvsp[-3].node)->getList());
						(yyval.node)->getList().push_back((yyvsp[0].symbol));
						printCode((yyval.node)->getCode());
					}
#line 2223 "y.tab.c"
    break;

  case 43: /* declaration_list: declaration_list COMMA ID LTHIRD CONST_INT RTHIRD  */
#line 445 "1905072_parser.y"
                                        {
						printRule("declaration_list","declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
						(yyval.node) = new Node();
						(yyval.node)->setCode((yyvsp[-5].node)->getCode()+","+(yyvsp[-3].symbol)->getName()+"["+(yyvsp[-1].symbol)->getName()+"]");
						(yyval.node)->setList((yyvsp[-5].node)->getList());
						(yyval.node)->getList().push_back((yyvsp[-3].symbol));
						printCode((yyval.node)->getCode());
					}
#line 2236 "y.tab.c"
    break;

  case 44: /* declaration_list: declaration_list error COMMA ID LTHIRD CONST_INT RTHIRD  */
#line 454 "1905072_parser.y"
                                        {
						printRule("declaration_list","declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
						(yyval.node) = new Node();
						(yyval.node)->setCode((yyvsp[-6].node)->getCode()+","+(yyvsp[-3].symbol)->getName()+"["+(yyvsp[-1].symbol)->getName()+"]");
						(yyval.node)->setList((yyvsp[-6].node)->getList());
						(yyval.node)->getList().push_back((yyvsp[-3].symbol));
						printCode((yyval.node)->getCode());
					}
#line 2249 "y.tab.c"
    break;

  case 45: /* declaration_list: ID  */
#line 463 "1905072_parser.y"
                                        { 
						printRule("declaration_list","ID"); 
						(yyval.node) = new Node();
						(yyval.node)->setCode((yyvsp[0].symbol)->getName());
						(yyval.node)->getList().push_back((yyvsp[0].symbol));
						printCode((yyval.node)->getCode());
					}
#line 2261 "y.tab.c"
    break;

  case 46: /* declaration_list: ID LTHIRD CONST_INT RTHIRD  */
#line 471 "1905072_parser.y"
                                        {
						printRule("declaration_list","ID LTHIRD CONST_INT RTHIRD");
						(yyval.node) = new Node();
						(yyval.node)->setCode((yyvsp[-3].symbol)->getName()+"["+(yyvsp[-1].symbol)->getName()+"]");
						(yyval.node)->getList().push_back((yyvsp[-3].symbol));
						printCode((yyval.node)->getCode());
					}
#line 2273 "y.tab.c"
    break;

  case 47: /* statements: statement  */
#line 481 "1905072_parser.y"
                        {
				printRule("statements","statement");
				(yyval.node) = new Node();
            	(yyval.node)->setCode((yyvsp[0].node)->getCode());
            	printCode((yyval.node)->getCode());
			}
#line 2284 "y.tab.c"
    break;

  case 48: /* statements: statements statement  */
#line 488 "1905072_parser.y"
                        {
				printRule("statements","statements statement");
				(yyval.node) = new Node();
				(yyval.node)->setCode((yyvsp[-1].node)->getCode() + "\n" + (yyvsp[0].node)->getCode());
				printCode((yyval.node)->getCode());
	   		}
#line 2295 "y.tab.c"
    break;

  case 49: /* statements: statements error statement  */
#line 495 "1905072_parser.y"
                        {
				printRule("statements","statements statement");
				(yyval.node) = new Node();
				(yyval.node)->setCode((yyvsp[-2].node)->getCode() + "\n" + (yyvsp[0].node)->getCode());
				printCode((yyval.node)->getCode());
			}
#line 2306 "y.tab.c"
    break;

  case 50: /* statement: var_declaration  */
#line 504 "1905072_parser.y"
                        {
				printRule("statement","var_declaration");
				(yyval.node) = new Node();
            	(yyval.node)->setCode((yyvsp[0].node)->getCode());
            	printCode((yyval.node)->getCode()); 
			}
#line 2317 "y.tab.c"
    break;

  case 51: /* statement: expression_statement  */
#line 511 "1905072_parser.y"
                        {
				printRule("statement","expression_statement");
				(yyval.node) = new Node();
            	(yyval.node)->setCode((yyvsp[0].node)->getCode());
            	printCode((yyval.node)->getCode()); 
			}
#line 2328 "y.tab.c"
    break;

  case 52: /* statement: compound_statement  */
#line 518 "1905072_parser.y"
                        {
				printRule("statement","compound_statement");
				(yyval.node) = new Node();
            	(yyval.node)->setCode((yyvsp[0].node)->getCode());
            	printCode((yyval.node)->getCode()); 
			}
#line 2339 "y.tab.c"
    break;

  case 53: /* statement: FOR LPAREN expression_statement expression_statement expression RPAREN statement  */
#line 525 "1905072_parser.y"
                        {
				printRule("statement","FOR LPAREN expression_statement expression_statement expression RPAREN statement");
				(yyval.node) = new Node();
            	(yyval.node)->setCode(
					"for("+(yyvsp[-4].node)->getCode()+
					(yyvsp[-3].node)->getCode()+(yyvsp[-2].node)->getCode()+
					")"+(yyvsp[0].node)->getCode()
				);
            	printCode((yyval.node)->getCode()); 
			}
#line 2354 "y.tab.c"
    break;

  case 54: /* statement: IF LPAREN expression RPAREN statement  */
#line 536 "1905072_parser.y"
                        {
				printRule("statement","IF LPAREN expression RPAREN statement");
				(yyval.node) = new Node();
            	(yyval.node)->setCode("if("+(yyvsp[-2].node)->getCode()+")"+(yyvsp[0].node)->getCode());
            	printCode((yyval.node)->getCode()); 
			}
#line 2365 "y.tab.c"
    break;

  case 55: /* statement: IF LPAREN expression RPAREN statement ELSE statement  */
#line 543 "1905072_parser.y"
                        {
				printRule("statement","IF LPAREN expression RPAREN statement ELSE statement");
				(yyval.node) = new Node();
            	(yyval.node)->setCode(
					"if("+(yyvsp[-4].node)->getCode()+")"+
					(yyvsp[-2].node)->getCode()+"\nelse "+
					(yyvsp[0].node)->getCode()
				);
            	printCode((yyval.node)->getCode()); 
			}
#line 2380 "y.tab.c"
    break;

  case 56: /* statement: WHILE LPAREN expression RPAREN statement  */
#line 554 "1905072_parser.y"
                        {
				printRule("statement","WHILE LPAREN expression RPAREN statement");
				(yyval.node) = new Node();
            	(yyval.node)->setCode("while("+(yyvsp[-2].node)->getCode()+")"+(yyvsp[0].node)->getCode());
            	printCode((yyval.node)->getCode()); 
			}
#line 2391 "y.tab.c"
    break;

  case 57: /* statement: PRINTLN LPAREN ID RPAREN SEMICOLON  */
#line 561 "1905072_parser.y"
                        {
				printRule("statement","PRINTLN LPAREN ID RPAREN SEMICOLON");
				(yyval.node) = new Node();
            	(yyval.node)->setCode("printf("+(yyvsp[-2].symbol)->getName()+");");
            	printCode((yyval.node)->getCode()); 
			}
#line 2402 "y.tab.c"
    break;

  case 58: /* statement: RETURN expression SEMICOLON  */
#line 568 "1905072_parser.y"
                        {
				printRule("statement","RETURN expression SEMICOLON");
				(yyval.node) = new Node();
            	(yyval.node)->setCode("return "+(yyvsp[-1].node)->getCode()+";");
            	printCode((yyval.node)->getCode()); 
			}
#line 2413 "y.tab.c"
    break;

  case 59: /* expression_statement: SEMICOLON  */
#line 577 "1905072_parser.y"
                                                {
							printRule("expression_statement","SEMICOLON");
							(yyval.node) = new Node();
							(yyval.node)->setCode(";");
							printCode((yyval.node)->getCode());
						}
#line 2424 "y.tab.c"
    break;

  case 60: /* expression_statement: expression SEMICOLON  */
#line 584 "1905072_parser.y"
                                                {
							printRule("expression_statement","expression SEMICOLON");
							(yyval.node) = new Node();
							(yyval.node)->setCode((yyvsp[-1].node)->getCode()+";");
							printCode((yyval.node)->getCode());
						}
#line 2435 "y.tab.c"
    break;

  case 61: /* variable: ID  */
#line 593 "1905072_parser.y"
                        {
				printRule("variable","ID");
				(yyval.node) = new Node();
            	(yyval.node)->setCode((yyvsp[0].symbol)->getName());
            	printCode((yyval.node)->getCode());
			}
#line 2446 "y.tab.c"
    break;

  case 62: /* variable: ID LTHIRD expression RTHIRD  */
#line 600 "1905072_parser.y"
                        {
				printRule("variable","ID LTHIRD expression RTHIRD");
				(yyval.node) = new Node();
            	(yyval.node)->setCode((yyvsp[-3].symbol)->getName()+"["+(yyvsp[-1].node)->getCode()+"]");
            	printCode((yyval.node)->getCode());
			}
#line 2457 "y.tab.c"
    break;

  case 63: /* expression: logic_expression  */
#line 609 "1905072_parser.y"
                        {
				printRule("expression","logic_expression");
				(yyval.node) = new Node();
				(yyval.node)->setCode((yyvsp[0].node)->getCode());
				printCode((yyval.node)->getCode());
			}
#line 2468 "y.tab.c"
    break;

  case 64: /* expression: variable ASSIGNOP logic_expression  */
#line 616 "1905072_parser.y"
                        {
				printRule("expression","variable ASSIGNOP logic_expression");
				(yyval.node) = new Node();
				(yyval.node)->setCode((yyvsp[-2].node)->getCode()+"="+(yyvsp[0].node)->getCode());
				printCode((yyval.node)->getCode());
			}
#line 2479 "y.tab.c"
    break;

  case 65: /* logic_expression: rel_expression  */
#line 625 "1905072_parser.y"
                                        {
						printRule("logic_expression","rel_expression");
						(yyval.node) = new Node();
						(yyval.node)->setCode((yyvsp[0].node)->getCode());
						printCode((yyval.node)->getCode());
					}
#line 2490 "y.tab.c"
    break;

  case 66: /* logic_expression: rel_expression LOGICOP rel_expression  */
#line 632 "1905072_parser.y"
                                        {
						printRule("logic_expression","rel_expression LOGICOP rel_expression");
						(yyval.node) = new Node();
						(yyval.node)->setCode((yyvsp[-2].node)->getCode()+(yyvsp[-1].symbol)->getName()+(yyvsp[0].node)->getCode());
						printCode((yyval.node)->getCode());
					}
#line 2501 "y.tab.c"
    break;

  case 67: /* rel_expression: simple_expression  */
#line 641 "1905072_parser.y"
                                {
					printRule("rel_expression","simple_expression");
					(yyval.node) = new Node();
					(yyval.node)->setCode((yyvsp[0].node)->getCode());
					printCode((yyval.node)->getCode());
				}
#line 2512 "y.tab.c"
    break;

  case 68: /* rel_expression: simple_expression RELOP simple_expression  */
#line 648 "1905072_parser.y"
                                {
					printRule("rel_expression","simple_expression RELOP simple_expression");
					(yyval.node) = new Node();
					(yyval.node)->setCode((yyvsp[-2].node)->getCode()+(yyvsp[-1].symbol)->getName()+(yyvsp[0].node)->getCode());
					printCode((yyval.node)->getCode());
				}
#line 2523 "y.tab.c"
    break;

  case 69: /* simple_expression: term  */
#line 657 "1905072_parser.y"
                                        {
						printRule("simple_expression","term");
						(yyval.node) = new Node();
						(yyval.node)->setCode((yyvsp[0].node)->getCode());
						printCode((yyval.node)->getCode());
					}
#line 2534 "y.tab.c"
    break;

  case 70: /* simple_expression: simple_expression ADDOP term  */
#line 664 "1905072_parser.y"
                                        {
						printRule("simple_expression","simple_expression ADDOP term");
						(yyval.node) = new Node();
						(yyval.node)->setCode((yyvsp[-2].node)->getCode()+(yyvsp[-1].symbol)->getName()+(yyvsp[0].node)->getCode());
						printCode((yyval.node)->getCode());
					}
#line 2545 "y.tab.c"
    break;

  case 71: /* term: unary_expression  */
#line 673 "1905072_parser.y"
                {
			printRule("term","unary_expression");
			(yyval.node) = new Node();
			(yyval.node)->setCode((yyvsp[0].node)->getCode());
			printCode((yyval.node)->getCode());
		}
#line 2556 "y.tab.c"
    break;

  case 72: /* term: term MULOP unary_expression  */
#line 680 "1905072_parser.y"
                {
			printRule("term","term MULOP unary_expression");
			(yyval.node) = new Node();
			(yyval.node)->setCode((yyvsp[-2].node)->getCode()+(yyvsp[-1].symbol)->getName()+(yyvsp[0].node)->getCode());
			printCode((yyval.node)->getCode());
		}
#line 2567 "y.tab.c"
    break;

  case 73: /* unary_expression: ADDOP unary_expression  */
#line 689 "1905072_parser.y"
                                        { 
						printRule("unary_expression","ADDOP unary_expression");
						(yyval.node) = new Node();
						(yyval.node)->setCode((yyvsp[-1].symbol)->getName()+(yyvsp[0].node)->getCode());
						printCode((yyval.node)->getCode());
					}
#line 2578 "y.tab.c"
    break;

  case 74: /* unary_expression: NOT unary_expression  */
#line 696 "1905072_parser.y"
                                        {
						printRule("unary_expression","NOT unary_expression");
						(yyval.node) = new Node();
						(yyval.node)->setCode("!"+(yyvsp[0].node)->getCode());
						printCode((yyval.node)->getCode());
					}
#line 2589 "y.tab.c"
    break;

  case 75: /* unary_expression: factor  */
#line 703 "1905072_parser.y"
                                        {
						printRule("unary_expression","factor");
						(yyval.node) = new Node();
						(yyval.node)->setCode((yyvsp[0].node)->getCode());
						printCode((yyval.node)->getCode());
					}
#line 2600 "y.tab.c"
    break;

  case 76: /* factor: variable  */
#line 712 "1905072_parser.y"
                {
			printRule("factor","variable");
			(yyval.node) = new Node();
			(yyval.node)->setCode((yyvsp[0].node)->getCode());
			printCode((yyval.node)->getCode());
		}
#line 2611 "y.tab.c"
    break;

  case 77: /* factor: ID LPAREN argument_list RPAREN  */
#line 719 "1905072_parser.y"
                {
			printRule("factor","ID LPAREN argument_list RPAREN");
			(yyval.node) = new Node();
			(yyval.node)->setCode((yyvsp[-3].symbol)->getName()+"("+(yyvsp[-1].node)->getCode()+")");
			printCode((yyval.node)->getCode());
		}
#line 2622 "y.tab.c"
    break;

  case 78: /* factor: LPAREN expression RPAREN  */
#line 726 "1905072_parser.y"
                {
			printRule("factor","LPAREN expression RPAREN");
			(yyval.node) = new Node();
			(yyval.node)->setCode("("+(yyvsp[-1].node)->getCode()+")");
			printCode((yyval.node)->getCode());
		}
#line 2633 "y.tab.c"
    break;

  case 79: /* factor: CONST_INT  */
#line 733 "1905072_parser.y"
                {
			printRule("factor","CONST_INT");
			(yyval.node) = new Node();
			(yyval.node)->setCode((yyvsp[0].symbol)->getName());
			printCode((yyval.node)->getCode());
		}
#line 2644 "y.tab.c"
    break;

  case 80: /* factor: CONST_FLOAT  */
#line 740 "1905072_parser.y"
                {
			printRule("factor","CONST_FLOAT");
			(yyval.node) = new Node();
			(yyval.node)->setCode((yyvsp[0].symbol)->getName());
			printCode((yyval.node)->getCode());
		}
#line 2655 "y.tab.c"
    break;

  case 81: /* factor: variable INCOP  */
#line 747 "1905072_parser.y"
                {
			printRule("factor","variable INCOP");
			(yyval.node) = new Node();
            (yyval.node)->setCode((yyvsp[-1].node)->getCode()+"++");
            printCode((yyval.node)->getCode());
		}
#line 2666 "y.tab.c"
    break;

  case 82: /* factor: variable DECOP  */
#line 754 "1905072_parser.y"
                {
			printRule("factor","variable DECOP");
			(yyval.node) = new Node();
            (yyval.node)->setCode((yyvsp[-1].node)->getCode()+"--");
            printCode((yyval.node)->getCode());
		}
#line 2677 "y.tab.c"
    break;

  case 83: /* argument_list: arguments  */
#line 763 "1905072_parser.y"
                                {
					printRule("argument_list","arguments");
					(yyval.node) = new Node();
                    (yyval.node)->setCode((yyvsp[0].node)->getCode());
                    printCode((yyval.node)->getCode());
				}
#line 2688 "y.tab.c"
    break;

  case 84: /* argument_list: %empty  */
#line 770 "1905072_parser.y"
                                { 
					printRule("argument_list","");	
					(yyval.node) = new Node();		
				}
#line 2697 "y.tab.c"
    break;

  case 85: /* arguments: arguments COMMA logic_expression  */
#line 777 "1905072_parser.y"
                        {
				printRule("arguments","arguments COMMA logic_expression");
				(yyval.node) = new Node();
                (yyval.node)->setCode((yyvsp[-2].node)->getCode()+","+(yyvsp[0].node)->getCode()); 
                printCode((yyval.node)->getCode());
			}
#line 2708 "y.tab.c"
    break;

  case 86: /* arguments: logic_expression  */
#line 784 "1905072_parser.y"
                        {
				printRule("arguments","logic_expression");
				(yyval.node) = new Node();
                (yyval.node)->setCode((yyvsp[0].node)->getCode()); 
                printCode((yyval.node)->getCode());
			}
#line 2719 "y.tab.c"
    break;


#line 2723 "y.tab.c"

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

#line 793 "1905072_parser.y"

int main(int argc,char *argv[]){
	if (argc != 2)
    {
        printf("Please provide input file name and try again\n");
        return 0;
    }

    FILE *fin = fopen(argv[1], "r");
    if (fin == NULL)
    {
        printf("Cannot open specified file\n");
        return 0;
    }

    errout.open("1905072_error.txt");
    logout.open("1905072_log.txt");
	tokenout.open("1905072_token.txt");

	table = new SymbolTable(7,sdbmHash);
    yyin = fin;
    line_count = yylineno = 1;
	error_count = 0;
    yyparse();
    fclose(yyin);

    table->printAllScope();

    logout << "Total lines: " << yylineno << endl;
    logout << "Total errors: " << error_count;

    errout.close();
    logout.close();
	tokenout.close();

    return EXIT_SUCCESS;
}


