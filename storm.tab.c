/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 1 "storm.y"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <utility>
#include <stack>
#include <vector>
#include <set>
#include <sstream>
#include "include/quadruple_store.h"
#include "include/function.h"
#include "include/class.h"
#include "include/virtual_machine.h"
using namespace std;

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
extern int linenum;

QuadrupleStore quadStore;

void yyerror(const char *s);


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

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
/* Line 193 of yacc.c.  */
#line 191 "storm.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 204 "storm.tab.c"

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
# if defined YYENABLE_NLS && YYENABLE_NLS
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
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
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
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  21
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   182

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  69
/* YYNRULES -- Number of rules.  */
#define YYNRULES  115
/* YYNRULES -- Number of states.  */
#define YYNSTATES  190

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      35,    36,     2,     2,    32,     2,    40,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    31,
       2,    39,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    33,     2,    34,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    37,     2,    38,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    13,    17,    19,    23,
      25,    27,    32,    33,    34,    35,    46,    48,    49,    55,
      57,    58,    60,    62,    66,    69,    73,    74,    77,    79,
      82,    84,    86,    88,    90,    92,    93,    94,    95,   108,
     109,   110,   118,   119,   128,   129,   130,   139,   140,   143,
     144,   148,   149,   154,   156,   158,   160,   162,   164,   166,
     168,   169,   178,   179,   182,   183,   186,   187,   190,   191,
     196,   198,   199,   204,   206,   207,   212,   214,   215,   220,
     222,   223,   228,   230,   231,   236,   238,   239,   243,   245,
     246,   251,   253,   255,   257,   259,   261,   263,   267,   268,
     275,   277,   278,   284,   285,   290,   291,   293,   295,   299,
     301,   303,   305,   307,   309,   310
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      42,     0,    -1,    -1,    43,    42,    -1,    47,    42,    -1,
      77,    42,    -1,    75,    44,    31,    -1,    46,    -1,    44,
      32,    46,    -1,     8,    -1,    45,    -1,    45,    33,     3,
      34,    -1,    -1,    -1,    -1,     9,    51,    48,    45,    49,
      35,    53,    36,    50,    56,    -1,    15,    -1,    -1,    33,
       3,    34,    52,    75,    -1,    75,    -1,    -1,    54,    -1,
      55,    -1,    53,    32,    55,    -1,    75,    46,    -1,    37,
      57,    38,    -1,    -1,    57,    58,    -1,    43,    -1,    82,
      31,    -1,    59,    -1,    63,    -1,    66,    -1,    68,    -1,
      72,    -1,    -1,    -1,    -1,    16,    35,    98,    31,    60,
      82,    61,    31,    98,    62,    36,    56,    -1,    -1,    -1,
      17,    64,    35,    82,    65,    36,    56,    -1,    -1,    18,
      67,    56,    17,    35,    82,    36,    31,    -1,    -1,    -1,
      19,    35,    82,    69,    36,    56,    70,    71,    -1,    -1,
      20,    56,    -1,    -1,    21,    73,    31,    -1,    -1,    21,
      82,    74,    31,    -1,    76,    -1,    10,    -1,    11,    -1,
      12,    -1,    13,    -1,    14,    -1,    45,    -1,    -1,    22,
      45,    78,    79,    37,    80,    81,    38,    -1,    -1,    23,
      45,    -1,    -1,    43,    80,    -1,    -1,    47,    81,    -1,
      -1,    82,    30,    83,    84,    -1,    84,    -1,    -1,    84,
      29,    85,    86,    -1,    86,    -1,    -1,    86,    28,    87,
      88,    -1,    88,    -1,    -1,    88,    27,    89,    90,    -1,
      90,    -1,    -1,    90,    26,    91,    92,    -1,    92,    -1,
      -1,    92,    25,    93,    94,    -1,    94,    -1,    -1,    24,
      95,    96,    -1,    96,    -1,    -1,    35,    97,    82,    36,
      -1,   101,    -1,   103,    -1,   107,    -1,   108,    -1,    45,
      -1,    98,    -1,    99,    39,    82,    -1,    -1,    40,    45,
     100,    33,    82,    34,    -1,    45,    -1,    -1,    45,   102,
      35,   105,    36,    -1,    -1,    82,   104,    40,   101,    -1,
      -1,   106,    -1,    82,    -1,   106,    32,    82,    -1,     3,
      -1,     4,    -1,     5,    -1,     6,    -1,     7,    -1,    -1,
      45,   109,    33,    82,    34,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    68,    68,    69,    70,    71,    73,    75,    76,    78,
      80,    81,    83,    83,    83,    83,    85,    86,    86,    87,
      88,    89,    91,    92,    94,    96,    97,    98,   100,   101,
     102,   103,   104,   105,   106,   108,   108,   109,   108,   111,
     111,   111,   113,   113,   115,   115,   115,   116,   117,   119,
     119,   120,   120,   122,   124,   124,   124,   124,   124,   125,
     127,   127,   128,   129,   130,   131,   132,   133,   135,   135,
     136,   138,   138,   139,   141,   141,   142,   144,   144,   145,
     147,   147,   148,   150,   150,   151,   153,   153,   154,   156,
     156,   157,   158,   159,   160,   161,   162,   164,   166,   166,
     167,   169,   169,   171,   171,   172,   173,   175,   176,   178,
     179,   180,   181,   182,   184,   184
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "C_INT", "C_FLOAT", "C_STRING", "C_CHAR",
  "C_BOOL", "ID", "FUNCTION", "T_INT", "T_FLOAT", "T_STRING", "T_CHAR",
  "T_BOOL", "T_VOID", "FOR", "WHILE", "DO", "IF", "ELSE", "RETURN",
  "CLASS", "EXTENDS", "UN_OP_P0", "BIN_OP_P1", "BIN_OP_P2", "BIN_OP_P3",
  "BIN_OP_P4", "BIN_OP_P5", "BIN_OP_P6", "';'", "','", "'['", "']'", "'('",
  "')'", "'{'", "'}'", "'='", "'.'", "$accept", "program", "var_declr",
  "var_declr_a", "id", "var_arr", "function", "@1", "@2", "@3",
  "return_type", "@4", "parameters", "params", "parameter", "block",
  "statements", "statement", "for_stm", "@5", "@6", "@7", "while_stm",
  "@8", "@9", "do_while_stm", "@10", "if_stm", "@11", "@12", "else_stm",
  "return_stm", "@13", "@14", "type", "type_aux", "class_declr", "@15",
  "parent_class", "attribute_declr", "method_declr", "expr", "@16",
  "expr6", "@17", "expr5", "@18", "expr4", "@19", "expr3", "@20", "expr2",
  "@21", "expr1", "@22", "expr0", "@23", "assign", "assignable", "@24",
  "fn_call", "@25", "obj_fn_call", "@26", "arguments", "args", "literal",
  "arr_access", "@27", 0
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
     285,    59,    44,    91,    93,    40,    41,   123,   125,    61,
      46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    41,    42,    42,    42,    42,    43,    44,    44,    45,
      46,    46,    48,    49,    50,    47,    51,    52,    51,    51,
      53,    53,    54,    54,    55,    56,    57,    57,    58,    58,
      58,    58,    58,    58,    58,    60,    61,    62,    59,    64,
      65,    63,    67,    66,    69,    70,    68,    71,    71,    73,
      72,    74,    72,    75,    76,    76,    76,    76,    76,    76,
      78,    77,    79,    79,    80,    80,    81,    81,    83,    82,
      82,    85,    84,    84,    87,    86,    86,    89,    88,    88,
      91,    90,    90,    93,    92,    92,    95,    94,    94,    97,
      96,    96,    96,    96,    96,    96,    96,    98,   100,    99,
      99,   102,   101,   104,   103,   105,   105,   106,   106,   107,
     107,   107,   107,   107,   109,   108
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     3,     1,     3,     1,
       1,     4,     0,     0,     0,    10,     1,     0,     5,     1,
       0,     1,     1,     3,     2,     3,     0,     2,     1,     2,
       1,     1,     1,     1,     1,     0,     0,     0,    12,     0,
       0,     7,     0,     8,     0,     0,     8,     0,     2,     0,
       3,     0,     4,     1,     1,     1,     1,     1,     1,     1,
       0,     8,     0,     2,     0,     2,     0,     2,     0,     4,
       1,     0,     4,     1,     0,     4,     1,     0,     4,     1,
       0,     4,     1,     0,     4,     1,     0,     3,     1,     0,
       4,     1,     1,     1,     1,     1,     1,     3,     0,     6,
       1,     0,     5,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     0,     5
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     9,     0,    54,    55,    56,    57,    58,     0,     0,
       2,    59,     2,     0,    53,     2,    16,     0,    12,    19,
      60,     1,     3,     4,     0,    10,     7,     5,     0,     0,
      62,     6,     0,     0,    17,    13,     0,     0,     8,     0,
       0,     0,    63,    64,    11,    18,    20,    64,    66,     0,
      21,    22,     0,    65,    66,     0,     0,    14,    24,    67,
      61,    23,     0,    26,    15,     0,   109,   110,   111,   112,
     113,     0,    39,    42,     0,    49,    86,    89,    25,     0,
      28,    95,    27,    30,    31,    32,    33,    34,   103,    70,
      73,    76,    79,    82,    85,    88,    96,     0,    91,    92,
      93,    94,     0,     0,     0,     0,    95,     0,    51,     0,
       0,    98,     0,     0,    68,    29,     0,    71,    74,    77,
      80,    83,     0,   100,     0,     0,     0,    44,    50,     0,
     103,    87,   103,     0,   105,     0,     0,     0,     0,     0,
       0,     0,     0,    97,    35,    40,     0,     0,    52,    90,
       0,   107,     0,   106,   103,    69,   101,   104,    72,    75,
      78,    81,    84,     0,     0,     0,     0,   103,   102,     0,
     115,    36,     0,   103,    45,    99,   108,     0,    41,     0,
      47,     0,    43,     0,    46,    37,    48,     0,     0,    38
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     9,    10,    24,   106,    26,    12,    29,    41,    62,
      18,    40,    49,    50,    51,    64,    65,    82,    83,   163,
     177,   187,    84,   103,   164,    85,   104,    86,   147,   180,
     184,    87,   107,   129,    13,    14,    15,    30,    37,    48,
      55,   130,   136,    89,   138,    90,   139,    91,   140,    92,
     141,    93,   142,    94,   109,    95,   110,    96,    97,   133,
      98,   112,    99,   116,   152,   153,   100,   101,   113
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -104
static const yytype_int16 yypact[] =
{
      95,  -104,    78,  -104,  -104,  -104,  -104,  -104,    -1,     9,
      95,  -104,    95,    -1,  -104,    95,  -104,    30,  -104,  -104,
    -104,  -104,  -104,  -104,    29,    48,  -104,  -104,    44,    -1,
      64,  -104,    -1,    91,  -104,  -104,    -1,    58,  -104,    62,
     132,    63,  -104,   132,  -104,  -104,   132,   132,    88,    34,
    -104,  -104,    -1,  -104,    88,    72,   132,  -104,  -104,  -104,
    -104,  -104,    76,  -104,  -104,   117,  -104,  -104,  -104,  -104,
    -104,    65,  -104,  -104,    66,    15,  -104,  -104,  -104,    -1,
    -104,    18,  -104,  -104,  -104,  -104,  -104,  -104,    45,    86,
      98,    89,    93,   107,  -104,  -104,  -104,   100,  -104,  -104,
    -104,  -104,    -3,   112,    76,    15,    -5,   118,   -24,    15,
      15,  -104,   113,   120,  -104,  -104,   110,  -104,  -104,  -104,
    -104,  -104,    15,  -104,   123,    15,   134,   -24,  -104,   125,
     128,  -104,   -19,   126,    15,    15,    15,    -1,    15,    15,
      15,    15,    15,   128,  -104,   -24,   127,   124,  -104,  -104,
      15,   -24,   129,   131,    38,    86,  -104,  -104,    98,    89,
      93,   107,  -104,    15,   130,    15,    76,    43,  -104,    15,
    -104,   -24,    76,     5,  -104,  -104,   -24,   133,  -104,   136,
     141,    -3,  -104,    76,  -104,  -104,  -104,   135,    76,  -104
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -104,    52,   -16,  -104,     0,    -7,   -10,  -104,  -104,  -104,
    -104,  -104,  -104,  -104,   114,  -103,  -104,  -104,  -104,  -104,
    -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,
    -104,  -104,  -104,  -104,     2,  -104,  -104,  -104,  -104,   121,
     115,   -51,  -104,    36,  -104,    35,  -104,    37,  -104,    39,
    -104,    33,  -104,    40,  -104,    68,  -104,   -99,  -104,  -104,
      41,  -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -115
static const yytype_int16 yytable[] =
{
      11,   126,    11,   124,    19,     1,   114,     1,    20,    21,
      11,   114,    11,    25,    88,    11,  -103,   149,    66,    67,
      68,    69,    70,     1,   108,    38,   -59,    47,  -114,    35,
    -101,    47,    25,    28,  -100,   114,    42,    79,    54,    76,
      11,   179,    45,    11,    54,    58,    11,    11,    52,    80,
      77,  -114,    25,  -101,   127,    79,    11,  -100,    52,   132,
      31,    32,    22,   174,    23,    81,    56,    27,   114,   178,
      57,   143,   170,   114,   145,   114,   115,   175,    34,   111,
     186,    33,   185,   151,   154,   189,     1,    36,     3,     4,
       5,     6,     7,    16,    39,    43,    44,     2,    46,   167,
     102,   105,   123,     1,     2,     3,     4,     5,     6,     7,
      60,    17,   171,    63,   173,   117,   119,     8,   176,   120,
      66,    67,    68,    69,    70,     1,   118,     3,     4,     5,
       6,     7,   121,    71,    72,    73,    74,   156,    75,   122,
       1,    76,     3,     4,     5,     6,     7,   125,   134,   128,
     137,   146,    77,   135,   144,    78,   148,    79,   114,   150,
     166,   183,   165,   169,   181,   168,   172,   182,    53,    59,
      61,   188,   155,   158,   161,     0,   159,   131,   157,   160,
       0,   123,   162
};

static const yytype_int16 yycheck[] =
{
       0,   104,     2,   102,     2,     8,    30,     8,     8,     0,
      10,    30,    12,    13,    65,    15,    40,    36,     3,     4,
       5,     6,     7,     8,    75,    32,     8,    43,    33,    29,
      35,    47,    32,     3,    39,    30,    36,    40,    48,    24,
      40,    36,    40,    43,    54,    52,    46,    47,    46,    65,
      35,    33,    52,    35,   105,    40,    56,    39,    56,   110,
      31,    32,    10,   166,    12,    65,    32,    15,    30,   172,
      36,   122,    34,    30,   125,    30,    31,    34,    34,    79,
     183,    33,   181,   134,   135,   188,     8,    23,    10,    11,
      12,    13,    14,    15,     3,    37,    34,     9,    35,   150,
      35,    35,   102,     8,     9,    10,    11,    12,    13,    14,
      38,    33,   163,    37,   165,    29,    27,    22,   169,    26,
       3,     4,     5,     6,     7,     8,    28,    10,    11,    12,
      13,    14,    25,    16,    17,    18,    19,   137,    21,    39,
       8,    24,    10,    11,    12,    13,    14,    35,    35,    31,
      40,    17,    35,    33,    31,    38,    31,    40,    30,    33,
      36,    20,    35,    32,    31,    36,    36,    31,    47,    54,
      56,    36,   136,   138,   141,    -1,   139,   109,   137,   140,
      -1,   181,   142
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     8,     9,    10,    11,    12,    13,    14,    22,    42,
      43,    45,    47,    75,    76,    77,    15,    33,    51,    75,
      45,     0,    42,    42,    44,    45,    46,    42,     3,    48,
      78,    31,    32,    33,    34,    45,    23,    79,    46,     3,
      52,    49,    45,    37,    34,    75,    35,    43,    80,    53,
      54,    55,    75,    80,    47,    81,    32,    36,    46,    81,
      38,    55,    50,    37,    56,    57,     3,     4,     5,     6,
       7,    16,    17,    18,    19,    21,    24,    35,    38,    40,
      43,    45,    58,    59,    63,    66,    68,    72,    82,    84,
      86,    88,    90,    92,    94,    96,    98,    99,   101,   103,
     107,   108,    35,    64,    67,    35,    45,    73,    82,    95,
      97,    45,   102,   109,    30,    31,   104,    29,    28,    27,
      26,    25,    39,    45,    98,    35,    56,    82,    31,    74,
      82,    96,    82,   100,    35,    33,    83,    40,    85,    87,
      89,    91,    93,    82,    31,    82,    17,    69,    31,    36,
      33,    82,   105,   106,    82,    84,    45,   101,    86,    88,
      90,    92,    94,    60,    65,    35,    36,    82,    36,    32,
      34,    82,    36,    82,    56,    34,    82,    61,    56,    36,
      70,    31,    31,    20,    71,    98,    56,    62,    36,    56
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
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
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
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
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
#line 68 "storm.y"
    { quadStore.end(); ;}
    break;

  case 7:
#line 75 "storm.y"
    { quadStore.declareVar(); ;}
    break;

  case 8:
#line 76 "storm.y"
    { quadStore.declareVar(); ;}
    break;

  case 9:
#line 78 "storm.y"
    { quadStore.lastIdName = string(yylval.sval); ;}
    break;

  case 10:
#line 80 "storm.y"
    { quadStore.typeIsArray = false; ;}
    break;

  case 11:
#line 81 "storm.y"
    { quadStore.typeIsArray = true; quadStore.lastArraySize = atoi(yylval.sval); quadStore.validateArraySize(); ;}
    break;

  case 12:
#line 83 "storm.y"
    { quadStore.lastReturnType = string(yylval.sval); ;}
    break;

  case 13:
#line 83 "storm.y"
    { quadStore.lastFuncName = string(yylval.sval); ;}
    break;

  case 14:
#line 83 "storm.y"
    { quadStore.declareFunc(); ;}
    break;

  case 15:
#line 83 "storm.y"
    { quadStore.functionExit(); ;}
    break;

  case 16:
#line 85 "storm.y"
    { quadStore.returnTypeIsArray = false; ;}
    break;

  case 17:
#line 86 "storm.y"
    { quadStore.returnTypeIsArray = true; quadStore.lastReturnArraySize = atoi(yylval.sval); quadStore.validateReturnArraySize(); ;}
    break;

  case 19:
#line 87 "storm.y"
    { quadStore.returnTypeIsArray = false; ;}
    break;

  case 24:
#line 94 "storm.y"
    { quadStore.declareParam() ;}
    break;

  case 35:
#line 108 "storm.y"
    { quadStore.forConditionStart(); ;}
    break;

  case 36:
#line 108 "storm.y"
    { quadStore.forConditionEnd(); ;}
    break;

  case 37:
#line 109 "storm.y"
    { quadStore.forStart(); ;}
    break;

  case 38:
#line 109 "storm.y"
    { quadStore.forEnd(); ;}
    break;

  case 39:
#line 111 "storm.y"
    { quadStore.whileConditionStart(); ;}
    break;

  case 40:
#line 111 "storm.y"
    { quadStore.whileBlockStart(); ;}
    break;

  case 41:
#line 111 "storm.y"
    { quadStore.whileEnd(); ;}
    break;

  case 42:
#line 113 "storm.y"
    { quadStore.doWhileStart(); ;}
    break;

  case 43:
#line 113 "storm.y"
    { quadStore.doWhileEnd(); ;}
    break;

  case 44:
#line 115 "storm.y"
    { quadStore.ifStart(); ;}
    break;

  case 45:
#line 115 "storm.y"
    { quadStore.ifBlockEnd(); ;}
    break;

  case 46:
#line 115 "storm.y"
    { quadStore.ifEnd(); ;}
    break;

  case 49:
#line 119 "storm.y"
    { quadStore.returnVoid(); ;}
    break;

  case 51:
#line 120 "storm.y"
    { quadStore.returnExpr(); ;}
    break;

  case 53:
#line 122 "storm.y"
    { quadStore.lastType = string(yylval.sval); ;}
    break;

  case 59:
#line 125 "storm.y"
    { quadStore.lastObjectType = quadStore.lastIdName; quadStore.isObjectType = true; quadStore.validateType(); ;}
    break;

  case 60:
#line 127 "storm.y"
    { quadStore.declareClass(); ;}
    break;

  case 61:
#line 127 "storm.y"
    { quadStore.endClass(); ;}
    break;

  case 63:
#line 129 "storm.y"
    { quadStore.setParentClass(); ;}
    break;

  case 68:
#line 135 "storm.y"
    { quadStore.lastOperator = string(yylval.sval); quadStore._operator(); ;}
    break;

  case 69:
#line 135 "storm.y"
    { quadStore.operation(6); ;}
    break;

  case 71:
#line 138 "storm.y"
    { quadStore.lastOperator = string(yylval.sval); quadStore._operator(); ;}
    break;

  case 72:
#line 138 "storm.y"
    { quadStore.operation(5); ;}
    break;

  case 74:
#line 141 "storm.y"
    { quadStore.lastOperator = string(yylval.sval); quadStore._operator(); ;}
    break;

  case 75:
#line 141 "storm.y"
    { quadStore.operation(4); ;}
    break;

  case 77:
#line 144 "storm.y"
    { quadStore.lastOperator = string(yylval.sval); quadStore._operator(); ;}
    break;

  case 78:
#line 144 "storm.y"
    { quadStore.operation(3); ;}
    break;

  case 80:
#line 147 "storm.y"
    { quadStore.lastOperator = string(yylval.sval); quadStore._operator(); ;}
    break;

  case 81:
#line 147 "storm.y"
    { quadStore.operation(2); ;}
    break;

  case 83:
#line 150 "storm.y"
    { quadStore.lastOperator = string(yylval.sval); quadStore._operator(); ;}
    break;

  case 84:
#line 150 "storm.y"
    { quadStore.operation(1); ;}
    break;

  case 86:
#line 153 "storm.y"
    { quadStore.lastOperator = string(yylval.sval); quadStore._operator(); ;}
    break;

  case 87:
#line 153 "storm.y"
    { quadStore.operation(0); ;}
    break;

  case 89:
#line 156 "storm.y"
    { quadStore.openParenthesis(); ;}
    break;

  case 90:
#line 156 "storm.y"
    { quadStore.closeParenthesis(); ;}
    break;

  case 95:
#line 161 "storm.y"
    { quadStore.varExpr(); ;}
    break;

  case 97:
#line 164 "storm.y"
    { quadStore.assign(); ;}
    break;

  case 98:
#line 166 "storm.y"
    { quadStore.initArrAccess(); ;}
    break;

  case 99:
#line 166 "storm.y"
    { quadStore.arrAccess(); ;}
    break;

  case 100:
#line 167 "storm.y"
    { quadStore.initAssign(); ;}
    break;

  case 101:
#line 169 "storm.y"
    { quadStore.fnCallInit(); ;}
    break;

  case 102:
#line 169 "storm.y"
    { quadStore.fnCall(); ;}
    break;

  case 103:
#line 171 "storm.y"
    { quadStore.objFnCallInit() ;}
    break;

  case 107:
#line 175 "storm.y"
    { quadStore.argument(); ;}
    break;

  case 108:
#line 176 "storm.y"
    { quadStore.argument(); ;}
    break;

  case 109:
#line 178 "storm.y"
    { quadStore.literal("int", string(yylval.sval)) ;}
    break;

  case 110:
#line 179 "storm.y"
    { quadStore.literal("float", string(yylval.sval)) ;}
    break;

  case 111:
#line 180 "storm.y"
    { quadStore.literal("string", string(yylval.sval)) ;}
    break;

  case 112:
#line 181 "storm.y"
    { quadStore.literal("char", string(yylval.sval)) ;}
    break;

  case 113:
#line 182 "storm.y"
    { quadStore.literal("bool", string(yylval.sval)) ;}
    break;

  case 114:
#line 184 "storm.y"
    { quadStore.initArrAccess(); ;}
    break;

  case 115:
#line 184 "storm.y"
    { quadStore.arrAccess(); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 1911 "storm.tab.c"
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
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  if (yyn == YYFINAL)
    YYACCEPT;

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
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


#line 186 "storm.y"


int main(int argc, char** argv) {
  quadStore.begin();
    // Open a file to read the input from it
  if (argc < 2) {
    cout << "error: no input file" << endl;
    exit(1);
  }

  FILE *myfile = fopen(argv[1], "r");
  if (!myfile) {
    cout << "I can't open " << argv[1] << "!" << endl;
    return -1;
  }
  // set flex to read from it instead of defaulting to STDIN:
  yyin = myfile;
  
  // parse through the input until there is no more:
  do {
    yyparse();
  } while (!feof(yyin));

  VirtualMachine vm(quadStore.quads);
  vm.Start();
}

void yyerror(const char *s) {
  // Print an error message along with the line number where it failed
  cout << "EEK, parse error on line " << linenum << "!  Message: " << s << endl;
  exit(-1);
}

