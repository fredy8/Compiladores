#ifndef VIRTUAL_MACHINE_H_
#define VIRTUAL_MACHINE_H_

#include <iostream>
#include <type_traits>
#include <stack>
#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include <boost/any.hpp>
#include "quadruple.h"

using namespace std;
using namespace boost;

set<string> operators { ">", "<", ">=", "<=", "==", "!=", "+", "-", "/", "*", "%" };

class VirtualMachine {
 public:
  VirtualMachine(vector<Quadruple> quads) : quads(quads), memory(1000, 0) {}
  void Start() {
    int halt = quads.size();
    next_instruction = 0;
    while (next_instruction != halt) {
      int last_instruction = next_instruction;
      Execute(next_instruction);
      if (next_instruction == last_instruction)
        next_instruction++;
    }
  }
 private:
  void Execute(int instructionNum) {
    Quadruple quad = quads[instructionNum];
    if (quad.a == "GOTO") {
      next_instruction = stoi(quad.d); 
    } else if (quad.a == "CONSTANT") {
      int address = stoi(quad.d);
      if (quad.b == "int") {
        int value = stoi(quad.c);
        memory[address] = value;
      } else if (quad.b == "float") {
        double value = stod(quad.c);
        memory[address] = value;
      } else if (quad.b == "string") {
        memory[address] = quad.c;
      } else if (quad.b == "bool") {
        memory[address] = quad.c == "true";
      } else if (quad.b == "char") {
        memory[address] = quad.c[0];
      } else {
        cout << "unsupported constant type" << endl;
        assert(false);
      }
    } else if (quad.a == "=") {
      int read_address = stoi(quad.b);
      int write_address = stoi(quad.d);
      memory[write_address] = memory[read_address];
    } else if (operators.find(quad.a) != operators.end()) {
      any left_val = memory[stoi(quad.b)];
      any right_val = memory[stoi(quad.c)];

      int write_address = stoi(quad.d);

      int lefti = left_val.type() == typeid(int) ? any_cast<int>(left_val) : 0;
      int righti = right_val.type() == typeid(int) ? any_cast<int>(right_val) : 0;

      bool both_int = left_val.type() == typeid(int) && right_val.type() == typeid(int);

      double leftd = left_val.type() == typeid(double) ? any_cast<double>(left_val) : lefti;
      double rightd = right_val.type() == typeid(double) ? any_cast<double>(right_val) : righti;

      bool leftb = left_val.type() == typeid(bool) ? any_cast<bool>(left_val) : 0;
      bool rightb = right_val.type() == typeid(bool) ? any_cast<bool>(right_val) : 0;

      if (quad.a == "<") memory[write_address] = both_int ? lefti < righti : leftd < rightd;
      else if (quad.a == ">") memory[write_address] = both_int ? lefti > righti : leftd > rightd;
      else if (quad.a == ">=") memory[write_address] = both_int ? lefti >= righti : leftd >= rightd;
      else if (quad.a == "<=") memory[write_address] = both_int ? lefti <= righti : leftd <= rightd;
      else if (quad.a == "==") memory[write_address] = both_int ? lefti == righti : leftd == rightd;
      else if (quad.a == "+") memory[write_address] = both_int ? lefti + righti : leftd + rightd;
      else if (quad.a == "-") memory[write_address] = both_int ? lefti - righti : leftd - rightd;
      else if (quad.a == "/") memory[write_address] = both_int ? lefti / righti : leftd / rightd;
      else if (quad.a == "*") memory[write_address] = both_int ? lefti * righti : leftd * rightd;
      else if (quad.a == "%") memory[write_address] = lefti > righti;

    } else if (quad.a == "!") {
    } else if (quad.a == "RETURN") {
      int return_address = stack_.top();
      stack_.pop();
      next_instruction = any_cast<int>(memory[return_address]);
    } else if (quad.a == "POP") {
      int write_address = stoi(quad.b);
      memory[write_address] = memory[stack_.top()];
      stack_.pop();
    } else if (quad.a == "PUSH") {
      int num = stoi(quad.a);
      stack_.push(num);
    } else if (quad.a == "GOTOF") {
      bool condition_address = stoi(quad.b);
      bool goto_address = stoi(quad.d);
      if (!any_cast<bool>(memory[condition_address]))
        next_instruction = goto_address;
    } else if (quad.a == "GOTOV") {
      bool condition_address = stoi(quad.b);
      bool goto_address = stoi(quad.d);
      if (any_cast<bool>(memory[condition_address]))
        next_instruction = goto_address;
    } else if (quad.a == "PRINT") {
      int read_address = stoi(quad.d);
      cout << any_cast<string>(memory[read_address]);
    } else if (quad.a == "READ") {
      int write_address = stoi(quad.d);
      string val;
      cin >> val;
      memory[write_address] = val;
    } else {
      cout << "Quadruple not supported: " << quad.a << endl;
      assert(false);
    }
  }
  vector<any> memory;
  stack<int> stack_;
  vector<Quadruple> quads;
  int next_instruction;
};

#endif // VIRTUAL_MACHINE_H_

