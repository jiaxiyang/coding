#include <algorithm>
#include <iostream>
#include <map>
#include <memory>

class Op {
public:
  Op(std::string name){};
  virtual std::string run(std::string input) = 0;

public:
  virtual ~Op() { std::cout << "Deconstruct Op" << std::endl; };

private:
  Op(const Op &other) = delete;
};

class Relu : public Op {
public:
  Relu(std::string name) : Op(name) {
    std::cout << "Construct Relu" << std::endl;
  };
  ~Relu() override { std::cout << "Deconstruct Relu" << std::endl; };
  std::string run(std::string input) { return "Relu result"; };

public:
  static int hold_;
};

class Conv : public Op {
public:
  Conv(std::string name) : Op(name) {
    std::cout << "Construct Conv" << std::endl;
  };
  ~Conv() override { std::cout << "Deconstruct Conv" << std::endl; };
  std::string run(std::string input) { return "Conv result"; };

public:
  static int hold_;
};

class OpRegister {
public:
  static OpRegister &get_instance() {
    static OpRegister op_register;
    return op_register;
  }

  int regist(std::string name, std::function<std::unique_ptr<Op>()> func) {
    map_[name] = func;
    return 0;
  }
  void list() {
    std::cout << "Map list:" << std::endl;

    for (auto &m : map_) {
      std::cout << m.first << std::endl;
    }
  }

  std::unique_ptr<Op> create(std::string name) {
    if (map_.find(name) != map_.end()) {
      auto &creator = map_[name];
      return creator();
    } else {
      std::cerr << name << " not support!" << std::endl;
    }
    return nullptr;
  }

private:
  OpRegister() { std::cout << "Construct OpRegister" << std::endl; };
  ~OpRegister() { std::cout << "Deconstruct OpRegister" << std::endl; };
  OpRegister(const OpRegister &other) = delete;
  OpRegister &operator=(const OpRegister &other) = delete;

private:
  std::unordered_map<std::string, std::function<std::unique_ptr<Op>()>> map_;
};

#define OPREGIST(name)                                                         \
  int name::hold_ =                                                            \
      OpRegister::get_instance().regist(#name, []() -> std::unique_ptr<Op> {   \
        return std::make_unique<name>(#name);                                  \
      });

OPREGIST(Relu);
OPREGIST(Conv);

int main(int argc, char *argv[]) {
  OpRegister::get_instance().list();
  auto relu = OpRegister::get_instance().create("Relu");
  std::cout << relu->run("relu input") << std::endl;
  auto conv = OpRegister::get_instance().create("Conv");
  std::cout << relu->run("conv input") << std::endl;

  return 0;
}
