#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

using namespace std;
#include <map>

struct SymbolTableData {
  string type;
  int size;
  SymbolTableData() {}
  SymbolTableData(string type, int size = -1) : type(type), size(size) {}
};

typedef map<string, SymbolTableData> SymbolTable;

#endif // SYMBOLTABLE_H_
