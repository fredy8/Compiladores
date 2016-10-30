#ifndef CLASS_H_
#define CLASS_H_

#include "symbol_table.h"

struct Class {
 public:
  string name;
  SymbolTable classSymbolTable;
  Class(string name) {}
  Class() {}
};

#endif // CLASS_H_
