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
     UN_OP_P0 = 278,
     BIN_OP_P1 = 279,
     BIN_OP_P2 = 280,
     BIN_OP_P3 = 281,
     BIN_OP_P4 = 282,
     BIN_OP_P5 = 283,
     BIN_OP_P6 = 284
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
#define UN_OP_P0 278
#define BIN_OP_P1 279
#define BIN_OP_P2 280
#define BIN_OP_P3 281
#define BIN_OP_P4 282
#define BIN_OP_P5 283
#define BIN_OP_P6 284




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
#line 189 "storm.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 202 "storm.tab.c"

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
#define YYFINAL  20
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   190

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  66
/* YYNRULES -- Number of rules.  */
#define YYNRULES  110
/* YYNRULES -- Number of states.  */
#define YYNSTATES  181

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   284

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      34,    35,     2,     2,    31,     2,    39,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    30,
       2,    38,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    32,     2,    33,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    36,     2,    37,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    13,    17,    19,    23,
      25,    27,    32,    33,    34,    35,    46,    47,    49,    51,
      55,    58,    62,    63,    66,    68,    71,    73,    75,    77,
      79,    81,    82,    83,    84,    97,    98,    99,   107,   108,
     117,   118,   119,   128,   129,   132,   133,   137,   138,   143,
     145,   147,   149,   151,   153,   155,   157,   159,   161,   162,
     169,   170,   173,   176,   177,   182,   184,   185,   190,   192,
     193,   198,   200,   201,   206,   208,   209,   214,   216,   217,
     222,   224,   225,   229,   231,   232,   237,   239,   241,   243,
     245,   247,   249,   253,   254,   261,   263,   264,   270,   271,
     276,   277,   279,   281,   285,   287,   289,   291,   293,   295,
     296
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      41,     0,    -1,    -1,    42,    41,    -1,    46,    41,    -1,
      75,    41,    -1,    73,    43,    30,    -1,    45,    -1,    43,
      31,    45,    -1,     8,    -1,    44,    -1,    44,    32,     3,
      33,    -1,    -1,    -1,    -1,     9,    72,    47,    44,    48,
      34,    50,    35,    49,    53,    -1,    -1,    51,    -1,    52,
      -1,    50,    31,    52,    -1,    73,    45,    -1,    36,    54,
      37,    -1,    -1,    54,    55,    -1,    42,    -1,    78,    30,
      -1,    56,    -1,    60,    -1,    63,    -1,    65,    -1,    69,
      -1,    -1,    -1,    -1,    16,    34,    94,    30,    57,    78,
      58,    30,    94,    59,    35,    53,    -1,    -1,    -1,    17,
      61,    34,    78,    62,    35,    53,    -1,    -1,    18,    64,
      53,    17,    34,    78,    35,    30,    -1,    -1,    -1,    19,
      34,    78,    66,    35,    53,    67,    68,    -1,    -1,    20,
      53,    -1,    -1,    21,    70,    30,    -1,    -1,    21,    78,
      71,    30,    -1,    15,    -1,    73,    -1,    74,    -1,    10,
      -1,    11,    -1,    12,    -1,    13,    -1,    14,    -1,    44,
      -1,    -1,    22,    44,    76,    36,    77,    37,    -1,    -1,
      42,    77,    -1,    46,    77,    -1,    -1,    78,    29,    79,
      80,    -1,    80,    -1,    -1,    80,    28,    81,    82,    -1,
      82,    -1,    -1,    82,    27,    83,    84,    -1,    84,    -1,
      -1,    84,    26,    85,    86,    -1,    86,    -1,    -1,    86,
      25,    87,    88,    -1,    88,    -1,    -1,    88,    24,    89,
      90,    -1,    90,    -1,    -1,    23,    91,    92,    -1,    92,
      -1,    -1,    34,    93,    78,    35,    -1,    97,    -1,    99,
      -1,   103,    -1,   104,    -1,    44,    -1,    94,    -1,    95,
      38,    78,    -1,    -1,    39,    44,    96,    32,    78,    33,
      -1,    44,    -1,    -1,    44,    98,    34,   101,    35,    -1,
      -1,    78,   100,    39,    97,    -1,    -1,   102,    -1,    78,
      -1,   102,    31,    78,    -1,     3,    -1,     4,    -1,     5,
      -1,     6,    -1,     7,    -1,    -1,    44,   105,    32,    78,
      33,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    67,    67,    68,    69,    70,    72,    74,    75,    77,
      79,    80,    82,    82,    82,    82,    83,    84,    86,    87,
      89,    91,    92,    93,    95,    96,    97,    98,    99,   100,
     101,   103,   103,   104,   103,   106,   106,   106,   108,   108,
     110,   110,   110,   111,   112,   114,   114,   115,   115,   117,
     117,   119,   121,   121,   121,   121,   121,   121,   123,   123,
     124,   125,   126,   128,   128,   129,   131,   131,   132,   134,
     134,   135,   137,   137,   138,   140,   140,   141,   143,   143,
     144,   146,   146,   147,   149,   149,   150,   151,   152,   153,
     154,   155,   157,   159,   159,   160,   162,   162,   164,   164,
     165,   166,   168,   169,   171,   172,   173,   174,   175,   177,
     177
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
  "CLASS", "UN_OP_P0", "BIN_OP_P1", "BIN_OP_P2", "BIN_OP_P3", "BIN_OP_P4",
  "BIN_OP_P5", "BIN_OP_P6", "';'", "','", "'['", "']'", "'('", "')'",
  "'{'", "'}'", "'='", "'.'", "$accept", "program", "var_declr",
  "var_declr_a", "id", "var_arr", "function", "@1", "@2", "@3",
  "parameters", "params", "parameter", "block", "statements", "statement",
  "for_stm", "@4", "@5", "@6", "while_stm", "@7", "@8", "do_while_stm",
  "@9", "if_stm", "@10", "@11", "else_stm", "return_stm", "@12", "@13",
  "return_type", "type", "type_aux", "class_declr", "@14", "class_declr_a",
  "expr", "@15", "expr6", "@16", "expr5", "@17", "expr4", "@18", "expr3",
  "@19", "expr2", "@20", "expr1", "@21", "expr0", "@22", "assign",
  "assignable", "@23", "fn_call", "@24", "obj_fn_call", "@25", "arguments",
  "args", "literal", "arr_access", "@26", 0
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
      59,    44,    91,    93,    40,    41,   123,   125,    61,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    41,    41,    41,    41,    42,    43,    43,    44,
      45,    45,    47,    48,    49,    46,    50,    50,    51,    51,
      52,    53,    54,    54,    55,    55,    55,    55,    55,    55,
      55,    57,    58,    59,    56,    61,    62,    60,    64,    63,
      66,    67,    65,    68,    68,    70,    69,    71,    69,    72,
      72,    73,    74,    74,    74,    74,    74,    74,    76,    75,
      77,    77,    77,    79,    78,    78,    81,    80,    80,    83,
      82,    82,    85,    84,    84,    87,    86,    86,    89,    88,
      88,    91,    90,    90,    93,    92,    92,    92,    92,    92,
      92,    92,    94,    96,    95,    95,    98,    97,   100,    99,
     101,   101,   102,   102,   103,   103,   103,   103,   103,   105,
     104
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     3,     1,     3,     1,
       1,     4,     0,     0,     0,    10,     0,     1,     1,     3,
       2,     3,     0,     2,     1,     2,     1,     1,     1,     1,
       1,     0,     0,     0,    12,     0,     0,     7,     0,     8,
       0,     0,     8,     0,     2,     0,     3,     0,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     6,
       0,     2,     2,     0,     4,     1,     0,     4,     1,     0,
       4,     1,     0,     4,     1,     0,     4,     1,     0,     4,
       1,     0,     3,     1,     0,     4,     1,     1,     1,     1,
       1,     1,     3,     0,     6,     1,     0,     5,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     0,
       5
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     9,     0,    52,    53,    54,    55,    56,     0,     0,
       2,    57,     2,     0,    51,     2,    49,    12,    50,    58,
       1,     3,     4,     0,    10,     7,     5,     0,     0,     6,
       0,     0,    13,    60,     8,     0,     0,    60,    60,     0,
      11,    16,    61,    62,    59,     0,    17,    18,     0,     0,
      14,    20,    19,     0,    22,    15,     0,   104,   105,   106,
     107,   108,     0,    35,    38,     0,    45,    81,    84,    21,
       0,    24,    90,    23,    26,    27,    28,    29,    30,    98,
      65,    68,    71,    74,    77,    80,    83,    91,     0,    86,
      87,    88,    89,     0,     0,     0,     0,    90,     0,    47,
       0,     0,    93,     0,     0,    63,    25,     0,    66,    69,
      72,    75,    78,     0,    95,     0,     0,     0,    40,    46,
       0,    98,    82,    98,     0,   100,     0,     0,     0,     0,
       0,     0,     0,     0,    92,    31,    36,     0,     0,    48,
      85,     0,   102,     0,   101,    98,    64,    96,    99,    67,
      70,    73,    76,    79,     0,     0,     0,     0,    98,    97,
       0,   110,    32,     0,    98,    41,    94,   103,     0,    37,
       0,    43,     0,    39,     0,    42,    33,    44,     0,     0,
      34
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     9,    10,    23,    97,    25,    12,    27,    36,    53,
      45,    46,    47,    55,    56,    73,    74,   154,   168,   178,
      75,    94,   155,    76,    95,    77,   138,   171,   175,    78,
      98,   120,    17,    13,    14,    15,    28,    39,   121,   127,
      80,   129,    81,   130,    82,   131,    83,   132,    84,   133,
      85,   100,    86,   101,    87,    88,   124,    89,   103,    90,
     107,   143,   144,    91,    92,   104
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -93
static const yytype_int16 yypact[] =
{
      86,   -93,   122,   -93,   -93,   -93,   -93,   -93,     1,    14,
      86,   -93,    86,     1,   -93,    86,   -93,   -93,   -93,   -93,
     -93,   -93,   -93,    49,    -6,   -93,   -93,     1,     7,   -93,
       1,    56,   -93,   140,   -93,    -4,    52,   140,   140,    53,
     -93,   147,   -93,   -93,   -93,    37,   -93,   -93,     1,   147,
     -93,   -93,   -93,    65,   -93,   -93,   108,   -93,   -93,   -93,
     -93,   -93,    58,   -93,   -93,    68,    16,   -93,   -93,   -93,
       1,   -93,    26,   -93,   -93,   -93,   -93,   -93,   -93,    55,
      75,    78,    81,    84,    93,   -93,   -93,   -93,    85,   -93,
     -93,   -93,   -93,    -7,   104,    65,    16,    35,   109,   -11,
      16,    16,   -93,   106,   111,   -93,   -93,   102,   -93,   -93,
     -93,   -93,   -93,    16,   -93,   114,    16,   129,   -11,   -93,
     126,   133,   -93,   -18,   131,    16,    16,    16,     1,    16,
      16,    16,    16,    16,   133,   -93,   -11,   130,   132,   -93,
     -93,    16,   -11,   134,   135,    45,    75,   -93,   -93,    78,
      81,    84,    93,   -93,    16,   136,    16,    65,    48,   -93,
      16,   -93,   -11,    65,    18,   -93,   -93,   -11,   138,   -93,
     143,   145,    -7,   -93,    65,   -93,   -93,   -93,   139,    65,
     -93
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -93,    30,    -2,   -93,     0,   -23,    24,   -93,   -93,   -93,
     -93,   -93,   121,   -92,   -93,   -93,   -93,   -93,   -93,   -93,
     -93,   -93,   -93,   -93,   -93,   -93,   -93,   -93,   -93,   -93,
     -93,   -93,   -93,     3,   -93,   -93,   -93,    51,   -50,   -93,
      50,   -93,    46,   -93,    54,   -93,    47,   -93,    44,   -93,
      57,   -93,    79,   -93,   -89,   -93,   -93,    59,   -93,   -93,
     -93,   -93,   -93,   -93,   -93,   -93
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -110
static const yytype_int16 yytable[] =
{
      11,     1,    11,   117,   115,    18,    79,    34,    19,     1,
      11,   105,    11,    24,    20,    11,    99,   140,   105,    57,
      58,    59,    60,    61,     1,    51,    31,    32,   -98,    40,
      24,    37,    70,    11,   -57,    37,    37,    11,    11,    67,
      21,    11,    22,    33,    48,    26,   118,   105,    24,    11,
      68,   123,    48,   170,    71,    70,    72,    38,  -109,    35,
     -96,    38,    38,   134,   -95,   165,   136,  -109,    49,   -96,
     102,   169,    50,   -95,   105,   142,   145,   105,   161,    29,
      30,   166,   177,   176,   105,   106,    41,   180,    42,    43,
      44,   158,    93,   114,     1,     2,     3,     4,     5,     6,
       7,    54,    96,   108,   162,   109,   164,   110,     8,   111,
     167,    57,    58,    59,    60,    61,     1,   112,     3,     4,
       5,     6,     7,   113,    62,    63,    64,    65,   147,    66,
       1,    67,     3,     4,     5,     6,     7,    16,   116,   119,
     125,   128,    68,   126,   135,    69,   137,    70,     1,     2,
       3,     4,     5,     6,     7,     1,   139,     3,     4,     5,
       6,     7,   105,   141,   156,   174,   160,   157,   172,   159,
      52,   163,   114,   173,   179,   149,   152,   146,   151,   122,
       0,     0,     0,     0,   150,     0,     0,   148,     0,     0,
     153
};

static const yytype_int16 yycheck[] =
{
       0,     8,     2,    95,    93,     2,    56,    30,     8,     8,
      10,    29,    12,    13,     0,    15,    66,    35,    29,     3,
       4,     5,     6,     7,     8,    48,    32,    27,    39,    33,
      30,    33,    39,    33,     8,    37,    38,    37,    38,    23,
      10,    41,    12,    36,    41,    15,    96,    29,    48,    49,
      34,   101,    49,    35,    56,    39,    56,    33,    32,     3,
      34,    37,    38,   113,    38,   157,   116,    32,    31,    34,
      70,   163,    35,    38,    29,   125,   126,    29,    33,    30,
      31,    33,   174,   172,    29,    30,    34,   179,    37,    38,
      37,   141,    34,    93,     8,     9,    10,    11,    12,    13,
      14,    36,    34,    28,   154,    27,   156,    26,    22,    25,
     160,     3,     4,     5,     6,     7,     8,    24,    10,    11,
      12,    13,    14,    38,    16,    17,    18,    19,   128,    21,
       8,    23,    10,    11,    12,    13,    14,    15,    34,    30,
      34,    39,    34,    32,    30,    37,    17,    39,     8,     9,
      10,    11,    12,    13,    14,     8,    30,    10,    11,    12,
      13,    14,    29,    32,    34,    20,    31,    35,    30,    35,
      49,    35,   172,    30,    35,   129,   132,   127,   131,   100,
      -1,    -1,    -1,    -1,   130,    -1,    -1,   128,    -1,    -1,
     133
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     8,     9,    10,    11,    12,    13,    14,    22,    41,
      42,    44,    46,    73,    74,    75,    15,    72,    73,    44,
       0,    41,    41,    43,    44,    45,    41,    47,    76,    30,
      31,    32,    44,    36,    45,     3,    48,    42,    46,    77,
      33,    34,    77,    77,    37,    50,    51,    52,    73,    31,
      35,    45,    52,    49,    36,    53,    54,     3,     4,     5,
       6,     7,    16,    17,    18,    19,    21,    23,    34,    37,
      39,    42,    44,    55,    56,    60,    63,    65,    69,    78,
      80,    82,    84,    86,    88,    90,    92,    94,    95,    97,
      99,   103,   104,    34,    61,    64,    34,    44,    70,    78,
      91,    93,    44,    98,   105,    29,    30,   100,    28,    27,
      26,    25,    24,    38,    44,    94,    34,    53,    78,    30,
      71,    78,    92,    78,    96,    34,    32,    79,    39,    81,
      83,    85,    87,    89,    78,    30,    78,    17,    66,    30,
      35,    32,    78,   101,   102,    78,    80,    44,    97,    82,
      84,    86,    88,    90,    57,    62,    34,    35,    78,    35,
      31,    33,    78,    35,    78,    53,    33,    78,    58,    53,
      35,    67,    30,    30,    20,    68,    94,    53,    59,    35,
      53
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
#line 67 "storm.y"
    { quadStore.end(); ;}
    break;

  case 7:
#line 74 "storm.y"
    { quadStore.declareVar(); ;}
    break;

  case 8:
#line 75 "storm.y"
    { quadStore.declareVar(); ;}
    break;

  case 9:
#line 77 "storm.y"
    { quadStore.lastIdName = string(yylval.sval); ;}
    break;

  case 10:
#line 79 "storm.y"
    { quadStore.typeIsArray = false; ;}
    break;

  case 11:
#line 80 "storm.y"
    { quadStore.typeIsArray = true; quadStore.lastArraySize = atoi(yylval.sval); quadStore.validateArraySize(); ;}
    break;

  case 12:
#line 82 "storm.y"
    { quadStore.lastReturnType = string(yylval.sval); ;}
    break;

  case 13:
#line 82 "storm.y"
    { quadStore.lastFuncName = string(yylval.sval); ;}
    break;

  case 14:
#line 82 "storm.y"
    { quadStore.declareFunc(); ;}
    break;

  case 15:
#line 82 "storm.y"
    { quadStore.functionExit(); ;}
    break;

  case 20:
#line 89 "storm.y"
    { quadStore.declareParam() ;}
    break;

  case 31:
#line 103 "storm.y"
    { quadStore.forConditionStart(); ;}
    break;

  case 32:
#line 103 "storm.y"
    { quadStore.forConditionEnd(); ;}
    break;

  case 33:
#line 104 "storm.y"
    { quadStore.forStart(); ;}
    break;

  case 34:
#line 104 "storm.y"
    { quadStore.forEnd(); ;}
    break;

  case 35:
#line 106 "storm.y"
    { quadStore.whileConditionStart(); ;}
    break;

  case 36:
#line 106 "storm.y"
    { quadStore.whileBlockStart(); ;}
    break;

  case 37:
#line 106 "storm.y"
    { quadStore.whileEnd(); ;}
    break;

  case 38:
#line 108 "storm.y"
    { quadStore.doWhileStart(); ;}
    break;

  case 39:
#line 108 "storm.y"
    { quadStore.doWhileEnd(); ;}
    break;

  case 40:
#line 110 "storm.y"
    { quadStore.ifStart(); ;}
    break;

  case 41:
#line 110 "storm.y"
    { quadStore.ifBlockEnd(); ;}
    break;

  case 42:
#line 110 "storm.y"
    { quadStore.ifEnd(); ;}
    break;

  case 45:
#line 114 "storm.y"
    { quadStore.returnVoid(); ;}
    break;

  case 47:
#line 115 "storm.y"
    { quadStore.returnExpr(); ;}
    break;

  case 51:
#line 119 "storm.y"
    { quadStore.lastType = string(yylval.sval); ;}
    break;

  case 57:
#line 121 "storm.y"
    { quadStore.validateType(); ;}
    break;

  case 58:
#line 123 "storm.y"
    { quadStore.declareClass(); ;}
    break;

  case 59:
#line 123 "storm.y"
    { quadStore.endClass(); ;}
    break;

  case 63:
#line 128 "storm.y"
    { quadStore.lastOperator = string(yylval.sval); quadStore._operator(); ;}
    break;

  case 64:
#line 128 "storm.y"
    { quadStore.operation(6); ;}
    break;

  case 66:
#line 131 "storm.y"
    { quadStore.lastOperator = string(yylval.sval); quadStore._operator(); ;}
    break;

  case 67:
#line 131 "storm.y"
    { quadStore.operation(5); ;}
    break;

  case 69:
#line 134 "storm.y"
    { quadStore.lastOperator = string(yylval.sval); quadStore._operator(); ;}
    break;

  case 70:
#line 134 "storm.y"
    { quadStore.operation(4); ;}
    break;

  case 72:
#line 137 "storm.y"
    { quadStore.lastOperator = string(yylval.sval); quadStore._operator(); ;}
    break;

  case 73:
#line 137 "storm.y"
    { quadStore.operation(3); ;}
    break;

  case 75:
#line 140 "storm.y"
    { quadStore.lastOperator = string(yylval.sval); quadStore._operator(); ;}
    break;

  case 76:
#line 140 "storm.y"
    { quadStore.operation(2); ;}
    break;

  case 78:
#line 143 "storm.y"
    { quadStore.lastOperator = string(yylval.sval); quadStore._operator(); ;}
    break;

  case 79:
#line 143 "storm.y"
    { quadStore.operation(1); ;}
    break;

  case 81:
#line 146 "storm.y"
    { quadStore.lastOperator = string(yylval.sval); quadStore._operator(); ;}
    break;

  case 82:
#line 146 "storm.y"
    { quadStore.operation(0); ;}
    break;

  case 84:
#line 149 "storm.y"
    { quadStore.openParenthesis(); ;}
    break;

  case 85:
#line 149 "storm.y"
    { quadStore.closeParenthesis(); ;}
    break;

  case 90:
#line 154 "storm.y"
    { quadStore.varExpr(); ;}
    break;

  case 92:
#line 157 "storm.y"
    { quadStore.assign(); ;}
    break;

  case 93:
#line 159 "storm.y"
    { quadStore.initArrAccess(); ;}
    break;

  case 94:
#line 159 "storm.y"
    { quadStore.arrAccess(); ;}
    break;

  case 95:
#line 160 "storm.y"
    { quadStore.initAssign(); ;}
    break;

  case 96:
#line 162 "storm.y"
    { quadStore.fnCallInit(); ;}
    break;

  case 97:
#line 162 "storm.y"
    { quadStore.fnCall(); ;}
    break;

  case 98:
#line 164 "storm.y"
    { quadStore.objFnCallInit() ;}
    break;

  case 102:
#line 168 "storm.y"
    { quadStore.argument(); ;}
    break;

  case 103:
#line 169 "storm.y"
    { quadStore.argument(); ;}
    break;

  case 104:
#line 171 "storm.y"
    { quadStore.literal("int", string(yylval.sval)) ;}
    break;

  case 105:
#line 172 "storm.y"
    { quadStore.literal("float", string(yylval.sval)) ;}
    break;

  case 106:
#line 173 "storm.y"
    { quadStore.literal("string", string(yylval.sval)) ;}
    break;

  case 107:
#line 174 "storm.y"
    { quadStore.literal("char", string(yylval.sval)) ;}
    break;

  case 108:
#line 175 "storm.y"
    { quadStore.literal("bool", string(yylval.sval)) ;}
    break;

  case 109:
#line 177 "storm.y"
    { quadStore.initArrAccess(); ;}
    break;

  case 110:
#line 177 "storm.y"
    { quadStore.arrAccess(); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 1888 "storm.tab.c"
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


#line 179 "storm.y"


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

