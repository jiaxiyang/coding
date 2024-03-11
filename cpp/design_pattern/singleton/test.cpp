#include <iostream>
#include <string>

// 懒汉版：第一次使用初始化
class Singleton {
public:
  static Singleton &getInstance() {
    static Singleton singleton; // static变量是多线程安全的
    return singleton;
  }

  std::string getName() { return "Singleton"; };

private:
  // 构造函数不能delete
  Singleton() { std::cout << "Deconstruct Singleton" << std::endl; }
  ~Singleton() noexcept {
    std::cout << "Deconstruct Singleton" << std::endl;
  } // noexcept关键字告诉编译器，函数中不会发生异常,这有利于编译器对程序做更多的优化。如果在运行时，noexecpt函数向外抛出了异常（如果函数内部捕捉了异常并完成处理，这种情况不算抛出异常），程序会直接终止，调用std::terminate()函数，该函数内部会调用std::abort()终止程序。
  Singleton(const Singleton &other) = delete;
  Singleton &operator=(const Singleton &other) = delete;
};

// 恶汉版：main之前初始化
class Singleton1 {
public:
  static Singleton1 &getInstance() { return singleton_; }

  std::string getName() { return "Singleton1"; };

private:
  Singleton1() { std::cout << "Construct Singleton1" << std::endl; }

  ~Singleton1() noexcept { std::cout << "Deconstruct Singleton1" << std::endl; }
  Singleton1(const Singleton1 &other) = delete;
  Singleton1 &operator=(const Singleton1 &other) = delete;

private:
  static Singleton1 singleton_;
};

Singleton1 Singleton1::singleton_;

int main(int argc, char *argv[]) {
  // Singleton sin; // 报错，不能调用构造函数
  // 使用auto需要加引用, 否则会调用copy constructor
  auto &sin0 = Singleton::getInstance();
  std::cout << "0:" << sin0.getName() << ", address=" << &sin0 << std::endl;
  auto &sin1 = Singleton::getInstance();
  std::cout << "1:" << sin1.getName() << ", address=" << &sin1 << std::endl;

  auto &sin2 = Singleton1::getInstance();
  std::cout << "2:" << sin2.getName() << ", address=" << &sin2 << std::endl;
  auto &sin3 = Singleton1::getInstance();
  std::cout << "3:" << sin3.getName() << ", address=" << &sin3 << std::endl;

  return 0;
}
