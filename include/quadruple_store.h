#include <vector>
#include <sstream>
#include <stack>
#include "cube.h"
#include "quadruple.h"

class QuadrupleStore {
private:
  std::vector<Quadruple> quads;
  std::stack<std::string> typeStack;
  std::stack<std::string> operandStack;
  std::stack<std::string> operatorStack;
  int counter = 0;
  int tempCounter = 0;
  int constCounter = 0;
public:
  void pushOperand(std::string operand, std::string type) {
    operandStack.push(operand);
    typeStack.push(type);
  }
  void pushConstant(std::string type) {
    // TODO: send value as well
    operandStack.push(getConstantVariable());
    typeStack.push(type);
  }
  void pushOperator(std::string oper) {
    operatorStack.push(oper);
  }
  void popOperator(int priority) {
    // Check whether the next operator to evaluate has the expected priority
    if (operatorStack.empty()) {
      return;
    }
    std::string oper = operatorStack.top();
    int operPriority = getOperPriority(oper);
    if (operPriority != priority) {
      return;
    }
    operatorStack.pop();

    // Pop operands and types from their stacks
    std::string type1 = "", operand1 = "", type2 = "", operand2 = "";
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
    std::string resultType = Cube::getOperationType(oper, type1, type2);
    if (resultType == "") {
      semanticError("Invalid operation: " + type1 + " " + oper + " " + type2);
    }

    // Push new quadruple and result to stacks
    std::string result = getTemporalVariable();
    Quadruple quad(oper, operand1, operand2, result);
    typeStack.push(resultType);
    operandStack.push(result);
    quads.push_back(quad);
    counter++;
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
  void print() {
    for (int i = 0; i < quads.size(); i++) {
      std::cout << "[" << quads[i].a << ", " << quads[i].b << ", " << quads[i].c << ", " << quads[i].d << "]" << std::endl; 
    }
  }
private:
  std::string getTemporalVariable() {
    std::stringstream ss;
    ss << "t" << tempCounter;
    tempCounter++;
    return ss.str();
  }
  std::string getConstantVariable() {
    std::stringstream ss;
    ss << "c" << constCounter;
    constCounter++;
    return ss.str();
  }
  int getOperPriority(std::string oper) {
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
  }
  void semanticError(std::string err) {
    std::cout << "Semantic error: " << err << std::endl;
    exit(1);
  }
};
