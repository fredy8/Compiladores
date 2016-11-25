#ifndef VIRTUAL_MACHINE_H_
#define VIRTUAL_MACHINE_H_

#include <iostream>
#include <type_traits>
#include <stack>
#include <string>
#include <iostream>
#include <vector>
#include <boost/any.hpp>
#include "quadruple.h"

using namespace std;
using namespace boost;

set<string> operators { ">", "<", ">=", "<=", "==", "!=", "+", "-", "/", "*", "%", "&&" };

class VirtualMachine {
 public:
  VirtualMachine(vector<Quadruple> quads) : quads(quads) {
    memory.push(vector<any>(kMemSize, 0));
  }
  void Start() {
    int halt = quads.size();
    next_instruction = 0;
    while (next_instruction != halt) {
      int last_instruction = next_instruction;
      Execute();
      if (next_instruction == last_instruction)
        next_instruction++;
    }
  }
 private:
  void Execute() {
    Quadruple quad = quads[next_instruction];
    if (quad.a == "GOTO") {
      next_instruction = stoi(quad.d); 
    } else if (quad.a == "CONSTANT") {
      string address = quad.d;
      if (quad.b == "int") {
        int value = stoi(quad.c);
        access_memory(address) = value;
      } else if (quad.b == "float") {
        double value = stod(quad.c);
        access_memory(address) = value;
      } else if (quad.b == "string") {
        if (quad.c.find("\\n") != string::npos) {
          quad.c.replace(quad.c.find("\\n"), 2, "\n");
        }
        access_memory(address) = quad.c.substr(1, quad.c.size() - 2);
      } else if (quad.b == "bool") {
        access_memory(address) = quad.c == "true";
      } else if (quad.b == "char") {
        access_memory(address) = quad.c[0];
      } else {
        cout << "unsupported constant type" << endl;
        assert(false);
      }
    } else if (quad.a == "=") {
      string read_address = quad.b;
      string write_address = quad.d;
      access_memory(write_address) = access_memory(read_address);
    } else if (operators.find(quad.a) != operators.end()) {
      any left_val = access_memory(quad.b);
      any right_val = access_memory(quad.c);

      string write_address = quad.d;

      int lefti = left_val.type() == typeid(int) ? any_cast<int>(left_val) : 0;
      int righti = right_val.type() == typeid(int) ? any_cast<int>(right_val) : 0;

      bool both_int = left_val.type() == typeid(int) && right_val.type() == typeid(int);

      double leftd = left_val.type() == typeid(double) ? any_cast<double>(left_val) : lefti;
      double rightd = right_val.type() == typeid(double) ? any_cast<double>(right_val) : righti;

      bool leftb = left_val.type() == typeid(bool) ? any_cast<bool>(left_val) : 0;
      bool rightb = right_val.type() == typeid(bool) ? any_cast<bool>(right_val) : 0;
      auto&& w = access_memory(write_address);

      if (quad.a == "<") w = both_int ? lefti < righti : leftd < rightd;
      else if (quad.a == ">") if (both_int) w = lefti > righti; else w = leftd > rightd;
      else if (quad.a == ">=") if (both_int) w = lefti >= righti; else w = leftd >= rightd;
      else if (quad.a == "<=") if (both_int) w = lefti <= righti; else w = leftd <= rightd;
      else if (quad.a == "==") if (both_int) w = lefti == righti; else w = leftd == rightd;
      else if (quad.a == "+") if (both_int) w = lefti + righti; else w = leftd + rightd;
      else if (quad.a == "-") if (both_int) w = lefti - righti; else w = leftd - rightd;
      else if (quad.a == "/") if (both_int) w = lefti / righti; else w = leftd / rightd;
      else if (quad.a == "*") if (both_int) w = lefti * righti; else w = leftd * rightd;
      else if (quad.a == "%") w = lefti % righti;
      else if (quad.a == "&&") w = leftb && rightb;

    } else if (quad.a == "!") {
      string operand_address = quad.b;
      string write_address = quad.d;
      access_memory(write_address) = !any_cast<bool>(access_memory(operand_address));
    } else if (quad.a == "RETURN") {
      int return_address = stack_.top();
      stringstream ss;
      ss << return_address;
      stack_.pop();
      next_instruction = any_cast<int>(access_memory(ss.str()));
    } else if (quad.a == "POP") {
      string write_address = quad.b;
      stringstream ss;
      ss << stack_.top();
      access_memory(write_address) = access_memory(ss.str());
      stack_.pop();
    } else if (quad.a == "PUSH") {
      string index = quad.b;
      if (index[0] == '&') {
        index = index.substr(1);
        int idx = any_cast<int>(memory.top()[stoi(index)]);
        stringstream ss;
        ss << idx;
        index = ss.str();
      }

      int num = stoi(index);
      stack_.push(num);
    } else if (quad.a == "GOTOF") {
      string condition_address = quad.b;
      int goto_instruction = stoi(quad.d);
      if (!any_cast<bool>(access_memory(condition_address)))
        next_instruction = goto_instruction;
    } else if (quad.a == "GOTOV") {
      string condition_address = quad.b;
      int goto_address = stoi(quad.d);
      if (any_cast<bool>(access_memory(condition_address)))
        next_instruction = goto_address;
    } else if (quad.a == "PRINT") {
      int read_address = stack_.top();
      stringstream ss;
      ss << read_address;
      stack_.pop();
      cout << any_cast<string>(access_memory(ss.str()));
    } else if (quad.a == "READ") {
      string write_address = quad.b;
      string val;
      cin >> val;
      access_memory(write_address) = val;
    } else if (quad.a == "STRCAT") {
      string write_address = quad.b;
      int left = stack_.top(); stack_.pop();
      int right = stack_.top(); stack_.pop();
      stringstream ss, ss2;
      ss << left;
      ss2 << right;
      access_memory(write_address) = any_cast<string>(access_memory(ss.str())) + any_cast<string>(access_memory(ss2.str()));
    } else if (quad.a == "ITOS") {
      string write_address = quad.b;
      int int_address = stack_.top(); stack_.pop();
      stringstream ss, ss2;
      ss2 << int_address;
      ss << any_cast<int>(access_memory(ss2.str()));
      access_memory(write_address) = ss.str();
    } else if (quad.a == "STOI") {
      string write_address = quad.b;
      int string_address = stack_.top(); stack_.pop();
      stringstream ss;
      ss << string_address;
      string str = any_cast<string>(access_memory(ss.str()));
      access_memory(write_address) = stoi(str);
    } else if (quad.a == "VER") {
      int idx = any_cast<int>(access_memory(quad.b));
      if (idx < 0 || idx >= stoi(quad.c)) {
        cout << "Invalid array access." << endl;
        exit(1);
      }
    } else if (quad.a == "SCOPE") {
      if (quad.b == "PUSH") {
        memory.push(memory.top());
      } else {
        int from = stoi(quad.c);
        int to = stoi(quad.d);
        vector<any> tp = memory.top();
        memory.pop();
        for (int i = 0; i < kMemSize; i++) {
          if (i < from || i > to) {
            memory.top()[i] = tp[i];
          }
        }
      }
    } else {
      cout << "Quadruple not supported: " << quad.a << endl;
      assert(false);
    }
  }
  stack<vector<any>> memory;
  stack<int> stack_;
  vector<Quadruple> quads;
  int next_instruction;
  int stoi(string str) {
    return atoi(str.c_str());
  }
  double stod(string str) {
    return atof(str.c_str());
  }
  any& access_memory(string index) {
    if (index[0] == '&') {
      index = index.substr(1);
      int idx = any_cast<int>(memory.top()[stoi(index)]);
      stringstream ss;
      ss << idx;
      index = ss.str();
    }

    return memory.top()[stoi(index)];
  }
  static const int kMemSize = 10000;
};

#endif // VIRTUAL_MACHINE_H_

