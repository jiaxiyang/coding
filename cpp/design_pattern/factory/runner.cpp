#include <iostream>
#include <memory>
#include <string>

class Runner {
public:
  static std::unique_ptr<Runner> create(std::string &config);
  virtual std::string run(std::string &input) = 0;

public:
  virtual ~Runner() { std::cout << "Deconstruct Runner" << std::endl; };

protected:
  Runner(){};

private:
  Runner(const Runner &other) = delete;
};

// 需要public继承，默认是private
class RunnerImp1 : public Runner {
public:
  RunnerImp1(std::string &config) {
    std::cout << "Construct RunnerImp1: " << config << std::endl;
  };

  virtual std::string run(std::string &input) override {
    return "RunnerImp1 result";
  }

  ~RunnerImp1() { std::cout << "Deconstruct RunnerImp1" << std::endl; }
};

class RunnerImp2 : public Runner {
public:
  RunnerImp2(std::string &config) {
    std::cout << "Construct RunnerImp2: " << config << std::endl;
  };

  virtual std::string run(std::string &input) override {
    return "RunnerImp2 result";
  }

  ~RunnerImp2() { std::cout << "Deconstruct RunnerImp2" << std::endl; }
};

std::unique_ptr<Runner> Runner::create(std::string &config) {
  if (config == "imp1")
    return std::unique_ptr<Runner>(new RunnerImp1(config));
  else if (config == "imp2")
    return std::unique_ptr<Runner>(new RunnerImp2(config));
  else
    return std::unique_ptr<Runner>(new RunnerImp1(config));
};

int main(int argc, char *argv[]) {
  std::string test = "imp2";
  auto runner = Runner::create(test);
  auto result = runner->run(test);
  std::cout << "result: " << result << std::endl;

  return 0;
}
