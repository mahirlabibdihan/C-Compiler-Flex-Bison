
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IF = 258,
     ELSE = 259,
     LOWER_THAN_ELSE = 260,
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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 97 "1905072_parser.y"

	Segment* segment;
	Expression* expression;



/* Line 1676 of yacc.c  */
#line 141 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


