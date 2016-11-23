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
  // true if the return type is an array
  bool returnTypeIsArray;
  // the most recent return size of array read
  int lastReturnArraySize;
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
  // keeps track of array variable names for nested access
  stack<string> arrayIdStack;
public:
  void printOperandStack() {
    stack<string> copy = operandStack;
    stack<string> copy2 = typeStack;
    cout << "OPERAND STACK" << endl;
    while(!copy.empty() || !copy2.empty()) {
      if (!copy.empty()) {
        cout << copy.top();
        copy.pop();
      }
      if (!copy2.empty()) {
        cout << "\t" << copy2.top();
        copy2.pop();
      }
      cout << endl;
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
        if (cmd == "o") { printOperandStack(); break; }
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
    pushOperand(result, resultType);
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
  // Called after reading a parameter from a function
  void declareParam() {
    if (typeIsArray) {
      lastType += "[" + toString(lastArraySize) + "]";
    }
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
      cout << "array ";
      table->operator[](lastIdName) = lastType + "[" + toString(lastArraySize) + "]";
      memory_map.DeclareArrayVariable(scope, lastType, lastIdName, lastArraySize);
    } else {
      table->operator[](lastIdName) = lastType;
      memory_map.DeclareVariable(scope, lastType, lastIdName);
    }

    stringstream ss;
    ss << "var declared: " << lastIdName << endl;
    debug(ss.str());
  }
  // read after reading the signature of a function
  void declareFunc() {
    quads.emplace_back("SCOPE", "PUSH", "", "");
    counter++;

    if (inClass) {
      lastFuncName = lastClassName + "." + lastFuncName;
    }

    if (functions.find(lastFuncName) != functions.end()) {
      semanticError("Redefinition of function " + lastFuncName);
    }

    if (returnTypeIsArray) {
      lastReturnType += "[" + toString(lastReturnArraySize) + "]";
    }

    Function fn = Function(lastFuncName, lastReturnType, params, counter-1);
    functions[lastFuncName] = fn;
    if (lastReturnType != "void") {
      if (isTypeArray(lastReturnType)) {
        string type; int size;
        splitArrayType(lastReturnType, type, size);
        memory_map.DeclareGlobalArray(type, "@" + lastFuncName, size);
      } else {
        memory_map.DeclareGlobal(lastReturnType, "@" + lastFuncName);
      }
    }

    inFunction = true;
    for(auto& param: fn.params) {
      lastIdName = param.paramName;
      lastType = param.paramType;
      if (isTypeArray(lastType)) {
        splitArrayType(lastType, lastType, lastArraySize);
        typeIsArray = true;
      }
      declareVar();
    }

    for (Param param : params) {
      if (isTypeArray(param.paramType)) {
        popArray(param.paramName, param.paramType);
      } else {
        quads.emplace_back("POP", memory_map.Get(param.paramName, param.paramType), "", "");
        counter++;
      }
    }

    params.clear();

    stringstream ss;
    ss << "function declared: " << lastFuncName << endl;
    debug(ss.str());

    if (lastFuncName == "main") {
      quads[0].d = toString(counter);
    }
  }
  // Pops each of the elements of the array for a function declaration
  void popArray(string arrayName, string arrayType) {
    string type;
    int size;
    splitArrayType(arrayType, type, size);
    int baseMemory = atoi(memory_map.Get(arrayName, type).c_str());
    for (int i = 0; i < size; i++) {
      quads.emplace_back("POP", toString(baseMemory + size - 1 - i), "", "");
      counter++;
    }
  }

  // check that an array size supplied is valid
  // called after reading an array size
  void validateArraySize() {
    if (lastArraySize <= 0) {
      semanticError("Expected array size greater than 0.");
    }
  }

  // check that an array size supplied is valid
  // called after reading a return array size
  void validateReturnArraySize() {
    if (lastReturnArraySize <= 0) {
      semanticError("Expected return array size greater than 0.");
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

  // returns whether the variable is an array
  bool isArraySymbol(string varName) {
    return isTypeArray(getSymbolType(varName));
  }

  // returns the size of an array
  int getArraySize(string varName) {
    string type;
    int size;
    splitArrayType(getSymbolType(varName), type, size);
    return size;
  }

  // return the type of an array
  string getArrayType(string varName) {
    string type;
    int size;
    splitArrayType(getSymbolType(varName), type, size);
    return type;
  }

  // Returns whether this type represents an array
  bool isTypeArray(string type) {
    return type.find('[') != string::npos;
  }

  // Splits an array type into its basic type and size
  void splitArrayType(string arrayType, string &type, int &size) {
    int bracket = arrayType.find('['), l = arrayType.length();
    string number = arrayType.substr(bracket + 1, l - bracket - 2);
    type = arrayType.substr(0, bracket);
    size = atoi(number.c_str());
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

    pushOperand(lastIdName, getSymbolType(lastIdName));
  }

  // called after reading the right hand expression of an assignment
  void assign() { 
    stringstream ss;
    ss << "found assignment" << endl;
    debug(ss.str());

    std::string expression = operandStack.top();
    operandStack.pop();
    std::string expressionType = typeStack.top();
    typeStack.pop();
    std::string assignable = operandStack.top();
    operandStack.pop();
    std::string assignableType = typeStack.top();
    typeStack.pop();
    if (expressionType != assignableType) {
      semanticError("Expected " + assignableType + " found " + expressionType);
    }
    if (isTypeArray(assignableType)) {
      assignArray(assignable, expression, assignableType);
    } else {
      quads.push_back(Quadruple("=", memory_map.Get(expression, expressionType), "", memory_map.Get(assignable, assignableType)));
      counter++;
    }
  }
  // Used to copy arrays
  void assignArray(string arrayName1, string arrayName2, string arrayType) {
    string type;
    int size;
    splitArrayType(arrayType, type, size);
    int baseMemory1 = atoi(memory_map.Get(arrayName1, type).c_str());
    int baseMemory2 = atoi(memory_map.Get(arrayName2, type).c_str());
    for (int i = 0; i < size; i++) {
      quads.emplace_back("=", toString(baseMemory2 + i), "", toString(baseMemory1 + i));
      counter++;
    }
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
    int numPushes = 0;
    for (Param param : params) {
      if (isTypeArray(param.paramType)) {
        string type; int size;
        splitArrayType(param.paramType, type, size);
        numPushes += size;
      } else {
        numPushes++;
      }
    }

    if (fnName != "read" && fnName != "print" && fnName != "strcat" && fnName != "itos") {
      // push return address
      string ct = getConstantVariable("int", toString(counter+3+numPushes));
      quads.emplace_back("PUSH", memory_map.Get(ct, "int"), "", "");
      counter++;
    }

    // check fn args types and push them to the stack
    for (int i = 0; i < numArgs; i++) {
      string argType = typeStack.top();
      typeStack.pop();
      string paramType = params[params.size() - 1 - i].paramType;
      if (argType != paramType) {
        stringstream ss;
        ss << "function " << fnName << " expects " << paramType << " for its parameter #" << (params.size()-i) << "; found " << argType;
        semanticError(ss.str());
      }
      string arg = operandStack.top();
      operandStack.pop();

      if (isTypeArray(paramType)) {
        pushArray(arg, paramType);
      } else {
        quads.emplace_back("PUSH", memory_map.Get(arg, paramType), "", "");
        counter++;
      }
    }

    if (fnName == "read") {
      quads.emplace_back("READ", memory_map.Get("@" + fnName, fn.returnType), "", "");
      counter++;
    } else if (fnName == "print") {
      quads.emplace_back("PRINT", "", "", "");
      counter++;
    } else if (fnName == "itos") {
      quads.emplace_back("ITOS", memory_map.Get("@" + fnName, fn.returnType), "", "");
      counter++;
    } else if (fnName == "strcat") {
      quads.emplace_back("STRCAT", memory_map.Get("@" + fnName, fn.returnType), "", "");
      counter++;
    } else {
      // goto function
      quads.emplace_back("GOTO", "", "", toString(fn.location));
      counter++;
    }

    typeStack.push(fn.returnType);
    if (fn.returnType != "void") {
      string tmp;
      if (isTypeArray(fn.returnType)) {
        string type; int size;
        splitArrayType(fn.returnType, type, size);
        tmp = getTemporalArray(type, size);
        assignArray(tmp, "@" + fnName, fn.returnType);
      } else {
        tmp = getTemporalVariable(fn.returnType); // alberto
        quads.emplace_back("=", memory_map.Get("@" + fnName, fn.returnType), "", memory_map.Get(tmp, fn.returnType));
        counter++;
      }
      operandStack.push(tmp);
      typeStack.push(fn.returnType);
    }
  }
  // Pushes each element of the array separately into the runtime stack
  void pushArray(string arrayName, string arrayType) {
    string type;
    int size;
    splitArrayType(arrayType, type, size);
    int baseMemory = atoi(memory_map.Get(arrayName, type).c_str());
    for (int i = 0; i < size; i++) {
      quads.emplace_back("PUSH", toString(baseMemory + i), "", "");
      counter++;
    }

  }
  // called after reading a literal
  void literal(string type, string value) {
    stringstream ss;
    ss << "found literal: " << type << endl;
    debug(ss.str());
    pushConstant(type, value);
  }
  // called after reading the variable name of an array type when accessing an array
  void initArrAccess() {
    if (!isArraySymbol(lastIdName)) {
      semanticError("Variable is not an array: " + lastIdName);
    }
    arrayIdStack.push(lastIdName);
  }
  // called after reading an array access.
  void arrAccess() {
    string indexType = typeStack.top();
    typeStack.pop(); 
    if (indexType != "int") {
      semanticError("Array subscript must be an int; found " + indexType);
    }

    string index = operandStack.top();
    operandStack.pop();
    string arrayId = arrayIdStack.top();
    arrayIdStack.pop();
    string arrayType = getArrayType(arrayId);
    int arraySize = getArraySize(arrayId);
    string arrayMemory = memory_map.Get(arrayId, arrayType);
    string indexMemory = memory_map.Get(index, "int");

    // Generate quadrule to verify that index is valid
    quads.emplace_back(Quadruple("VER", indexMemory, toString(arraySize), ""));
    counter++;
    // Store array size to add it to the index
    string ct = getConstantVariable("int", arrayMemory);
    string ctMemory = memory_map.Get(ct, "int");
    // Add them to get the memory for the array cell
    string cellVariable = getTemporalVariable("int");
    string cellMemory = memory_map.Get(cellVariable, "int");
    quads.emplace_back(Quadruple("+", ctMemory, indexMemory, cellMemory));
    counter++;
    // Push the result to the operand stack as an indirect access
    arrayType.substr(0, arrayType.find('['));
    pushOperand("&" + cellVariable, arrayType);

    stringstream ss;
    ss << "found array access " << arrayId << "[]: " << arrayType << endl;
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
    string type = getSymbolType(lastIdName);
    if (type == "") {
      semanticError("Use of undeclared variable: " + lastIdName);
    }

    pushOperand(lastIdName, type);
  }
  // called after reading a return expression
  void returnExpr() {
    string retType = typeStack.top();
    typeStack.pop();
    string fnName = (inClass ? lastClassName + "." : "") + lastFuncName;
    string functionReturnType = functions[lastFuncName].returnType;
    if (functionReturnType != retType) {
      semanticError("function " + fnName + " expects " + functionReturnType + " as return type; found " + retType);
    }

    if (retType != "void") {
      if (isTypeArray(functionReturnType)) {
        assignArray("@" + lastFuncName, operandStack.top(), functionReturnType);
        operandStack.pop();
      } else {
        quads.emplace_back("=", memory_map.Get(operandStack.top(), functionReturnType), "", memory_map.Get("@" + lastFuncName, functionReturnType));
        counter++;
        operandStack.pop();
      }
    }

    quads.emplace_back("SCOPE", "POP", toString(memory_map.kLocalStart), toString(memory_map.kConstantStart - 1));
    counter++;
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
    memory_map.DeclareGlobal("string", "@read");
    functions["strcat"] = Function("strcat", "string", vector<Param>{ {"left", "string"}, {"right", "string"} });
    memory_map.DeclareGlobal("string", "@strcat");
    functions["itos"] = Function("itos", "string", vector<Param>{ { "number", "int" } });
    memory_map.DeclareGlobal("string", "@itos");

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
    std::stringstream ss;
    ss << "$c" << constCounter;
    constCounter++;
    memory_map.DeclareConstant(type, ss.str());
    quads.emplace_back("CONSTANT", type, value, memory_map.Get(ss.str(), type));
    counter++;
    return ss.str();
  }
  string getTemporalArray(string type, int size) {
    std::stringstream ss;
    ss << "*t" << tempCounter;
    tempCounter++;
    memory_map.DeclareTemporaryArray(type, ss.str(), size);
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
