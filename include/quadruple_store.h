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
  std::stack<int> jumpStack;
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
  void ifStart() {
    // Get information on the conditional and validate it's a bool
    std::string type = typeStack.top();
    typeStack.pop();
    std::string condition = operandStack.top();
    operandStack.pop();
    if (type != "bool") {
      semanticError("Expected bool on if statement");
    }
    // Generate GOTOF quadruple and store the counter to modify it later
    jumpStack.push(counter);
    quads.push_back(Quadruple("GOTOF", condition, "", ""));
    counter++;
  }
  void ifBlockEnd() {
    // Modify if statement quadruple to jump to the end of block
    int ifQuad = jumpStack.top();
    jumpStack.pop();
    quads[ifQuad].d = toString(counter + 1);
    // Add GOTO jump to the end of the if statement and store the counter
    jumpStack.push(counter);
    quads.push_back(Quadruple("GOTO", "", "", ""));
    counter++;
  }
  void ifEnd() {
    // Modify end of if block quadruple to jump to this point
    int endIfQuad = jumpStack.top();
    jumpStack.pop();
    quads[endIfQuad].d = toString(counter);
  }
  void whileConditionStart() {
    // Store the beginning of the expression evaluation to jump to
    jumpStack.push(counter);
  }
  void whileBlockStart() {
    // Get information on the conditional and validate it's a bool
    std::string type = typeStack.top();
    typeStack.pop();
    std::string condition = operandStack.top();
    operandStack.pop();
    if (type != "bool") {
      semanticError("Expected bool on while statement");
    }
    // Generate GOTOF quadruple and store the counter to modify it later
    jumpStack.push(counter);
    quads.push_back(Quadruple("GOTOF", condition, "", ""));
    counter++;
  }
  void whileEnd() {
    int gotof = jumpStack.top();
    jumpStack.pop();
    int jump = jumpStack.top();
    jumpStack.pop();
    // Go back to where the condition is evaluated
    quads.push_back(Quadruple("GOTO", "", "", toString(jump)));
    counter++;
    // Modify quadruple to jump to when false
    quads[gotof].d = toString(counter);
    std::cout << "Ending while on " << counter << ", with jump on " << gotof << std::endl;
  }
  void doWhileStart() {
    // Push to jump stack the start of the do while block
    jumpStack.push(counter);
  }
  void doWhileEnd() {
    // Get information on the conditional and validate it's a bool
    std::string type = typeStack.top();
    typeStack.pop();
    std::string condition = operandStack.top();
    operandStack.pop();
    if (type != "bool") {
      semanticError("Expected bool on do while statement");
    }
    // Generate GOTOV quadruple
    int jump = jumpStack.top();
    jumpStack.pop();
    quads.push_back(Quadruple("GOTOV", condition, "", toString(jump)));
    counter++;
  }
  void forConditionStart() {
    // Push to jump stack the beginning of the condition
    jumpStack.push(counter);
  }
  void forConditionEnd() {
    // Get information on the conditional and validate it's a bool
    std::string type = typeStack.top();
    typeStack.pop();
    std::string condition = operandStack.top();
    operandStack.pop();
    if (type != "bool") {
      semanticError("Expected bool on do while statement");
    }
    // Generate GOTOF quadruple
    jumpStack.push(counter);
    quads.push_back(Quadruple("GOTOF", condition, "", ""));
    counter++;
    // Jump to where the block starts (skip third element)
    jumpStack.push(counter);
    quads.push_back(Quadruple("GOTO", condition, "", ""));
    counter++;
    // Store the start of the third element of the for
    jumpStack.push(counter);
  }
  void forStart() {
    // Pop elements from the jump stack
    int jump4 = jumpStack.top();
    jumpStack.pop();
    int jump3 = jumpStack.top();
    jumpStack.pop();
    int jump2 = jumpStack.top();
    jumpStack.pop();
    int jump1 = jumpStack.top();
    jumpStack.pop();
    // Jump back to where the condition evaluation starts
    quads.push_back(Quadruple("GOTO", "", "", toString(jump1)));
    counter++;
    // Jump here when the condition is evaluated to true (code inside for)
    quads[jump3].d = toString(counter);
    // Put unused elements back into the stack
    jumpStack.push(jump2);
    jumpStack.push(jump4);
  }
  void forEnd() {
    // Jump back to the third element of the for
    int jump2 = jumpStack.top();
    jumpStack.pop();
    quads.push_back(Quadruple("GOTO", "", "", toString(jump2)));
    counter++;
    // Jump here when the condition is false and we exit the loop
    int jump1 = jumpStack.top();
    jumpStack.pop();
    quads[jump1].d = toString(counter);
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
  std::string toString(int num) {
    std::stringstream ss;
    ss << num;
    return ss.str();
  }
};
