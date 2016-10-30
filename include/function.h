#ifndef FUNCTION_H_
#define FUNCTION_H_

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

typedef map<string, Function> FunctionsTable;

#endif // FUNCTION_H_
