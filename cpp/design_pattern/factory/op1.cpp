#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

class Op {
public:
  Op(std::string config){};
  Op(const Op &other) = delete;
  Op &operator=(const Op &other) = delete;
  virtual ~Op(){};

public:
  virtual std::string get_info() = 0;
  virtual std::string run(std::string input) = 0;
};

class Relu : public Op {
public:
  Relu(std::string config) : Op(config), config_(config) {
    std::cout << "Construct relu, config: " << config << std::endl;
  }
  Relu(const Relu &other) = delete;
  Relu &operator=(const Relu &other) = delete;
  ~Relu() { std::cout << "Deconstruct relu" << std::endl; }

public:
  std::string get_info() override { return config_; }
  std::string run(std::string input) override { return "relu output"; }

private:
  std::string config_;
  static int hold_;
};

class OpRegister {
public:
  static OpRegister &get_instance() {
    static OpRegister op_register;
    return op_register;
  }

  int regist(std::string name, std::function<std::unique_ptr<Op>()> creator) {
    map_[name] = creator;
    return 0;
  }
  std::unique_ptr<Op> create(std::string op) {
    if (map_.find(op) != map_.end()) {

      auto creator = map_[op];
      return creator();

    } else {
      std::cerr << "Don't support " << op << std::endl;
    }
    return nullptr;
  }

private:
  OpRegister() { std::cout << "Construct OpRegister" << std::endl; };
  ~OpRegister() { std::cout << "Deconstruct OpRegister" << std::endl; }
  OpRegister(const OpRegister &other) = delete;
  OpRegister &operator=(const OpRegister &other) = delete;

private:
  std::unordered_map<std::string, std::function<std::unique_ptr<Op>()>> map_;
};

#define OPREGIST(op)                                                           \
  int op::hold_ = OpRegister::get_instance().regist(                           \
      #op, []() { return std::unique_ptr<op>(new op(#op)); });
OPREGIST(Relu)

int main(int argc, char *argv[]) {
  std::cout << "begin main" << std::endl;

  auto relu = OpRegister::get_instance().create("Relu");
  std::cout << relu->run("relu input") << std::endl;

  return 0;
}
