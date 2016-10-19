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
#include "include/cube.h"
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
string lastIdName, lastType, lastFuncName, lastReturnType, lastClassName, lastOperator;
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
stack<string> operatorStack;
map<string, int> arraySizes;
stack<int> fnCallNumArgsStack;

void semanticError(string err) {
  cout << "Semantic error (l" << linenum << "): " << err << endl;
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
    lastFuncName = lastClassName + "." + lastFuncName;
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
  } else if (inClass && functions.count(lastClassName + "." + lastIdName)) {
    lastIdName = lastClassName + "." + lastIdName;
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

  Function& fn = functions[fnName];
  vector<Param> params = fn.params;
  int numArgsExpected = params.size();
  if (numArgsExpected != numArgs) {
    stringstream ss;
    ss << "function " << fnName << " expects " << numArgsExpected << " argument(s); found " << numArgs;
    semanticError(ss.str());
  }

  for (int i = 0; i < numArgs; i++) {
    string argType = typeStack.top();
    typeStack.pop();
    string paramType = params[params.size() - 1 - i].paramType;
    if (argType != paramType) {
      stringstream ss;
      ss << "function " << fnName << " expects " << paramType << " for its parameter #" << (params.size()-i) << "; found " << argType;
      semanticError(ss.str());
    }
  }

  typeStack.push(fn.returnType);
}

void literal(string type) {
  cout << "found literal: " << type << endl;
  typeStack.push(type);
}

void initArrAccess() {
  typeStack.push(getSymbolType(lastIdName));
}

void arrAccess() {
  typeStack.pop(); 
  string type = typeStack.top();
  typeStack.pop(); 
  typeStack.push(type.substr(0, type.size()-2));
}

void operation() {
  string t2 = typeStack.top();
  typeStack.pop();
  string t1 = typeStack.top();
  typeStack.pop();
  string op = operatorStack.top();
  operatorStack.pop();
  string resultType = Cube::getOperationType(op, t1, t2);
  if (resultType == "") {
    semanticError("Invalid operation: " + t1 + " " + op + " " + t2);
  }

  typeStack.push(resultType);
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

void _operator() {
  operatorStack.push(lastOperator);
}

void _conditional() {
  string type = typeStack.top();
  typeStack.pop();
  if (type != "bool") {
    semanticError("Expected bool, found " + type);
  }
}

void end() {
  if (functions.count("main") == 0) {
    semanticError("No main function found.");
  }
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
  { end(); }
  | var_declr program
  | function program
  | class_declr program;
var_declr:
  type var_declr_a ';';
var_declr_a:
  var_arr { declareVar(); }
  | var_declr_a ',' var_arr { declareVar(); };
id:
  ID { lastIdName = string(yylval.sval); } ;
var_arr:
  id { typeIsArray = false; }
  | id '[' C_INT ']' { typeIsArray = true; lastArraySize = yylval.ival; validateArraySize(); };
function:
  FUNCTION return_type { lastReturnType = string(yylval.sval); } id { lastFuncName = string(yylval.sval); } '(' parameters ')' { declareFunc(); } block { functionExit(); };
parameters:
  | params;
params:
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
  FOR '(' assign ';' expr { _conditional(); } ';' assign ')' block;
while_stm:
  WHILE '(' expr { _conditional(); } ')' block;
do_while_stm:
  DO block WHILE '(' expr { _conditional(); } ')' ';'
if_stm:
  IF '(' expr { _conditional(); } ')' block else_stm;
else_stm:
  | ELSE block;
return_stm:
  RETURN { returnVoid(); } ';'
  | RETURN expr { returnExpr(); } ';';
return_type:
  T_VOID | type;
type:
  type_aux { lastType = string(yylval.sval); };
type_aux: 
  T_INT | T_FLOAT | T_STRING | T_CHAR | id { validateType(); };
class_declr:
  CLASS id { declareClass(); } '{' class_declr_a '}' { endClass(); };
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
  | id { varExpr(); };
assign:
  assignable { initAssign(); } '=' expr { assign(); };
assignable:
  id
  | id '[' expr ']';
operation:
  UN_OP expr
  | expr BIN_OP { lastOperator = string(yylval.sval); _operator(); } expr { operation(); };
fn_call:
  id { fnCallInit(); } '(' arguments ')' { fnCall(); };
obj_fn_call:
  expr { objFnCallInit() } '.' fn_call;
arguments:
  | args;
args:
  expr { argument(); }
  | args ',' expr { argument(); };
literal:
  C_INT { literal("int") } | C_FLOAT { literal("float") } | C_STRING { literal("string") } | C_CHAR { literal("char") };
arr_access:
  id { initArrAccess(); } '[' expr ']' { arrAccess() };

%%

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
