#ifndef MEMORY_MAP_H
#define MEMORY_MAP_H

#include <string>
#include <map>
#include <utility>
#include <cassert>

using namespace std;

class MemoryMap {
 public:
  enum VariableLifetime {
    VT_Global,
    VT_Local,
    VT_Constant,
    VT_Temporary
  };
  MemoryMap() {
    address_to_var.assign(1000, "");
    memory_pointers.emplace(VT_Global, AreaPointers(kGlobalStart));
    memory_pointers.emplace(VT_Local, AreaPointers(kLocalStart));
    memory_pointers.emplace(VT_Constant, AreaPointers(kConstantStart));
    memory_pointers.emplace(VT_Temporary, AreaPointers(kTemporaryStart));
  }
  void DeclareVariable(VariableLifetime lifetime, string variable_type, string var_name) {
    auto area_pointers = memory_pointers.find(lifetime)->second;

    if (variable_type == "int")
      address_to_var[area_pointers.next_int++] = var_name;
    if (variable_type == "float")
      address_to_var[area_pointers.next_float++] = var_name;
    if (variable_type == "string")
      address_to_var[area_pointers.next_string++] = var_name;
    if (variable_type == "bool")
      address_to_var[area_pointers.next_bool++] = var_name;
    if (variable_type == "char")
      address_to_var[area_pointers.next_char++] = var_name;
    assert(false);
  }
  int Get(VariableLifetime lifetime, string type, string var_name) {
     int start = kGlobalStart; 
     if (lifetime == VT_Local) start = kLocalStart;
     if (lifetime == VT_Constant) start = kConstantStart;
     if (lifetime == VT_Local) start = kTemporaryStart;

     if (type == "int") start += kIntOffset; 
     if (type == "float") start += kFloatOffset; 
     if (type == "string") start += kStringOffset; 
     if (type == "bool") start += kBoolOffset; 
     if (type == "char") start += kCharOffset; 

     for(int i = start; i < start + 50; i++) {
       if (address_to_var[i] == var_name)
         return i;
     }

     return -1;
  }
  void ResetLocals() {
    memory_pointers.emplace(VT_Local, AreaPointers(kLocalStart));
  }
  void ResetTemporaries() {
    memory_pointers.emplace(VT_Temporary, AreaPointers(kTemporaryStart));
  }
 private:
  vector<string> address_to_var;
  struct AreaPointers {
    AreaPointers(int area_start) {
      next_int = area_start + kIntOffset;
      next_float = area_start + kFloatOffset;
      next_string = area_start + kStringOffset;
      next_bool = area_start + kBoolOffset;
      next_char = area_start + kCharOffset;
    }
    int next_int;
    int next_float;
    int next_string;
    int next_bool;
    int next_char;
  };
  map<VariableLifetime, AreaPointers> memory_pointers;
  static const int kGlobalStart = 0, kLocalStart = 250, kConstantStart = 500, kTemporaryStart = 750;
  static const int kIntOffset = 0, kFloatOffset = 50, kStringOffset = 100, kBoolOffset = 150, kCharOffset = 200;
};

#endif // MEMORY_MAP_H
