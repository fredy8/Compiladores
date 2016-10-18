%{
#include <cstdio>
#include <iostream>
#include <map>
#include <utility>
#include <stack>
#include <vector>
#include <set>
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
  Function(string name, string returnType, vector<Param> params) : params(params), returnType(returnType), name(name) {}
  Function() {}
};

typedef map<string, Function> FunctionsTable;

FunctionsTable functions;
SymbolTable globalScopeSymbolTable;
stack<SymbolTable> functionScopeSymbolTable;
string lastIdName, lastType, lastFuncName, lastReturnType, lastClassName;
int lastArraySize;
vector<Param> params;
set<string> classes;
stack<string> fnCallInits;

void semanticError(string err) {
  cout << "Semantic error: " << err << endl;
  exit(1);
}

void declareParam() {
  params.push_back(Param(lastIdName, lastType));
}

void declareFunc() {
  functions[lastFuncName] = Function(lastFuncName, lastReturnType, params);
  params.clear();
}

void declareVar() {
  SymbolTable& table = globalScopeSymbolTable;
  if (!functionScopeSymbolTable.empty()) {
    table = functionScopeSymbolTable.top();
  }

  if (table.find(lastIdName) != table.end()) {
    semanticError("Redeclaration of " + lastIdName);
  }

  table[lastIdName] = lastType;
}

void validateArraySize() {
   if (lastArraySize <= 0) {
    semanticError("Expected array size greater than 0.");
   }
}

void declareClass() {
  if (classes.find(lastClassName) != classes.end()) {
    semanticError("Redefinition of class " + lastClassName);
  }

  classes.insert(lastClassName);
}

void validateType() {
  if (classes.find(lastIdName) == classes.end()) {
    semanticError("Undefined type: " + lastIdName);
  }
}

void fnCallInit() {
  if (functions.find(lastIdName) == functions.end()) {
    semanticError("Use of undeclared function: " + lastIdName);
  }

  fnCallInits.push(lastIdName);
}

void fnCall() {
  Function& fn = functions[fnCallInits.top()];
  fnCallInits.pop();
  functionScopeSymbolTable.push(SymbolTable());
  for(auto& param: fn.params) {
    lastIdName = param.paramName;
    lastType = param.paramType;
    declareVar();
  }
}

void functionExit() {
  functionScopeSymbolTable.pop();
}

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
%token UN_OP
%token BIN_OP

%%
// Sintactic variables
program:
  | var_declr program
  | function program
  | class_declr program;
var_declr:
  type var_declr_a ';';
var_declr_a:
  var_arr
  | var_declr_a ',' var_arr;
id:
  ID { lastIdName = string(yylval.sval); } ;
var_arr:
  id
  | id '[' C_INT ']' { lastArraySize = yylval.ival; validateArraySize(); };
function:
  FUNCTION return_type { lastReturnType = string(yylval.sval); } id { lastFuncName = string(yylval.sval); } '(' parameters ')' { declareFunc(); } block;
parameters:
  parameter
  | parameters ',' parameter;
parameter:
  type var_arr { declareParam() };
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
  FOR '(' assign ';' expr ';' assign ')' block;
while_stm:
  WHILE '(' expr ')' block;
do_while_stm:
  DO block WHILE '(' expr ')' ';'
if_stm:
  IF '(' expr ')' block else_stm;
else_stm:
  | ELSE block;
return_stm:
  RETURN ';'
  | RETURN expr ';';
return_type:
  T_VOID | type;
type:
  type_aux { lastType = string(yylval.sval); };
type_aux: 
  T_INT | T_FLOAT | T_STRING | T_CHAR | id { validateType(); };
class_declr:
  CLASS id { lastClassName = string(yylval.sval); declareClass(); } '{' class_declr_a '}';
class_declr_a:
  | var_declr class_declr_a
  | function class_declr_a;
expr:
  assign
  | fn_call
  | obj_fn_call
  | operation
  | '(' expr ')'
  | literal
  | arr_access
  | id;
assign:
  id '=' expr;
operation:
  UN_OP expr
  | expr BIN_OP expr;
fn_call:
  id { fnCallInit(); } '(' arguments ')' { fnCall(); };
obj_fn_call:
  expr '.' fn_call;
arguments:
  | args;
args:
  expr
  | args ',' expr;
literal:
  C_INT | C_FLOAT | C_STRING | C_CHAR;
arr_access:
  id '[' expr ']';

%%

int main(int, char**) {
  // Open a file to read the input from it
#ifdef __APPLE__
  string filename = "test/test1.storm";
#else
  string filename = "test\\test1.storm";
#endif
  FILE *myfile = fopen(filename.c_str(), "r");
  if (!myfile) {
    cout << "I can't open " << filename << "!" << endl;
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
