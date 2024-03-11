#include <iostream>
#include <string>

class Singleton {
public:
  static Singleton &getInstance() {
    static Singleton singleton;
    return singleton;
  }

  std::string getName() { return "Singleton"; };

private:
  Singleton() {}
  Singleton(const Singleton &other) {}
  ~Singleton() noexcept {
  } // noexcept关键字告诉编译器，函数中不会发生异常,这有利于编译器对程序做更多的优化。如果在运行时，noexecpt函数向外抛出了异常（如果函数内部捕捉了异常并完成处理，这种情况不算抛出异常），程序会直接终止，调用std::terminate()函数，该函数内部会调用std::abort()终止程序。
  Singleton &operator=(const Singleton &other) { return *this; }
};

int main(int argc, char *argv[]) {
  // Singleton sin; // 报错，不能调用构造函数
  // 使用auto需要加引用, 否则会调用copy constructor
  auto &sin = Singleton::getInstance();
  std::cout << "1:" << sin.getName() << ", address=" << &sin << std::endl;
  auto &sin1 = Singleton::getInstance();
  std::cout << "2:" << sin1.getName() << ", address=" << &sin1 << std::endl;

  return 0;
}
