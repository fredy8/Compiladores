#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <string>
#include <vector>
#include <map>
#include "symbol_table.h" 

using namespace std;

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
  int location;
  Function(string name, string returnType, vector<Param> params, int location = -1) : params(params), returnType(returnType), name(name), location(location) {}
  Function() {}
};

typedef map<string, Function> FunctionsTable;

#endif // FUNCTION_H_
