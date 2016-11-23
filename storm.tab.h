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
     C_BOOL = 262,
     ID = 263,
     FUNCTION = 264,
     T_INT = 265,
     T_FLOAT = 266,
     T_STRING = 267,
     T_CHAR = 268,
     T_BOOL = 269,
     T_VOID = 270,
     FOR = 271,
     WHILE = 272,
     DO = 273,
     IF = 274,
     ELSE = 275,
     RETURN = 276,
     CLASS = 277,
     EXTENDS = 278,
     UN_OP_P0 = 279,
     BIN_OP_P1 = 280,
     BIN_OP_P2 = 281,
     BIN_OP_P3 = 282,
     BIN_OP_P4 = 283,
     BIN_OP_P5 = 284,
     BIN_OP_P6 = 285
   };
#endif
/* Tokens.  */
#define C_INT 258
#define C_FLOAT 259
#define C_STRING 260
#define C_CHAR 261
#define C_BOOL 262
#define ID 263
#define FUNCTION 264
#define T_INT 265
#define T_FLOAT 266
#define T_STRING 267
#define T_CHAR 268
#define T_BOOL 269
#define T_VOID 270
#define FOR 271
#define WHILE 272
#define DO 273
#define IF 274
#define ELSE 275
#define RETURN 276
#define CLASS 277
#define EXTENDS 278
#define UN_OP_P0 279
#define BIN_OP_P1 280
#define BIN_OP_P2 281
#define BIN_OP_P3 282
#define BIN_OP_P4 283
#define BIN_OP_P5 284
#define BIN_OP_P6 285




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 28 "storm.y"
{
  int ival;
  float fval;
  bool bval;
  char *sval;
  char cval;
}
/* Line 1529 of yacc.c.  */
#line 117 "storm.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

