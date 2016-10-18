/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
     C_INT = 258,
     C_FLOAT = 259,
     C_STRING = 260,
     C_CHAR = 261,
     ID = 262,
     FUNCTION = 263,
     T_INT = 264,
     T_FLOAT = 265,
     T_STRING = 266,
     T_CHAR = 267,
     T_VOID = 268,
     FOR = 269,
     WHILE = 270,
     DO = 271,
     IF = 272,
     ELSE = 273,
     RETURN = 274,
     CLASS = 275,
     UN_OP = 276,
     BIN_OP = 277
   };
#endif
/* Tokens.  */
#define C_INT 258
#define C_FLOAT 259
#define C_STRING 260
#define C_CHAR 261
#define ID 262
#define FUNCTION 263
#define T_INT 264
#define T_FLOAT 265
#define T_STRING 266
#define T_CHAR 267
#define T_VOID 268
#define FOR 269
#define WHILE 270
#define DO 271
#define IF 272
#define ELSE 273
#define RETURN 274
#define CLASS 275
#define UN_OP 276
#define BIN_OP 277




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 121 "storm.y"
{
  int ival;
  float fval;
  char *sval;
  char cval;
}
/* Line 1529 of yacc.c.  */
#line 100 "storm.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

