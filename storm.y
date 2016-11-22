%{
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
%}

%union {
  int ival;
  float fval;
  char *sval;
  char cval;
}

%token<ival> C_INT
%token<fval> C_FLOAT
%token<sval> C_STRING
%token<cval> C_CHAR
%token<sval> ID
%token FUNCTION
%token T_INT
%token T_FLOAT
%token T_STRING
%token T_CHAR
%token T_VOID
%token FOR
%token WHILE
%token DO
%token IF
%token ELSE
%token RETURN
%token CLASS
%token UN_OP_P0
%token BIN_OP_P1
%token BIN_OP_P2
%token BIN_OP_P3
%token BIN_OP_P4
%token BIN_OP_P5
%token BIN_OP_P6

%%
// Sintactic variables
program:
  { quadStore.end(); }
  | var_declr program
  | function program
  | class_declr program;
var_declr:
  type var_declr_a ';';
var_declr_a:
  var_arr { quadStore.declareVar(); }
  | var_declr_a ',' var_arr { quadStore.declareVar(); };
id:
  ID { quadStore.lastIdName = string(yylval.sval); } ;
var_arr:
  id { quadStore.typeIsArray = false; }
  | id '[' C_INT ']' { quadStore.typeIsArray = true; quadStore.lastArraySize = atoi(yylval.sval); quadStore.validateArraySize(); };
function:
  FUNCTION return_type { quadStore.lastReturnType = string(yylval.sval); } id { quadStore.lastFuncName = string(yylval.sval); } '(' parameters ')' { quadStore.declareFunc(); } block { quadStore.functionExit(); };
parameters:
  | params;
params:
  parameter
  | parameters ',' parameter;
parameter:
  type var_arr { quadStore.declareParam() };
block:
  '{' statements '}';
statements:
  | statements statement;
statement:
  var_declr
  | expr ';'
  | for_stm
  | while_stm
  | do_while_stm
  | if_stm
  | return_stm;
for_stm:
  FOR '(' assign ';' { quadStore.forConditionStart(); } expr { quadStore.forConditionEnd(); } ';' 
    assign { quadStore.forStart(); } ')' block { quadStore.forEnd(); };
while_stm:
  WHILE { quadStore.whileConditionStart(); } '(' expr { quadStore.whileBlockStart(); } ')' block { quadStore.whileEnd(); };
do_while_stm:
  DO { quadStore.doWhileStart(); } block WHILE '(' expr ')' ';' { quadStore.doWhileEnd(); };
if_stm:
  IF '(' expr { quadStore.ifStart(); } ')' block { quadStore.ifBlockEnd(); } else_stm { quadStore.ifEnd(); };
else_stm:
  | ELSE block;
return_stm:
  RETURN { quadStore.returnVoid(); } ';'
  | RETURN expr { quadStore.returnExpr(); } ';';
return_type:
  T_VOID | type;
type:
  type_aux { quadStore.lastType = string(yylval.sval); };
type_aux: 
  T_INT | T_FLOAT | T_STRING | T_CHAR | id { quadStore.validateType(); };
class_declr:
  CLASS id { quadStore.declareClass(); } '{' class_declr_a '}' { quadStore.endClass(); };
class_declr_a:
  | var_declr class_declr_a
  | function class_declr_a;
expr:
  expr BIN_OP_P6 { quadStore.lastOperator = string(yylval.sval); quadStore._operator(); } expr6 { quadStore.operation(6); }
  | expr6;
expr6:
  expr6 BIN_OP_P5 { quadStore.lastOperator = string(yylval.sval); quadStore._operator(); } expr5 { quadStore.operation(5); }
  | expr5;
expr5:
  expr5 BIN_OP_P4 { quadStore.lastOperator = string(yylval.sval); quadStore._operator(); } expr4 { quadStore.operation(4); }
  | expr4;
expr4: 
  expr4 BIN_OP_P3 { quadStore.lastOperator = string(yylval.sval); quadStore._operator(); } expr3 { quadStore.operation(3); }
  | expr3;
expr3:
  expr3 BIN_OP_P2 { quadStore.lastOperator = string(yylval.sval); quadStore._operator(); } expr2 { quadStore.operation(2); }
  | expr2;
expr2:
  expr2 BIN_OP_P1 { quadStore.lastOperator = string(yylval.sval); quadStore._operator(); } expr1 { quadStore.operation(1); }
  | expr1;
expr1:
  UN_OP_P0 { quadStore.lastOperator = string(yylval.sval); quadStore._operator(); } expr0 { quadStore.operation(0); }
  | expr0;
expr0:
  '(' { quadStore.openParenthesis(); } expr ')' { quadStore.closeParenthesis(); }
  | assign
  | fn_call
  | obj_fn_call
  | literal
  | arr_access
  | id { quadStore.varExpr(); };
assign:
  assignable '=' expr { quadStore.assign(); };
assignable:
  id { quadStore.initAssign(); }
  | id { quadStore.initArrAccess(); } '[' expr ']' { quadStore.arrAccess(); } ;
fn_call:
  id { quadStore.fnCallInit(); } '(' arguments ')' { quadStore.fnCall(); };
obj_fn_call:
  expr { quadStore.objFnCallInit() } '.' fn_call;
arguments:
  | args;
args:
  expr { quadStore.argument(); }
  | args ',' expr { quadStore.argument(); };
literal:
  C_INT { quadStore.literal("int", string(yylval.sval)) } | C_FLOAT { quadStore.literal("float", string(yylval.sval)) } | C_STRING { quadStore.literal("string", string(yylval.sval)) } | C_CHAR { quadStore.literal("char", string(yylval.sval)) };
arr_access:
  id { quadStore.initArrAccess(); } '[' expr ']' { quadStore.arrAccess(); };

%%

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
}

void yyerror(const char *s) {
  // Print an error message along with the line number where it failed
  cout << "EEK, parse error on line " << linenum << "!  Message: " << s << endl;
  exit(-1);
}
