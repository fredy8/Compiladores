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
  vector<Quadruple> quads;
  stack<string> typeStack;
  stack<string> operandStack;
  stack<string> operatorStack;
  stack<int> jumpStack;
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
  // true if you want to declare a temporary variable
  bool isTemporary = false;
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
  // this stack goes along the previous fnCallStack, and maintains
  // a boolean value indicating whether it's a method call or not
  stack<bool> methodCallStack;
  // keeps the name of the object the method was called on
  stack<string> objectCallStack;
  // stores the name of the last class
  string lastObjectType;
  // stores whether we are declaring an object
  bool isObjectType;
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
  void pushOperand(string operand, string type) {
    operandStack.push(operand);
    typeStack.push(type);
  }
  void pushConstant(string type, string value) {
    operandStack.push(getConstantVariable(type, value));
    typeStack.push(type);
  }
  void pushOperator(string oper) {
    operatorStack.push(oper);
  }
  void popOperator(int priority) {
    // Check whether the next operator to evaluate has the expected priority
    if (operatorStack.empty()) {
      return;
    }
    string oper = operatorStack.top();
    int operPriority = getOperPriority(oper);
    if (operPriority != priority) {
      return;
    }
    operatorStack.pop();

    // Pop operands and types from their stacks
    string type1 = "", operand1 = "", type2 = "", operand2 = "";
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
    string resultType = Cube::getOperationType(oper, type1, type2);
    if (resultType == "") {
      semanticError("Invalid operation: " + type1 + " " + oper + " " + type2);
    }

    // Push new quadruple and result to stacks
    string result = getTemporalVariable(resultType);
    string b = memory_map.Get(operand1, type1);
    string c = (operand2 == "" ? "" : memory_map.Get(operand2, type2));
    string d = memory_map.Get(result, resultType);
    pushOperand(result, resultType);
    addQuad(oper, b, c, d);
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
    string type = typeStack.top();
    typeStack.pop();
    string condition = operandStack.top();
    operandStack.pop();
    if (type != "bool") {
      semanticError("Expected bool on if statement");
    }
    // Generate GOTOF quadruple and store the counter to modify it later
    jumpStack.push(counter);
    addQuad("GOTOF", memory_map.Get(condition, "bool"), "", "");
  }
  void ifBlockEnd() {
    // Modify if statement quadruple to jump to the end of block
    int ifQuad = jumpStack.top();
    jumpStack.pop();
    quads[ifQuad].d = toString(counter + 1);
    // Add GOTO jump to the end of the if statement and store the counter
    jumpStack.push(counter);
    addQuad("GOTO", "", "", "");
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
    string type = typeStack.top();
    typeStack.pop();
    string condition = operandStack.top();
    operandStack.pop();
    if (type != "bool") {
      semanticError("Expected bool on while statement");
    }
    // Generate GOTOF quadruple and store the counter to modify it later
    jumpStack.push(counter);
    addQuad("GOTOF", memory_map.Get(condition, "bool"), "", "");
  }
  void whileEnd() {
    int gotof = jumpStack.top();
    jumpStack.pop();
    int jump = jumpStack.top();
    jumpStack.pop();
    // Go back to where the condition is evaluated
    addQuad("GOTO", "", "", toString(jump));
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
    string type = typeStack.top();
    typeStack.pop();
    string condition = operandStack.top();
    operandStack.pop();
    if (type != "bool") {
      semanticError("Expected bool on do while statement");
    }
    // Generate GOTOV quadruple
    int jump = jumpStack.top();
    jumpStack.pop();
    addQuad("GOTOV", memory_map.Get(condition, "bool"), "", toString(jump));
  }
  void forConditionStart() {
    // Push to jump stack the beginning of the condition
    jumpStack.push(counter);
  }
  void forConditionEnd() {
    // Get information on the conditional and validate it's a bool
    string type = typeStack.top();
    typeStack.pop();
    string condition = operandStack.top();
    operandStack.pop();
    if (type != "bool") {
      semanticError("Expected bool on do while statement");
    }
    // Generate GOTOF quadruple
    jumpStack.push(counter);
    addQuad("GOTOF", memory_map.Get(condition, "bool"), "", "");
    // Jump to where the block starts (skip third element)
    jumpStack.push(counter);
    addQuad("GOTO", "", "", condition);
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
    addQuad("GOTO", "", "", toString(jump1));
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
    addQuad("GOTO", "", "", toString(jump2));
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
    string varName = lastIdName;
    if (inFunction) {
      scope = MemoryMap::VT_Local;
      table = &functions[lastFuncName].localSymbolTable;

      if (table->find(varName) != table->end()) {
        semanticError("Redeclaration of " + varName);
      }
    } else if (inClass) {
      declareObjectAttribute();
      return;
    }
    if (isTemporary) {
      scope = MemoryMap::VT_Temporary;
    }

    if (globalScopeSymbolTable.find(varName) != globalScopeSymbolTable.end()) {
      semanticError("Redeclaration of " + varName);
    }
    
    stringstream ss;

    if (isObjectType && typeIsArray) {
      semanticError("You can't declare an array of a custom class.");
    } else if (isObjectType) {
      isObjectType = false;
      table->operator[](varName) = lastObjectType;
      declareObject(lastObjectType, varName + ".");
      ss << "object ";
    } else if (typeIsArray) {
      ss << "array ";
      table->operator[](varName) = lastType + "[" + toString(lastArraySize) + "]";
      memory_map.DeclareArrayVariable(scope, lastType, varName, lastArraySize);
    } else {
      table->operator[](varName) = lastType;
      memory_map.DeclareVariable(scope, lastType, varName);
    }

    ss << "var declared: " << varName << endl;
    debug(ss.str());
  }
  // it is used to add attributes to a class
  void declareObjectAttribute() {
    SymbolTable* table = &classes[lastClassName].classSymbolTable;
    if (table->find(lastIdName) != table->end()) {
      semanticError("Redeclaration of attribute " + lastIdName + " in class " + lastClassName);
    }
    stringstream ss;
    if (typeIsArray) {
      ss << "array ";
      table->operator[](lastIdName) = lastType + "[" + toString(lastArraySize) + "]";
    } else {
      table->operator[](lastIdName) = lastType;
    }

    ss << "attribute declared: " << lastIdName << endl;
    debug(ss.str());
  }
  // it is used to get the memory for an instance of a custom class 
  void declareObject(string className, string objectPrefix) {
    bool tmpInClass = inClass;
    inClass = false;
    SymbolTable table = classes[className].classSymbolTable;
    for (auto const &attribute : table) {
      string attrName = attribute.first;
      string attrType = attribute.second;
      typeIsArray = false;
      isObjectType = false;
      if (isTypeArray(attrType)) {
        string type; int size;
        splitArrayType(attrType, type, size);
        lastType = type;
        lastArraySize = size;
        typeIsArray = true;
      } else if (isTypeClass(attrType)) {
        lastObjectType = attrType;
        isObjectType = true;
      } else {
        lastType = attrType;
      }
      lastIdName = objectPrefix + attrName;
      declareVar();
    }
    inClass = tmpInClass;
  }
  // Declares a global object for method calling
  void declareGlobalObject(string className, string globalName) {
    bool tmpInFunction = inFunction;
    inFunction = false;
    declareObject(className, globalName + ".");
    inFunction = tmpInFunction;
  }
  // Declares a temporary object for function return values
  void declareTemporaryObject(string className, string temporaryName) {
    bool tmpIsTemporary = isTemporary;
    isTemporary = true;
    declareObject(className, temporaryName + ".");
    isTemporary = tmpIsTemporary;
  }
  // read after reading the signature of a function
  void declareFunc() {
    addQuad("SCOPE", "PUSH", "", "");

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
      if (isTypeClass(lastReturnType)) {
        declareGlobalObject(lastReturnType, "@" + lastFuncName);
      } else if (isTypeArray(lastReturnType)) {
        string type; int size;
        splitArrayType(lastReturnType, type, size);
        memory_map.DeclareGlobalArray(type, "@" + lastFuncName, size);
      } else {
        memory_map.DeclareGlobal(lastReturnType, "@" + lastFuncName);
      }
    }

    inFunction = true;

    // Declare a global object to pass the information
    // Make a local copy of it
    if (inClass) {
      declareGlobalObject(lastClassName, "@@" + lastFuncName);
      declareObject(lastClassName, "");
      popObject(lastClassName, "@@" + lastFuncName);
    }

    for(auto& param: fn.params) {
      lastIdName = param.paramName;
      lastType = param.paramType;
      typeIsArray = false;
      if (isTypeArray(lastType)) {
        splitArrayType(lastType, lastType, lastArraySize);
        typeIsArray = true;
      }
      declareVar();
    }

    for (Param param : params) {
      if (isTypeClass(param.paramType)) {
        rPopObject(param.paramName, param.paramType);
      } else if (isTypeArray(param.paramType)) {
        popArray(param.paramName, param.paramType);
      } else {
        addQuad("POP", memory_map.Get(param.paramName, param.paramType), "", "");
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
      addQuad("POP", toString(baseMemory + size - 1 - i), "", "");
    }
  }

  // Copies all of the attributes of an object to local memory, from its global variable
  void popObject(string className, string globalVariable) {
    assignObject("", globalVariable + ".", className);
  }

  // When returning a method, copy the modified object into the global variable
  void pushObjectEnd(string globalName, string className) {
    assignObject(globalName + ".", "", className);
  }

  // Pops an object from the stack to receive it as a parameter
  void rPopObject(string objectName, string className) {
    SymbolTable table = classes[className].classSymbolTable;
    for (auto attribute = table.rbegin(); attribute != table.rend(); attribute++) {
      string attrName = objectName + "." + attribute->first;
      string attrType = attribute->second;
      if (isTypeClass(attrType)) {
        rPopObject(attrName, attrType);
      } else if (isTypeArray(attrType)) {
        popArray(attrName, attrType);
      } else {
        addQuad("POP", memory_map.Get(attrName, attrType), "", "");
      }
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
      operandStack.pop();
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
    methodCallStack.push(isObjFnCall);
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

  // Returns whether this type is a custom class
  bool isTypeClass(string type) {
    return classes.find(type) != classes.end();
  }

  // called after reading the function name of a method call
  void objFnCallInit() {
    isObjFnCall = true;
    // For some reason, this is already inside the stack
    // typeStack.push(getSymbolType(lastIdName));
    objectCallStack.push(lastIdName);
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

    string expression = operandStack.top();
    operandStack.pop();
    string expressionType = typeStack.top();
    typeStack.pop();
    string assignable = operandStack.top();
    operandStack.pop();
    string assignableType = typeStack.top();
    typeStack.pop();
    //cout << " = " << expression << " " << expressionType << endl;
    //cout << " = " << assignable << " " << assignableType << endl;
    if (expressionType != assignableType) {
      semanticError("Expected " + assignableType + " found " + expressionType);
    }
    if (isTypeClass(assignableType)) {
      assignObject(assignable + ".", expression + ".", assignableType);
    } else if (isTypeArray(assignableType)) {
      assignArray(assignable, expression, assignableType);
    } else {
      addQuad("=", memory_map.Get(expression, expressionType), "", memory_map.Get(assignable, assignableType));
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
      addQuad("=", toString(baseMemory2 + i), "", toString(baseMemory1 + i));
    }
  }
  // Used to copy objects
  void assignObject(string objectPrefix1, string objectPrefix2, string className) {
    SymbolTable table = classes[className].classSymbolTable;
    for (auto const &attribute : table) {
      string attrName1 = objectPrefix1 + attribute.first;
      string attrName2 = objectPrefix2 + attribute.first;
      string attrType = attribute.second;
      if (isTypeClass(attrType)) {
        assignObject(attrName1 + ".", attrName2 + ".", attrType);
      } else if (isTypeArray(attrType)) {
        assignArray(attrName1, attrName2, attrType);
      } else {
        addQuad("=", memory_map.Get(attrName2, attrType), "", memory_map.Get(attrName1, attrType));
      }
    }
  }
  // called after calling a function
  // foo(12, "abc")
  // ~~~~~~~~~~~~~^~~
  void fnCall() { 
    string fnName = fnCallStack.top();
    bool isMethodCall = methodCallStack.top();
    string objectName = "";
    if (isMethodCall) {
      objectName = objectCallStack.top();
      objectCallStack.pop();
    }
    stringstream ss;
    ss << "function call ended: " << fnName << endl;
    debug(ss.str());
    fnCallStack.pop();
    methodCallStack.pop();
    int numArgs = fnCallNumArgsStack.top();
    fnCallNumArgsStack.pop();

    // Copy the object to the global variable
    if (isMethodCall) {
      pushObject(objectName, "@@" + fnName, getSymbolType(objectName));
    }

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
      addQuad("PUSH", memory_map.Get(ct, "int"), "", "");
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

      if (isTypeClass(paramType)) {
        rPushObject(arg, paramType);
      } else if (isTypeArray(paramType)) {
        pushArray(arg, paramType);
      } else {
        addQuad("PUSH", memory_map.Get(arg, paramType), "", "");
      }
    }

    if (fnName == "read") {
      addQuad("READ", memory_map.Get("@" + fnName, fn.returnType), "", "");
    } else if (fnName == "print") {
      addQuad("PRINT", "", "", "");
    } else if (fnName == "itos") {
      addQuad("ITOS", memory_map.Get("@" + fnName, fn.returnType), "", "");
    } else if (fnName == "strcat") {
      addQuad("STRCAT", memory_map.Get("@" + fnName, fn.returnType), "", "");
    } else {
      // goto function
      addQuad("GOTO", "", "", toString(fn.location));
    }

    // Get object from global variable
    if (isMethodCall) {
      popObjectEnd(objectName, "@@" + fnName, getSymbolType(objectName));
    }

    if (fn.returnType != "void") {
      string tmp;
      if (isTypeClass(fn.returnType)) {
        tmp = getTemporalObject(fn.returnType);
        assignObject(tmp + ".", "@" + fnName + ".", fn.returnType);
      } else if (isTypeArray(fn.returnType)) {
        string type; int size;
        splitArrayType(fn.returnType, type, size);
        tmp = getTemporalArray(type, size);
        assignArray(tmp, "@" + fnName, fn.returnType);
      } else {
        tmp = getTemporalVariable(fn.returnType);
        addQuad("=", memory_map.Get("@" + fnName, fn.returnType), "", memory_map.Get(tmp, fn.returnType));
      }
      operandStack.push(tmp);
      typeStack.push(fn.returnType);
    } else {
      operandStack.push("");
      typeStack.push("void");
    }
  }
  // Pushes each element of the array separately into the runtime stack
  void pushArray(string arrayName, string arrayType) {
    string type;
    int size;
    splitArrayType(arrayType, type, size);
    int baseMemory = atoi(memory_map.Get(arrayName, type).c_str());
    for (int i = 0; i < size; i++) {
      addQuad("PUSH", toString(baseMemory + i), "", "");
    }
  }
  // Pushes the object to a global variable to be accessed by the method
  void pushObject(string objectName, string globalName, string className) {
    assignObject(globalName + ".", objectName + ".", className);
  }
  // After making a method call, copy the modified version of the object
  void popObjectEnd(string objectName, string globalName, string className) {
    assignObject(objectName + ".", globalName + ".", className);
  }
  // pushes object to stack to pass it as parameter
  void rPushObject(string objectName, string className) {
    SymbolTable table = classes[className].classSymbolTable;
    for (auto const &attribute : table) {
      string attrName = objectName + "." + attribute.first;
      string attrType = attribute.second;
      if (isTypeClass(attrType)) {
        rPushObject(attrName, attrType);
      } else if (isTypeArray(attrType)) {
        pushArray(attrName, attrType);
      } else {
        addQuad("PUSH", memory_map.Get(attrName, attrType), "", "");
      }
    }
  }
  // Gets how many pushes it will need for this class
  int getObjectSize(string className) {
    SymbolTable table = classes[className].classSymbolTable;
    int s = 0;
    for (auto const &attribute : table) {
      string attrType = attribute.second;
      if (isTypeClass(attrType)) {
        s += getObjectSize(attrType);
      } else if (isTypeArray(attrType)) {
        string type; int size;
        splitArrayType(attrType, type, size);
        s += size;
      } else {
        s++;
      }
    }
    return s;
  }
  // called after reading a literal
  void literal(string type, string value) {
    stringstream ss;
    ss << "found literal: " << type << " *** " << value << endl;
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
    addQuad("VER", indexMemory, toString(arraySize), "");
    // Store array size to add it to the index
    string ct = getConstantVariable("int", arrayMemory);
    string ctMemory = memory_map.Get(ct, "int");
    // Add them to get the memory for the array cell
    string cellVariable = getTemporalVariable("int");
    string cellMemory = memory_map.Get(cellVariable, "int");
    addQuad("+", ctMemory, indexMemory, cellMemory);
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
    string functionReturnType = functions[lastFuncName].returnType;
    if (functionReturnType != retType) {
      semanticError("function " + lastFuncName + " expects " + functionReturnType + " as return type; found " + retType);
    }

    if (retType != "void") {
      if (isTypeClass(functionReturnType)) {
        assignObject("@" + lastFuncName + ".", operandStack.top() + ".", functionReturnType);
        operandStack.pop();
      } else if (isTypeArray(functionReturnType)) {
        assignArray("@" + lastFuncName, operandStack.top(), functionReturnType);
        operandStack.pop();
      } else {
        addQuad("=", memory_map.Get(operandStack.top(), functionReturnType), "", memory_map.Get("@" + lastFuncName, functionReturnType));
        operandStack.pop();
      }
    }

    // If its a method, push back all the object
    // We have to first pop the return variable, for it to be at the top of the stack at the end
    if (inClass) {
      pushObjectEnd("@@" + lastFuncName, lastClassName);
    }

    addQuad("SCOPE", "POP", toString(memory_map.kLocalStart), toString(memory_map.kConstantStart - 1));
    addQuad("RETURN", "", "", "");
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
      cout << i << ": [ " << quads[i].a << ", " << quads[i].b << ", " << quads[i].c << ", " << quads[i].d << "]" << endl; 
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

    addQuad("GOTO", "", "", "");
  }
private:
  void addQuad(string a, string b, string c, string d) {
    quads.emplace_back(a, b, c, d);
    cout << "[" << a << ", " << b << ", " << c << ", " << d << "]" << endl;
    counter++;
  }
  string getTemporalVariable(string type) {
    stringstream ss;
    ss << "*t" << tempCounter;
    tempCounter++;
    memory_map.DeclareTemporary(type, ss.str());
    return ss.str();
  }
  string getConstantVariable(string type, string value) {
    stringstream ss;
    ss << "$c" << constCounter;
    constCounter++;
    memory_map.DeclareConstant(type, ss.str());
    addQuad("CONSTANT", type, value, memory_map.Get(ss.str(), type));
    return ss.str();
  }
  string getTemporalArray(string type, int size) {
    stringstream ss;
    ss << "*t" << tempCounter;
    tempCounter++;
    memory_map.DeclareTemporaryArray(type, ss.str(), size);
    return ss.str();
  }
  string getTemporalObject(string className) {
    stringstream ss;
    ss << "*t" << tempCounter;
    tempCounter++;
    string temporalObject = ss.str();
    declareTemporaryObject(className, temporalObject);
    return ss.str();
  }
  int getOperPriority(string oper) {
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
  void semanticError(string err) {
    cout << "Semantic error: " << err << endl;
    exit(1);
  }
  string toString(int num) {
    stringstream ss;
    ss << num;
    return ss.str();
  }
};
