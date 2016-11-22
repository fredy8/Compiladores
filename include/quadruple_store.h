#include <vector>
#include <cassert>
#include <sstream>
#include <stack>
#include "cube.h"
#include "quadruple.h"
#include "function.h"
#include "class.h"
#include "symbol_table.h"
#include "memory_map.h"

const bool DEBUG = false;

using namespace std;

class QuadrupleStore {
public:
  MemoryMap memory_map;
  std::vector<Quadruple> quads;
  std::stack<std::string> typeStack;
  std::stack<std::string> operandStack;
  std::stack<std::string> operatorStack;
  std::stack<int> jumpStack;
  int counter = 0;
  int tempCounter = 0;
  int constCounter = 0;
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
  bool inClass = false;
  // true if the fn call is a method
  bool isObjFnCall = false;
  // true if the type is an array type
  bool typeIsArray = false;
  // the stack of the functions beign called.
  // When nested calls are made, this is necessary:
  // e.g. foo(bar())
  stack<string> fnCallStack;
  // contains the number of arguments supplied when calling a function
  stack<int> fnCallNumArgsStack;
  // maps the name of a variable of type array to its array size
  map<string, int> arraySizes;
public:
  void printOperandStack() {
    stack<string> copy = operandStack;
    cout << "OPERAND STACK" << endl;
    while(!copy.empty()) {
      cout << copy.top() << endl;
      copy.pop();
    }
    cout << "----------------" << endl;
  }
  void debug(string message) {
    cout << message << endl;
    if (DEBUG) {
      cout << "c: continue\no: view operand stack" << endl;
      string cmd;
      while(cin >> cmd) {
        if (cmd == "c") break;
        if (cmd == "o") printOperandStack();
      }
      cout << endl << endl;
    }
  }
  void pushOperand(std::string operand, std::string type) {
    operandStack.push(operand);
    typeStack.push(type);
  }
  void pushConstant(std::string type, string value) {
    cout << value << "*****" << endl;
    operandStack.push(getConstantVariable(type, value));
    typeStack.push(type);
  }
  void pushOperator(std::string oper) {
    operatorStack.push(oper);
  }
  void popOperator(int priority) {
    // Check whether the next operator to evaluate has the expected priority
    if (operatorStack.empty()) {
      return;
    }
    std::string oper = operatorStack.top();
    int operPriority = getOperPriority(oper);
    if (operPriority != priority) {
      return;
    }
    operatorStack.pop();

    // Pop operands and types from their stacks
    std::string type1 = "", operand1 = "", type2 = "", operand2 = "";
    if (operPriority != 0) { // If it's a binary operator
      type2 = typeStack.top();
      operand2 = operandStack.top();
      typeStack.pop();
      operandStack.pop();
    }
    type1 = typeStack.top();
    operand1 = operandStack.top();
    typeStack.pop();
    operandStack.pop();

    // Check whether it's a valid operation with the semantic cube
    std::string resultType = Cube::getOperationType(oper, type1, type2);
    if (resultType == "") {
      semanticError("Invalid operation: " + type1 + " " + oper + " " + type2);
    }

    // Push new quadruple and result to stacks
    std::string result = getTemporalVariable(resultType);
    std::string b = memory_map.Get(operand1, type1);
    std::string c = (operand2 == "" ? "" : memory_map.Get(operand2, type2));
    std::string d = memory_map.Get(result, resultType);
    typeStack.push(resultType);
    operandStack.push(result);
    quads.emplace_back(Quadruple(oper, b, c, d));
    counter++;
  }
  void pushParenthesis() {
    operatorStack.push("(");
  }
  void popParenthesis() {
    if (operatorStack.empty() || operatorStack.top() != "(") {
      semanticError("Expected parenthesis on the top of the stack");
    }
    operatorStack.pop();
  }
  void ifStart() {
    // Get information on the conditional and validate it's a bool
    std::string type = typeStack.top();
    typeStack.pop();
    std::string condition = operandStack.top();
    operandStack.pop();
    if (type != "bool") {
      semanticError("Expected bool on if statement");
    }
    // Generate GOTOF quadruple and store the counter to modify it later
    jumpStack.push(counter);
    quads.push_back(Quadruple("GOTOF", memory_map.Get(condition, "bool"), "", ""));
    counter++;
  }
  void ifBlockEnd() {
    // Modify if statement quadruple to jump to the end of block
    int ifQuad = jumpStack.top();
    jumpStack.pop();
    quads[ifQuad].d = toString(counter + 1);
    // Add GOTO jump to the end of the if statement and store the counter
    jumpStack.push(counter);
    quads.push_back(Quadruple("GOTO", "", "", ""));
    counter++;
  }
  void ifEnd() {
    // Modify end of if block quadruple to jump to this point
    int endIfQuad = jumpStack.top();
    jumpStack.pop();
    quads[endIfQuad].d = toString(counter);
  }
  void whileConditionStart() {
    // Store the beginning of the expression evaluation to jump to
    jumpStack.push(counter);
  }
  void whileBlockStart() {
    // Get information on the conditional and validate it's a bool
    std::string type = typeStack.top();
    typeStack.pop();
    std::string condition = operandStack.top();
    operandStack.pop();
    if (type != "bool") {
      semanticError("Expected bool on while statement");
    }
    // Generate GOTOF quadruple and store the counter to modify it later
    jumpStack.push(counter);
    quads.push_back(Quadruple("GOTOF", memory_map.Get(condition, "bool"), "", ""));
    counter++;
  }
  void whileEnd() {
    int gotof = jumpStack.top();
    jumpStack.pop();
    int jump = jumpStack.top();
    jumpStack.pop();
    // Go back to where the condition is evaluated
    quads.push_back(Quadruple("GOTO", "", "", toString(jump)));
    counter++;
    // Modify quadruple to jump to when false
    quads[gotof].d = toString(counter);
    stringstream ss;
    ss << "Ending while on " << counter << ", with jump on " << gotof << endl;
    debug(ss.str());
  }
  void doWhileStart() {
    // Push to jump stack the start of the do while block
    jumpStack.push(counter);
  }
  void doWhileEnd() {
    // Get information on the conditional and validate it's a bool
    std::string type = typeStack.top();
    typeStack.pop();
    std::string condition = operandStack.top();
    operandStack.pop();
    if (type != "bool") {
      semanticError("Expected bool on do while statement");
    }
    // Generate GOTOV quadruple
    int jump = jumpStack.top();
    jumpStack.pop();
    quads.push_back(Quadruple("GOTOV", memory_map.Get(condition, "bool"), "", toString(jump)));
    counter++;
  }
  void forConditionStart() {
    // Push to jump stack the beginning of the condition
    jumpStack.push(counter);
  }
  void forConditionEnd() {
    // Get information on the conditional and validate it's a bool
    std::string type = typeStack.top();
    typeStack.pop();
    std::string condition = operandStack.top();
    operandStack.pop();
    if (type != "bool") {
      semanticError("Expected bool on do while statement");
    }
    // Generate GOTOF quadruple
    jumpStack.push(counter);
    quads.push_back(Quadruple("GOTOF", memory_map.Get(condition, "bool"), "", ""));
    counter++;
    // Jump to where the block starts (skip third element)
    jumpStack.push(counter);
    quads.push_back(Quadruple("GOTO", "", "", condition));
    counter++;
    // Store the start of the third element of the for
    jumpStack.push(counter);
  }
  void forStart() {
    // Pop elements from the jump stack
    int jump4 = jumpStack.top();
    jumpStack.pop();
    int jump3 = jumpStack.top();
    jumpStack.pop();
    int jump2 = jumpStack.top();
    jumpStack.pop();
    int jump1 = jumpStack.top();
    jumpStack.pop();
    // Jump back to where the condition evaluation starts
    quads.push_back(Quadruple("GOTO", "", "", toString(jump1)));
    counter++;
    // Jump here when the condition is evaluated to true (code inside for)
    quads[jump3].d = toString(counter);
    // Put unused elements back into the stack
    jumpStack.push(jump2);
    jumpStack.push(jump4);
  }
  void forEnd() {
    // Jump back to the third element of the for
    int jump2 = jumpStack.top();
    jumpStack.pop();
    quads.push_back(Quadruple("GOTO", "", "", toString(jump2)));
    counter++;
    // Jump here when the condition is false and we exit the loop
    int jump1 = jumpStack.top();
    jumpStack.pop();
    quads[jump1].d = toString(counter);
  }
  void assignEnd() {
    std::string expression = operandStack.top();
    operandStack.pop();
    std::string expressionType = typeStack.top();
    typeStack.top();
    std::string assignable = operandStack.top();
    std::string assignableType = typeStack.top();
    if (expressionType != assignableType) {
      semanticError("Expected " + assignableType + " found " + expressionType);
    }
    quads.push_back(Quadruple("=", memory_map.Get(expression, expressionType), "", memory_map.Get(assignable, assignableType)));
    counter++;
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
    MemoryMap::VariableLifetime scope = MemoryMap::VT_Global; 
    if (inFunction) {
      scope = MemoryMap::VT_Local;
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
    memory_map.DeclareVariable(scope, lastType, lastIdName);
    stringstream ss;
    ss << "var declared: " << lastIdName << endl;
    debug(ss.str());
  }
  // read after reading the signature of a function
  void declareFunc() {
    if (inClass) {
      lastFuncName = lastClassName + "." + lastFuncName;
    }

    if (functions.find(lastFuncName) != functions.end()) {
      semanticError("Redefinition of function " + lastFuncName);
    }

    Function fn = Function(lastFuncName, lastReturnType, params, counter);
    functions[lastFuncName] = fn;
    memory_map.DeclareGlobal(lastReturnType, "@" + lastFuncName);

    inFunction = true;
    for(auto& param: fn.params) {
      lastIdName = param.paramName;
      lastType = param.paramType;
      declareVar();
    } 

    for (Param param : params) {
      quads.emplace_back("POP", memory_map.Get(param.paramName, param.paramType), "", "");
      counter++;
    }

    params.clear();

    stringstream ss;
    ss << "function declared: " << lastFuncName << endl;
    debug(ss.str());

    if (lastFuncName == "main") {
      quads[0].d = toString(counter);
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
    stringstream ss;
    ss << "class declared: " << lastIdName << endl;
    debug(ss.str());
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

    stringstream ss;
    ss << "function call init: " << lastIdName << endl;
    debug(ss.str());

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

    stringstream ss;
    ss << "found assignable: " << lastIdName << endl;
    debug(ss.str());

    typeStack.push(getSymbolType(lastIdName));
    pushOperand(lastIdName, getSymbolType(lastIdName));
  }

  // called after reading the right hand expression of an assignment
  void assign() { 
    stringstream ss;
    ss << "found assignment" << endl;
    debug(ss.str());
    string typeAssigned = typeStack.top();
    typeStack.pop(); 
    string varType = typeStack.top();
    typeStack.pop();
    if (varType != typeAssigned) {
      semanticError("Expected " + varType + " found " + typeAssigned);
    }

    assignEnd();
  }
  // called after calling a function
  // foo(12, "abc")
  // ~~~~~~~~~~~~~^~~
  void fnCall() { 
    string fnName = fnCallStack.top();
    stringstream ss;
    ss << "function call ended: " << fnName << endl;
    debug(ss.str());
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

      quads.emplace_back("PUSH", memory_map.Get(operandStack.top(), paramType), "", "");
      counter++;
      operandStack.pop();
    }
    
    string ct = getConstantVariable("int", toString(counter+3));

    quads.emplace_back("PUSH", memory_map.Get(ct, "int"), "", "");
    counter++;

    quads.emplace_back("GOTO", "", "", toString(fn.location));
    counter++;

    typeStack.push(fn.returnType);
    if (fn.returnType != "void") {
      string tmp = getTemporalVariable(fn.returnType);
      quads.emplace_back("=", memory_map.Get(tmp, "int"), "", memory_map.Get("@" + fnName, fn.returnType));
      counter++;
      operandStack.push(tmp);
    }
  }
  // called after reading a literal
  void literal(string type, string value) {
    stringstream ss;
    ss << "found literal: " << type << endl;
    debug(ss.str());
    typeStack.push(type);
    pushConstant(type, value);
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
    stringstream ss;
    ss << "found array access" << type << endl;
    debug(ss.str());
  }
  // called after reading the last expression of an operation
  void operation(int operatorPriority) {
    popOperator(operatorPriority);
  }
  // called after reading an identifier used as an expression
  void varExpr() {
    stringstream ss;
    ss << "found var expr: " << lastIdName << endl;
    debug(ss.str());
    typeStack.push(getSymbolType(lastIdName));
    pushOperand(lastIdName, getSymbolType(lastIdName));
  }
  // called after reading a return expression
  void returnExpr() {
    string retType = typeStack.top();
    typeStack.pop();
    string fnName = (inClass ? lastClassName + "." : "") + lastFuncName;
    if (functions[lastFuncName].returnType != retType) {
      semanticError("function " + fnName + " expects " + functions[lastFuncName].returnType + " as return type; found " + retType);
    }

    if (retType != "void") {
      quads.emplace_back("=", memory_map.Get("@" + lastFuncName, functions[lastFuncName].returnType), "", memory_map.Get(operandStack.top(), functions[lastFuncName].returnType));
      counter++;
      operandStack.pop();
    }

    string tmp = memory_map.Get(getTemporalVariable(retType), retType);
    quads.emplace_back("RETURN", "", "", "");
    counter++;
  }
  // called after reading a return void expression
  void returnVoid() {
    typeStack.push("void");
    returnExpr();
  }
  // called after reading an argument in a function call
  void argument() {
    fnCallNumArgsStack.top()++;
  }
  // called after reading an operator
  void _operator() {
    pushOperator(lastOperator);
  }
  // called after reading an open parenthesis enclosing an expression
  void openParenthesis() {
    pushParenthesis();
  }
  // called after reading an open parenthesis enclosing an expression
  void closeParenthesis() {
    popParenthesis();
  }
  // called after reading everything
  void end() {
    if (functions.count("main") == 0) {
      semanticError("No main function found.");
    }
    cout << " === QUADRUPLES === " << endl;
    print();
  }
  void print() {
    for (int i = 0; i < quads.size(); i++) {
      std::cout << i << ": [ " << quads[i].a << ", " << quads[i].b << ", " << quads[i].c << ", " << quads[i].d << "]" << std::endl; 
    }
  }
  void begin() {
    types.insert("int");
    types.insert("float");
    types.insert("char");
    types.insert("bool");
    types.insert("string");
    
    vector<Param> params{ Param("arg", "string") };
    functions["print"] = Function("print", "void", params);
    functions["read"] = Function("read", "string", vector<Param>());

    quads.emplace_back("GOTO", "", "", "");
    counter++;
  }
private:
  std::string getTemporalVariable(string type) {
    std::stringstream ss;
    ss << "*t" << tempCounter;
    tempCounter++;
    memory_map.DeclareTemporary(type, ss.str());
    return ss.str();
  }
  std::string getConstantVariable(string type, string value) {
    counter++;
    std::stringstream ss;
    ss << "$c" << constCounter;
    constCounter++;
    memory_map.DeclareConstant(type, ss.str());
    quads.emplace_back("CONSTANT", type, value, memory_map.Get(ss.str(), type));
    return ss.str();
  }
  int getOperPriority(std::string oper) {
    if (oper == "!") return 0;
    if (oper == "*") return 1;
    if (oper == "/") return 1;
    if (oper == "%") return 1;
    if (oper == "+") return 2;
    if (oper == "-") return 2;
    if (oper == "<") return 3;
    if (oper == "<=") return 3;
    if (oper == ">=") return 3;
    if (oper == ">") return 3;
    if (oper == "==") return 4;
    if (oper == "!=") return 4;
    if (oper == "&&") return 5;
    if (oper == "||") return 6;
    assert(false);
    return 0;
  }
  void semanticError(std::string err) {
    std::cout << "Semantic error: " << err << std::endl;
    exit(1);
  }
  std::string toString(int num) {
    std::stringstream ss;
    ss << num;
    return ss.str();
  }
};
