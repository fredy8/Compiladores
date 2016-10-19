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




/* Copy the first part of user declarations.  */
#line 1 "storm.y"

#include <cstdio>
#include <iostream>
#include <map>
#include <utility>
#include <stack>
#include <vector>
#include <set>
#include <sstream>
using namespace std;

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
extern int linenum;

typedef map<string, string> SymbolTable;

struct Param {
 public:
  string paramName, paramType;
  Param(string paramName, string paramType) : paramName(paramName), paramType(paramType) {}
};

struct Function {
 public:
  string name;
  string returnType;
  vector<Param> params;
  SymbolTable localSymbolTable;
  Function(string name, string returnType, vector<Param> params) : params(params), returnType(returnType), name(name) {}
  Function() {}
};

struct Class {
 public:
  string name;
  SymbolTable classSymbolTable;
  Class(string name) {}
  Class() {}
};

typedef map<string, Function> FunctionsTable;

FunctionsTable functions;
SymbolTable globalScopeSymbolTable;
string lastIdName, lastType, lastFuncName, lastReturnType, lastClassName;
int lastArraySize;
vector<Param> params;
map<string, Class> classes;
set<string> types;
bool inFunction = false;
bool inClass = false;
bool typeIsArray;
bool isObjFnCall = false;
stack<string> fnCallStack;
stack<string> typeStack;
map<string, int> arraySizes;
stack<int> fnCallNumArgsStack;

void semanticError(string err) {
  cout << "Semantic error: " << err << endl;
  exit(1);
}

void declareParam() {
  params.push_back(Param(lastIdName, lastType));
}

void declareVar() {
  SymbolTable* table = &globalScopeSymbolTable;
  if (inFunction) {
    table = &functions[lastFuncName].localSymbolTable;

    if (table->find(lastIdName) != table->end()) {
      semanticError("Redeclaration of " + lastIdName);
    }
  } else if (inClass) {
    table = &classes[lastClassName].classSymbolTable;

    if (table->find(lastIdName) != table->end()) {
      semanticError("Redeclaration of " + lastIdName);
    }
  }

  if (globalScopeSymbolTable.find(lastIdName) != globalScopeSymbolTable.end()) {
    semanticError("Redeclaration of " + lastIdName);
  }
  
  if (typeIsArray) {
    arraySizes[lastIdName] = lastArraySize;
    lastType += "[]";
  }

  table->operator[](lastIdName) = lastType;
  cout << "var declared: " << lastIdName << endl;
}

void declareFunc() {
  if (inClass) {
    lastIdName = lastClassName + "." + lastClassName;
  }

  if (functions.find(lastFuncName) != functions.end()) {
    semanticError("Redefinition of function " + lastFuncName);
  }

  Function fn = Function(lastFuncName, lastReturnType, params);
  functions[lastFuncName] = fn;
  params.clear();
  inFunction = true;

  cout << "function declared: " << lastFuncName << endl;

  for(auto& param: fn.params) {
    lastIdName = param.paramName;
    lastType = param.paramType;
    declareVar();
  } 
}

void validateArraySize() {
  if (lastArraySize <= 0) {
    semanticError("Expected array size greater than 0.");
  }
}

void declareClass() {
  inClass = true;
  lastClassName = lastIdName;
  if (classes.find(lastIdName) != classes.end()) {
    semanticError("Redefinition of class " + lastIdName);
  }

  if (types.find(lastIdName) != types.end() || lastIdName == "void") {
    semanticError("Invalid class name: " + lastIdName);
  }

  classes[lastIdName] = Class(lastIdName);
  cout << "class declared: " << lastIdName << endl;
}

void endClass() {
  inClass = false;
}

void exitClass() {
  inClass = false;
}

void validateType() {
  if (classes.count(lastIdName) == 0 && types.count(lastIdName) == 0) {
    semanticError("Undefined type: " + lastIdName);
  }
}

void functionExit() {
  inFunction = false;
}

void fnCallInit() {
  if (isObjFnCall) {
    string objType = typeStack.top();
    typeStack.pop();
    lastIdName = objType + "." + lastIdName;
  }

  if (functions.find(lastIdName) == functions.end()) {
    semanticError("Use of undeclared function " + lastIdName);
  }

  fnCallStack.push(lastIdName);
  fnCallNumArgsStack.push(0);
  isObjFnCall = false;
}

string getSymbolType(string varName) {
  if (globalScopeSymbolTable.find(varName) != globalScopeSymbolTable.end()) {
    return globalScopeSymbolTable[varName];
  }

  if (inFunction && functions[lastFuncName].localSymbolTable.count(varName)) {
    return functions[lastFuncName].localSymbolTable[varName];
  }

  if (inClass && classes[lastClassName].classSymbolTable.count(varName)) {
    return classes[lastClassName].classSymbolTable[varName];
  }

  return "";
}

void objFnCallInit() {
  isObjFnCall = true;
  typeStack.push(getSymbolType(lastIdName));
}

void initAssign() {
  cout << "initAssign " << getSymbolType(lastIdName) << endl;
  if (getSymbolType(lastIdName) == "") {
    semanticError("Use of undeclared variable: " + lastIdName);
  }

  typeStack.push(getSymbolType(lastIdName));
}

void assign() {
  string typeAssigned = typeStack.top();
  typeStack.pop(); 
  string varType = typeStack.top();
  typeStack.pop();
  if (varType != typeAssigned) {
    semanticError("Expected " + varType + " found " + typeAssigned);
  }
}

void fnCall() {
  string fnName = fnCallStack.top();
  fnCallStack.pop();
  int numArgs = fnCallNumArgsStack.top();
  fnCallNumArgsStack.pop();
  vector<Param> params = functions[fnName].params;
  int numArgsExpected = params.size();
  if (numArgsExpected != numArgs) {
    stringstream ss;
    ss << "function " << fnName << " expects " << numArgsExpected << "; found " << numArgs;
    semanticError(ss.str());
  }

  for (int i = 0; i < numArgs; i++) {
    string argType = typeStack.top();
    typeStack.pop();
    if (argType != params[i].paramType) {
      stringstream ss;
      ss << "function " << fnName << " expects " << params[i].paramType << " for its parameter #" << (i+1) << "; found " << argType;
      semanticError(ss.str());
    }
  }
}

void literal(string type) {
  cout << "found literal: " << type << endl;
  typeStack.push(type);
}

void initArrAccess() {
  typeStack.push(getSymbolType(lastIdName));
}

void arrAccess() {
  string type = typeStack.top();
  typeStack.pop(); 
  typeStack.push(type.substr(type.size()-2));
}

void operation() {
  typeStack.pop();
}

void varExpr() {
  cout << "found var expr: " << lastIdName << endl;
  typeStack.push(getSymbolType(lastIdName));
}

void returnExpr() {
  string retType = typeStack.top();
  typeStack.pop();
  string fnName = (inClass ? lastClassName + "." : "") + lastFuncName;
  if (functions[lastFuncName].returnType != retType) {
    semanticError("function " + fnName + " expects " + functions[lastFuncName].returnType + " as return type; found " + retType);
  }
}

void returnVoid() {
  typeStack.push("void");
  returnExpr();
}

void argument() {
  fnCallNumArgsStack.top()++;
}

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
#line 287 "storm.y"
{
  int ival;
  float fval;
  char *sval;
  char cval;
}
/* Line 193 of yacc.c.  */
#line 433 "storm.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 446 "storm.tab.c"

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
#define YYFINAL  19
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   158

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNRULES -- Number of states.  */
#define YYNSTATES  139

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   277

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      27,    28,     2,     2,    24,     2,    32,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    23,
       2,    31,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    25,     2,    26,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    29,     2,    30,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    13,    17,    19,    23,
      25,    27,    32,    33,    34,    35,    46,    48,    52,    55,
      59,    60,    63,    65,    68,    70,    72,    74,    76,    78,
      88,    94,   102,   109,   110,   113,   114,   118,   119,   124,
     126,   128,   130,   132,   134,   136,   138,   140,   141,   148,
     149,   152,   155,   157,   159,   161,   163,   167,   169,   171,
     173,   174,   179,   182,   186,   187,   193,   194,   199,   200,
     202,   204,   208,   210,   212,   214,   216,   217
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      34,     0,    -1,    -1,    35,    34,    -1,    39,    34,    -1,
      59,    34,    -1,    57,    36,    23,    -1,    38,    -1,    36,
      24,    38,    -1,     7,    -1,    37,    -1,    37,    25,     3,
      26,    -1,    -1,    -1,    -1,     8,    56,    40,    37,    41,
      27,    43,    28,    42,    45,    -1,    44,    -1,    43,    24,
      44,    -1,    57,    38,    -1,    29,    46,    30,    -1,    -1,
      46,    47,    -1,    35,    -1,    62,    23,    -1,    48,    -1,
      49,    -1,    50,    -1,    51,    -1,    53,    -1,    14,    27,
      63,    23,    62,    23,    63,    28,    45,    -1,    15,    27,
      62,    28,    45,    -1,    16,    45,    15,    27,    62,    28,
      23,    -1,    17,    27,    62,    28,    45,    52,    -1,    -1,
      18,    45,    -1,    -1,    19,    54,    23,    -1,    -1,    19,
      62,    55,    23,    -1,    13,    -1,    57,    -1,    58,    -1,
       9,    -1,    10,    -1,    11,    -1,    12,    -1,    37,    -1,
      -1,    20,    37,    60,    29,    61,    30,    -1,    -1,    35,
      61,    -1,    39,    61,    -1,    63,    -1,    66,    -1,    68,
      -1,    65,    -1,    27,    62,    28,    -1,    72,    -1,    73,
      -1,    37,    -1,    -1,    37,    64,    31,    62,    -1,    21,
      62,    -1,    62,    22,    62,    -1,    -1,    37,    67,    27,
      70,    28,    -1,    -1,    62,    69,    32,    66,    -1,    -1,
      71,    -1,    62,    -1,    71,    24,    62,    -1,     3,    -1,
       4,    -1,     5,    -1,     6,    -1,    -1,    37,    74,    25,
      62,    26,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   317,   317,   318,   319,   320,   322,   324,   325,   327,
     329,   330,   332,   332,   332,   332,   334,   335,   337,   339,
     340,   341,   343,   344,   345,   346,   347,   348,   349,   351,
     353,   355,   357,   358,   359,   361,   361,   362,   362,   364,
     364,   366,   368,   368,   368,   368,   368,   370,   370,   371,
     372,   373,   375,   376,   377,   378,   379,   380,   381,   382,
     384,   384,   386,   387,   389,   389,   391,   391,   392,   393,
     395,   396,   398,   398,   398,   398,   400,   400
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "C_INT", "C_FLOAT", "C_STRING", "C_CHAR",
  "ID", "FUNCTION", "T_INT", "T_FLOAT", "T_STRING", "T_CHAR", "T_VOID",
  "FOR", "WHILE", "DO", "IF", "ELSE", "RETURN", "CLASS", "UN_OP", "BIN_OP",
  "';'", "','", "'['", "']'", "'('", "')'", "'{'", "'}'", "'='", "'.'",
  "$accept", "program", "var_declr", "var_declr_a", "id", "var_arr",
  "function", "@1", "@2", "@3", "parameters", "parameter", "block",
  "statements", "statement", "for_stm", "while_stm", "do_while_stm",
  "if_stm", "else_stm", "return_stm", "@4", "@5", "return_type", "type",
  "type_aux", "class_declr", "@6", "class_declr_a", "expr", "assign", "@7",
  "operation", "fn_call", "@8", "obj_fn_call", "@9", "arguments", "args",
  "literal", "arr_access", "@10", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,    59,    44,    91,    93,    40,    41,   123,
     125,    61,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    33,    34,    34,    34,    34,    35,    36,    36,    37,
      38,    38,    40,    41,    42,    39,    43,    43,    44,    45,
      46,    46,    47,    47,    47,    47,    47,    47,    47,    48,
      49,    50,    51,    52,    52,    54,    53,    55,    53,    56,
      56,    57,    58,    58,    58,    58,    58,    60,    59,    61,
      61,    61,    62,    62,    62,    62,    62,    62,    62,    62,
      64,    63,    65,    65,    67,    66,    69,    68,    70,    70,
      71,    71,    72,    72,    72,    72,    74,    73
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     3,     1,     3,     1,
       1,     4,     0,     0,     0,    10,     1,     3,     2,     3,
       0,     2,     1,     2,     1,     1,     1,     1,     1,     9,
       5,     7,     6,     0,     2,     0,     3,     0,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     6,     0,
       2,     2,     1,     1,     1,     1,     3,     1,     1,     1,
       0,     4,     2,     3,     0,     5,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     0,     5
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     9,     0,    42,    43,    44,    45,     0,     0,     2,
      46,     2,     0,    41,     2,    39,    12,    40,    47,     1,
       3,     4,     0,    10,     7,     5,     0,     0,     6,     0,
       0,    13,    49,     8,     0,     0,    49,    49,     0,    11,
       0,    50,    51,    48,     0,    16,     0,     0,    14,    18,
      17,     0,    20,    15,     0,    72,    73,    74,    75,     0,
       0,     0,     0,    35,     0,     0,    19,    22,    59,    21,
      24,    25,    26,    27,    28,    66,    52,    55,    53,    54,
      57,    58,     0,     0,     0,     0,    59,     0,    37,    62,
      66,     0,     0,     0,     0,    23,     0,    60,     0,    66,
       0,    66,    36,     0,    56,     0,    68,     0,    63,     0,
       0,     0,     0,     0,    38,    61,    70,     0,    69,    66,
      64,    67,    66,    30,    66,    33,    65,     0,    77,     0,
       0,     0,    32,    71,     0,    31,    34,     0,    29
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     8,     9,    22,    86,    24,    11,    26,    35,    51,
      44,    45,    53,    54,    69,    70,    71,    72,    73,   132,
      74,    87,   103,    16,    12,    13,    14,    27,    38,    75,
      76,    91,    77,    78,    92,    79,    96,   117,   118,    80,
      81,    93
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -78
static const yytype_int16 yypact[] =
{
     105,   -78,    94,   -78,   -78,   -78,   -78,    -4,     8,   105,
     -78,   105,    -4,   -78,   105,   -78,   -78,   -78,   -78,   -78,
     -78,   -78,    57,    -1,   -78,   -78,    -4,    38,   -78,    -4,
      86,   -78,   111,   -78,    68,     4,   111,   111,    69,   -78,
     121,   -78,   -78,   -78,    50,   -78,    -4,   121,   -78,   -78,
     -78,    95,   -78,   -78,    81,   -78,   -78,   -78,   -78,    83,
     110,    95,   114,    52,    52,    52,   -78,   -78,     3,   -78,
     -78,   -78,   -78,   -78,   -78,   104,   -78,   -78,   -78,   -78,
     -78,   -78,    -4,    52,   127,    52,    45,   120,    -7,   122,
      -6,   115,   118,   123,    52,   -78,   117,   -78,   124,     5,
     125,    16,   -78,   128,   -78,    52,    52,    52,   122,    -4,
      52,    95,    52,    95,   -78,   122,    -7,   126,   129,   112,
     -78,   -78,   113,   -78,    47,   132,   -78,    52,   -78,    -4,
     133,    95,   -78,    -7,   130,   -78,   -78,    95,   -78
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -78,    34,   -19,   -78,     0,   -23,    28,   -78,   -78,   -78,
     -78,   108,   -60,   -78,   -78,   -78,   -78,   -78,   -78,   -78,
     -78,   -78,   -78,   -78,     2,   -78,   -78,   -78,   103,   -44,
     -77,   -78,   -78,    48,   -78,   -78,   -78,   -78,   -78,   -78,
     -78,   -78
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -77
static const yytype_int16 yytable[] =
{
      10,    84,    10,     1,    17,    98,    33,    18,    19,    10,
     -46,    10,    23,    36,    10,    94,    94,    36,    36,    88,
      89,    90,   104,    49,    30,   -66,    31,    94,   -76,    23,
     -64,    40,    10,   111,   -60,    67,    10,    10,    94,    99,
      10,   101,    46,    20,   113,    21,    23,    10,    25,    46,
     108,   123,   134,   125,    68,    55,    56,    57,    58,     1,
      37,   115,   116,   119,    37,    37,   122,    32,   124,    94,
     -76,   136,   -64,    64,    47,   130,   -60,   138,    48,    65,
      28,    29,    97,   133,    55,    56,    57,    58,     1,    34,
       3,     4,     5,     6,    39,    59,    60,    61,    62,    43,
      63,     1,    64,     3,     4,     5,     6,    15,    65,   120,
      82,    66,     1,     2,     3,     4,     5,     6,     1,     2,
       3,     4,     5,     6,    52,     7,    94,    95,     1,    97,
       3,     4,     5,     6,    94,    94,   129,    83,   128,    41,
      42,    85,   100,   102,    94,   106,   105,   110,   107,   109,
     131,   114,   112,   127,   126,    50,   135,   121,   137
};

static const yytype_uint8 yycheck[] =
{
       0,    61,     2,     7,     2,    82,    29,     7,     0,     9,
       7,    11,    12,    32,    14,    22,    22,    36,    37,    63,
      64,    65,    28,    46,    25,    32,    26,    22,    25,    29,
      27,    27,    32,    28,    31,    54,    36,    37,    22,    83,
      40,    85,    40,     9,    28,    11,    46,    47,    14,    47,
      94,   111,   129,   113,    54,     3,     4,     5,     6,     7,
      32,   105,   106,   107,    36,    37,   110,    29,   112,    22,
      25,   131,    27,    21,    24,    28,    31,   137,    28,    27,
      23,    24,    82,   127,     3,     4,     5,     6,     7,     3,
       9,    10,    11,    12,    26,    14,    15,    16,    17,    30,
      19,     7,    21,     9,    10,    11,    12,    13,    27,   109,
      27,    30,     7,     8,     9,    10,    11,    12,     7,     8,
       9,    10,    11,    12,    29,    20,    22,    23,     7,   129,
       9,    10,    11,    12,    22,    22,    23,    27,    26,    36,
      37,    27,    15,    23,    22,    27,    31,    23,    25,    32,
      18,    23,    27,    24,    28,    47,    23,   109,    28
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,     8,     9,    10,    11,    12,    20,    34,    35,
      37,    39,    57,    58,    59,    13,    56,    57,    37,     0,
      34,    34,    36,    37,    38,    34,    40,    60,    23,    24,
      25,    37,    29,    38,     3,    41,    35,    39,    61,    26,
      27,    61,    61,    30,    43,    44,    57,    24,    28,    38,
      44,    42,    29,    45,    46,     3,     4,     5,     6,    14,
      15,    16,    17,    19,    21,    27,    30,    35,    37,    47,
      48,    49,    50,    51,    53,    62,    63,    65,    66,    68,
      72,    73,    27,    27,    45,    27,    37,    54,    62,    62,
      62,    64,    67,    74,    22,    23,    69,    37,    63,    62,
      15,    62,    23,    55,    28,    31,    27,    25,    62,    32,
      23,    28,    27,    28,    23,    62,    62,    70,    71,    62,
      37,    66,    62,    45,    62,    45,    28,    24,    26,    23,
      28,    18,    52,    62,    63,    23,    45,    28,    45
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
        case 7:
#line 324 "storm.y"
    { declareVar(); ;}
    break;

  case 8:
#line 325 "storm.y"
    { declareVar(); ;}
    break;

  case 9:
#line 327 "storm.y"
    { lastIdName = string(yylval.sval); ;}
    break;

  case 10:
#line 329 "storm.y"
    { typeIsArray = false; ;}
    break;

  case 11:
#line 330 "storm.y"
    { typeIsArray = true; lastArraySize = yylval.ival; validateArraySize(); ;}
    break;

  case 12:
#line 332 "storm.y"
    { lastReturnType = string(yylval.sval); ;}
    break;

  case 13:
#line 332 "storm.y"
    { lastFuncName = string(yylval.sval); ;}
    break;

  case 14:
#line 332 "storm.y"
    { declareFunc(); ;}
    break;

  case 15:
#line 332 "storm.y"
    { functionExit(); ;}
    break;

  case 18:
#line 337 "storm.y"
    { declareParam() ;}
    break;

  case 35:
#line 361 "storm.y"
    { returnVoid(); ;}
    break;

  case 37:
#line 362 "storm.y"
    { returnExpr(); ;}
    break;

  case 41:
#line 366 "storm.y"
    { lastType = string(yylval.sval); ;}
    break;

  case 46:
#line 368 "storm.y"
    { validateType(); ;}
    break;

  case 47:
#line 370 "storm.y"
    { declareClass(); ;}
    break;

  case 48:
#line 370 "storm.y"
    { endClass(); ;}
    break;

  case 59:
#line 382 "storm.y"
    { varExpr(); ;}
    break;

  case 60:
#line 384 "storm.y"
    { initAssign(); ;}
    break;

  case 61:
#line 384 "storm.y"
    { assign(); ;}
    break;

  case 63:
#line 387 "storm.y"
    { operation(); ;}
    break;

  case 64:
#line 389 "storm.y"
    { fnCallInit(); ;}
    break;

  case 65:
#line 389 "storm.y"
    { fnCall(); ;}
    break;

  case 66:
#line 391 "storm.y"
    { objFnCallInit() ;}
    break;

  case 70:
#line 395 "storm.y"
    { argument(); ;}
    break;

  case 71:
#line 396 "storm.y"
    { argument(); ;}
    break;

  case 72:
#line 398 "storm.y"
    { literal("int") ;}
    break;

  case 73:
#line 398 "storm.y"
    { literal("float") ;}
    break;

  case 74:
#line 398 "storm.y"
    { literal("string") ;}
    break;

  case 75:
#line 398 "storm.y"
    { literal("char") ;}
    break;

  case 76:
#line 400 "storm.y"
    { initArrAccess(); ;}
    break;

  case 77:
#line 400 "storm.y"
    { arrAccess() ;}
    break;


/* Line 1267 of yacc.c.  */
#line 1921 "storm.tab.c"
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


#line 402 "storm.y"


int main(int argc, char** argv) {
  types.insert("int");
  types.insert("float");
  types.insert("char");
  types.insert("bool");
  types.insert("string");

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
  
}

void yyerror(const char *s) {
  // Print an error message along with the line number where it failed
  cout << "EEK, parse error on line " << linenum << "!  Message: " << s << endl;
  exit(-1);
}

