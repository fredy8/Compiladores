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
    address_to_var.assign(kMemSize, "");
    memory_pointers.emplace(VT_Global, AreaPointers(kGlobalStart));
    memory_pointers.emplace(VT_Local, AreaPointers(kLocalStart));
    memory_pointers.emplace(VT_Temporary, AreaPointers(kTemporaryStart));
    memory_pointers.emplace(VT_Constant, AreaPointers(kConstantStart));
  }
  void DeclareGlobal(string type, string name) {
    DeclareVariable(VT_Global, type, name);
  }
  void DeclareLocal(string type, string name) {
    DeclareVariable(VT_Local, type, name);
  }
  void DeclareConstant(string type, string name) {
    DeclareVariable(VT_Constant, type, name);
  }
  void DeclareTemporary(string type, string name) {
    DeclareVariable(VT_Temporary, type, name);
  }
  void DeclareVariable(VariableLifetime lifetime, string variable_type, string var_name) {
    auto& area_pointers = memory_pointers.find(lifetime)->second;

    if (variable_type == "int")
      address_to_var[area_pointers.next_int++] = var_name;
    else if (variable_type == "float")
      address_to_var[area_pointers.next_float++] = var_name;
    else if (variable_type == "string")
      address_to_var[area_pointers.next_string++] = var_name;
    else if (variable_type == "bool")
      address_to_var[area_pointers.next_bool++] = var_name;
    else if (variable_type == "char")
      address_to_var[area_pointers.next_char++] = var_name;
    else {
      cout << "Invalid type: " << variable_type << endl;
      assert(false);
    }
  }
  void DeclareGlobalArray(string type, string name, int size) {
    DeclareArrayVariable(VT_Global, type, name, size);
  }
  void DeclareLocalArray(string type, string name, int size) {
    DeclareArrayVariable(VT_Local, type, name, size);
  }
  void DeclareArrayVariable(VariableLifetime lifetime, string variable_type, string var_name, int size) {
    auto& area_pointers = memory_pointers.find(lifetime)->second;

    if (lifetime != VT_Global && lifetime != VT_Local) {
      cout << "Array can't be declared in Lifetime: " << lifetime << endl;
      assert(false);
    }
    if (variable_type == "int") {
      address_to_var[area_pointers.next_int] = var_name;
      area_pointers.next_int += size;
    }
    else if (variable_type == "float") {
      address_to_var[area_pointers.next_float] = var_name;
      area_pointers.next_float += size;
    }
    else if (variable_type == "string") {
      address_to_var[area_pointers.next_string] = var_name;
      area_pointers.next_string += size;
    }
    else if (variable_type == "bool") {
      address_to_var[area_pointers.next_bool] = var_name;
      area_pointers.next_bool += size;
    }
    else if (variable_type == "char") {
      address_to_var[area_pointers.next_char] = var_name;
      area_pointers.next_char += size;
    }
    else {
      cout << "Invalid type: " << variable_type << endl;
      assert(false);
    }

  }
  int Get(VariableLifetime lifetime, string type, string var_name) {
     int start = kGlobalStart; 
     if (lifetime == VT_Local) start = kLocalStart;
     if (lifetime == VT_Constant) start = kConstantStart;
     if (lifetime == VT_Temporary) start = kTemporaryStart;

     if (type == "int") start += kTypeOffset*0;
     if (type == "float") start += kTypeOffset*1;
     if (type == "string") start += kTypeOffset*2;
     if (type == "bool") start += kTypeOffset*3;
     if (type == "char") start += kTypeOffset*4;

     for (int i = start; i < start + kTypeOffset; i++) {
       if (address_to_var[i] == var_name) {
         return i;
       }
     }

     return -1;
  }
  string Get(string name, string type) {
    int address;

    if (name[0] == '&')
      return "&" + Get(name.substr(1), type);
    else if (name[0] == '*')
      address = Get(VT_Temporary, type, name);
    else if (name[0] == '$')
      address = Get(VT_Constant, type, name);
    else {
      address = Get(VT_Global, type, name);
      if (address == -1)
        address = Get(VT_Local, type, name);
    }

    if (address == -1) {
      cout << type << " " << name << endl;
      assert(false);
    }

    return toString(address);
  }
  void ResetLocals() {
    memory_pointers.emplace(VT_Local, AreaPointers(kLocalStart));
  }
  void ResetTemporaries() {
    memory_pointers.emplace(VT_Temporary, AreaPointers(kTemporaryStart));
  }
  const int kGlobalStart = kMemSize/4*0, kLocalStart = kMemSize/4*1, kTemporaryStart = kMemSize/4*2, kConstantStart = kMemSize/4*3;
 private:
  vector<string> address_to_var;
  struct AreaPointers {
    AreaPointers(int area_start) {
      next_int = area_start + kMemSize/4/5*0;
      next_float = area_start + kMemSize/4/5*1;
      next_string = area_start + kMemSize/4/5*2;
      next_bool = area_start + kMemSize/4/5*3;
      next_char = area_start + kMemSize/4/5*4;
    }
    int next_int;
    int next_float;
    int next_string;
    int next_bool;
    int next_char;
  };
  map<VariableLifetime, AreaPointers> memory_pointers;
  const int kTypeOffset = kMemSize/4/5;
  static const int kMemSize = 10000;
  string toString(int num) {
    stringstream ss;
    ss << num;
    return ss.str();
  }
};

#endif // MEMORY_MAP_H
