#ifndef CLASS_H_
#define CLASS_H_

#include "symbol_table.h"

struct Class {
 public:
  string name, parentClass;
  SymbolTable classSymbolTable;
  Class(string name): name(name), parentClass("") {}
  Class() {}
};

#endif // CLASS_H_
