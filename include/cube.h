class Cube {
public:
  static std::string getOperationType(std::string oper, std::string type1, std::string type2) {
    int operType = operatorType(oper);
    switch (operType) {
      case 0:
        if (type1 == "int" && type2 == "int") 
          return "int";
        if (type1 == "int" || type1 == "float") && (type2 == "float" || type2 == "int")
          return "float";
        return "";
      case 1:
        if (type1 == "int" && type2 == "int")
          return "int";
        return "";
      case 2:
        if (type1 == "int" || type1 == "float") && (type2 == "float" || type2 == "int")
          return "bool";
        return "";
      case 3:
        if (type1 == "bool" && type2 == "bool") 
          return "bool";
        return "";
      case 4:
        if (type1 == "bool")
          return "bool";
        return "";
      default:
        return "";
    };
  }

private:
  static int operatorType(std::string oper) {
    if (oper == "+" || oper == "-" || oper == "*" || oper == "/")
      return 0;
    if (oper == "%")
      return 1;
    if (oper == ">" || oper == "<" || oper == "<=" || oper == ">=" || oper == "==")
      return 2;
    if (oper == "&&" || oper == "||")
      return 3;
    if (oper == "!")
      return 4;
    return -1;
  }
};
