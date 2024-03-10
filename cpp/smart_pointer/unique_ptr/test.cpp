#include <iostream>
#include <memory>
#include <vector>

// int main(int argc, char *argv[]) {
//   int i = 0;
//   auto deleter = [i](int *p) mutable {
//     std::cout << "delete int " << std::endl;
//     i = 10;
//     std::cout << i << std::endl;
//     delete p;
//   };

//   {
//     // unique_ptr模板有两个类型参数，所以必须有decltype(deleter)
//     auto ptr = std::unique_ptr<int, decltype(deleter)>(new int(4), deleter);
//     std::cout << "addr: " << ptr.get() << std::endl;
//     std::cout << "value: " << *ptr.get() << std::endl;
//     auto ptr1 = ptr.release();

//     // auto ptr(std::unique_ptr<int>(new int(4)), deleter);
//   }

//   std::cout << i << std::endl;

//   // shared_ptr模板只有一个类型参数，deleter是函数的参数
//   // std::shared_ptr<int> ptr(new int(42), [](int *ptr) {
//   //   std::cout << "Custom deleter called\n";
//   //   delete ptr;
//   // });
//   // std::cout << *ptr << std::endl;
//   return 0;
// }

// class Name
// {
// public:
//     //! Default constructor
//     Name();

//     //! Copy constructor
//     Name(const Name &other);

//     //! Move constructor
//     Name(Name &&other) noexcept;

//     //! Destructor
//     virtual ~Name() noexcept;

//     //! Copy assignment operator
//     Name& operator=(const Name &other);

//     //! Move assignment operator
//     Name& operator=(Name &&other) noexcept;

// protected:
// private:
// };

template <typename T>

class UniquePtr {
public:
  explicit UniquePtr(T *ptr)
      : raw_ptr_(
            ptr) { // 初始化列表比构造函数里赋值更高效：直接用参数构造，省去了一次赋值操作
    std::cout << "UniquePtr Construction" << std::endl;
  };
  // copy 构造函数: 更高效，直接用other成员变量构造自己的成员变量
  // other为什么传引用？ 传值会涉及到复制的操作，中间会有临时对象，引用更高效
  UniquePtr(const UniquePtr &other) = delete;
  // copy 赋值构造函数： 需要先构造默认成员变量，再使用other成员变量来赋值
  UniquePtr &operator=(const UniquePtr &other) = delete;

  ~UniquePtr() {
    std::cout << "UniquePtr Deconstruction" << std::endl;
    delete raw_ptr_;
    raw_ptr_ = nullptr;
  };

  T &operator*() { return *raw_ptr_; };

  T *operator->() { return raw_ptr_; }

private:
  T *raw_ptr_;
};

struct Test {
  Test(int a1, int b1) : a(a1), b(b1){};
  // Test(int a1, int b1) : {
  //   a = a1;
  //   b = b1;
  // };
  int a;
  int b;
};

void func(UniquePtr<int> i) {}

int main(int argc, char *argv[]) {
  // auto ptr = UniquePtr<Test>(new Test(1, 2));

  // 构造函数必须为explicit， 否则会出现所有权问题，导致资源被提前释放
  // auto raw_ptr = new int(5);
  // std::cout << *raw_ptr << std::endl;
  // func(raw_ptr);
  // std::cout << *raw_ptr << std::endl;

  auto ptr1(ptr);
  auto ptr1 = ptr;

  std::cout << (*ptr).a << std::endl;
  std::cout << (*ptr).b << std::endl;
  std::cout << ptr->a << std::endl;
  std::cout << ptr->b << std::endl;

  Test *test_ptr = new Test(3, 4);
  std::cout << test_ptr->a << std::endl;
  delete test_ptr;

  Test test(5, 6);
  std::cout << test.a << std::endl;

  return 0;
}
