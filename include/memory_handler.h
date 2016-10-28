class MemoryHandler {
private:
  int address[16];

public:
  MemoryHandler() {
    for (int i = 0; i < 16; i++) {
      address[i] = 1000*(i + 1);
    }
  }
  int getGlobalMemoryAddress(std::string type) {
    int index = typeIndex(type);
    return address[index]++;
  }
  int getLocalMemoryAddress(std::string type) {
    int index = typeIndex(type);
    return address[4 + index]++;
  }
  int getTemporalMemoryAddress(std::string type) {
    int index = typeIndex(type);
    return address[8 + index]++;
  }
  int getConstantMemoryAddress(std::string type) {
    int index = typeIndex(type);
    return address[12 + index]++;
  }
  void reset() {
    for (int i = 4; i < 12; i++) {
      address[i] = 1000*(i + 1);
    }
  }
  
private:
  int typeIndex(std::string type) {
    if (type == "int") return 0;
    if (type == "float") return 1;
    if (type == "char") return 2;
    if (type == "bool") return 3;
  }
};
