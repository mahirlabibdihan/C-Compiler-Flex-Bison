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

#line 154 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
