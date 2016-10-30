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
using namespace std;

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
extern int linenum;

// maps the name of a function to a function object
FunctionsTable functions;

// symbol table for global variables
SymbolTable globalScopeSymbolTable;

// the most recent identifier read
string lastIdName;

// the most recent type read
string lastType;

// the most recent function name read
string lastFuncName;

// the most recent return type read
string lastReturnType;

// the most recent class name read
string lastClassName;

// the most recent operator read
string lastOperator;

// the most recent array size read
int lastArraySize;

// the list of params of the most recent function read
vector<Param> params;

// maps the name of a class to the class objects
map<string, Class> classes;

// the defined types, including primitives
set<string> types;

// true if currently inside a function
bool inFunction = false;

// true if currently inside a class
inClass = false;

// true if the fn call is a method
isObjFnCall = false;

// true if the type is an array type
typeIsArray = false;

// the stack of the functions beign called.
// When nested calls are made, this is necessary:
// e.g. foo(bar())
stack<string> fnCallStack;

// the type stack
stack<string> typeStack;

// the operator stack
stack<string> operatorStack;

// 
stack<string> arrayAssignStack;

// contains the number of arguments supplied when calling a function
stack<int> fnCallNumArgsStack;

// maps the name of a variable of type array to its array size
map<string, int> arraySizes;

QuadrupleStore quadStore;

// Outputs a semantic error and exits
void semanticError(string err) {
  cout << "Semantic error (l" << linenum << "): " << err << endl;
  exit(1);
}

// Called after reading a parameter from a function
void declareParam() {
  params.push_back(Param(lastIdName, lastType));
}

// called after reading a variable declaration
// stores the variable in the corresponding symbol table and
// checks for redefinitions
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

// read after reading the signature of a function
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

// check that an array size supplied is valid
// called after reading an array size
void validateArraySize() {
  if (lastArraySize <= 0) {
    semanticError("Expected array size greater than 0.");
  }
}

// called after reading the name of a class
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

// called when finishing reading a class
void endClass() {
  inClass = false;
}

// called after reading a type
// checks that the type exists
void validateType() {
  if (classes.count(lastIdName) == 0 && types.count(lastIdName) == 0) {
    semanticError("Undefined type: " + lastIdName);
  }
}

// called when exiting a function declaration
void functionExit() {
  inFunction = false;
}

// called after reading the function name of a function call
// e.g. foo(1, "abc")
// ~~~~~~~~^~~~~~~~~
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

// returns the type of a variable
// first check global score, then function scope, then class scope
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

// called after reading the function name of a method call
void objFnCallInit() {
  isObjFnCall = true;
  typeStack.push(getSymbolType(lastIdName));
}

// called after reading the name of a variable in an identifier
void initAssign() {
  if (getSymbolType(lastIdName) == "") {
    semanticError("Use of undeclared variable: " + lastIdName);
  }

  typeStack.push(getSymbolType(lastIdName));
  quadStore.pushOperand(lastIdName, getSymbolType(lastIdName));
}

// called after reading the right hand expression of an assignment
void assign() {
  string typeAssigned = typeStack.top();
  typeStack.pop(); 
  string varType = typeStack.top();
  typeStack.pop();
  if (varType != typeAssigned) {
    semanticError("Expected " + varType + " found " + typeAssigned);
  }

  quadStore.assignEnd();
}

// called after calling a function
// foo(12, "abc")
// ~~~~~~~~~~~~~^~~
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

// called after reading a literal
void literal(string type) {
  cout << "found literal: " << type << endl;
  typeStack.push(type);
  quadStore.pushConstant(type);
}

// called after reading the variable name of an array type when accessing an array
void initArrAccess() {
  typeStack.push(getSymbolType(lastIdName));
}

// called after reading an array access.
void arrAccess() {
  string indexType = typeStack.top();
  typeStack.pop(); 
  if (indexType != "int") {
    semanticError("Array subscript must be an int; found " + indexType);
  }

  string type = typeStack.top();
  typeStack.pop(); 
  typeStack.push(type.substr(0, type.size()-2));
}

// called after reading the last expression of an operation
void operation(int operatorPriority) {
  quadStore.popOperator(operatorPriority);

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

// called after reading an identifier used as an expression
void varExpr() {
  cout << "found var expr: " << lastIdName << endl;
  typeStack.push(getSymbolType(lastIdName));
  quadStore.pushOperand(lastIdName, getSymbolType(lastIdName));
}

// called after reading a return expression
void returnExpr() {
  string retType = typeStack.top();
  typeStack.pop();
  string fnName = (inClass ? lastClassName + "." : "") + lastFuncName;
  if (functions[lastFuncName].returnType != retType) {
    semanticError("function " + fnName + " expects " + functions[lastFuncName].returnType + " as return type; found " + retType);
  }
}

// called after reading a return void expression
void returnVoid() {
  typeStack.push("void");
  returnExpr();
}

// called after reading an argument in a functino call
void argument() {
  fnCallNumArgsStack.top()++;
}

// called after reading an operator
void _operator() {
  quadStore.pushOperator(lastOperator);
  operatorStack.push(lastOperator);
}

// called after reading an open parenthesis enclosing an expression
void openParenthesis() {
  quadStore.pushParenthesis();
}

// called after reading an open parenthesis enclosing an expression
void closeParenthesis() {
  quadStore.popParenthesis();
}

// called after reading everything
void end() {
  if (functions.count("main") == 0) {
    semanticError("No main function found.");
  }
  cout << " === QUADRUPLES === " << endl;
  quadStore.print();
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
  expr BIN_OP_P6 { lastOperator = string(yylval.sval); _operator(); } expr6 { operation(6); }
  | expr6;
expr6:
  expr6 BIN_OP_P5 { lastOperator = string(yylval.sval); _operator(); } expr5 { operation(5); }
  | expr5;
expr5:
  expr5 BIN_OP_P4 { lastOperator = string(yylval.sval); _operator(); } expr4 { operation(4); }
  | expr4;
expr4: 
  expr4 BIN_OP_P3 { lastOperator = string(yylval.sval); _operator(); } expr3 { operation(3); }
  | expr3;
expr3:
  expr3 BIN_OP_P2 { lastOperator = string(yylval.sval); _operator(); } expr2 { operation(2); }
  | expr2;
expr2:
  expr2 BIN_OP_P1 { lastOperator = string(yylval.sval); _operator(); } expr1 { operation(1); }
  | expr1;
expr1:
  UN_OP_P0 { lastOperator = string(yylval.sval); _operator(); } expr0 { operation(0); }
  | expr0;
expr0:
  '(' { openParenthesis(); } expr ')' { closeParenthesis(); }
  | assign
  | fn_call
  | obj_fn_call
  | literal
  | arr_access
  | id { varExpr(); };
assign:
  assignable '=' expr { assign(); };
assignable:
  id { initAssign(); }
  | id { initAssign(); } '[' expr ']' { arrAccess(); } ;
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
  id { initArrAccess(); } '[' expr ']' { arrAccess(); };

%%

int main(int argc, char** argv) {
  types.insert("int");
  types.insert("float");
  types.insert("char");
  types.insert("bool");
  types.insert("string");
  
  vector<Param> params{ Param("arg", "string") }
  functions["print"] = Function("print", "void", params);
  functions["read"] = Function("read", "string", vector<Param>());

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
