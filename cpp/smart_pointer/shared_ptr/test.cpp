#include <iostream>
#include <memory>

template <typename T>

class SharedPtr {
public:
  //! Default constructor
  SharedPtr(T *raw_ptr) : raw_ptr_(raw_ptr), ref_count_(new int(1)){};

  //! Copy constructor
  SharedPtr(SharedPtr &other) {
    raw_ptr_ = other.raw_ptr_;
    ref_count_ = other.ref_count_;
    *ref_count_ = *ref_count_ + 1;
    std::cout << "Copy Constructor ref: " << *ref_count_ << std::endl;
  };

  //! Copy assignment operator
  SharedPtr &operator=(const SharedPtr &other) {
    if (this != &other) {
      release();
      raw_ptr_ = other.raw_ptr_;
      ref_count_ = other.ref_count_;
      *ref_count_ = *ref_count_ + 1;
      std::cout << "Copy assignment Constructor ref: " << *ref_count_
                << std::endl;
    }

    return *this;
  };

  //! Destructor
  ~SharedPtr() { release(); };

  void release() {
    *ref_count_ = *ref_count_ - 1;
    std::cout << "Deconstructor ref: " << *ref_count_ << std::endl;

    if (*ref_count_ == 0) {
      std::cout << "Release resource" << std::endl;
      delete raw_ptr_;
      delete ref_count_;
    }
  }

  T &operator*() { return *raw_ptr_; };

  T *operator->() { return raw_ptr_; }

  int use_count() { return *ref_count_; }

  T *raw_ptr_;
  int *ref_count_;
};

int main(int argc, char *argv[]) {
  auto ptr = SharedPtr<int>(new int(5));
  std::cout << ptr.use_count() << std::endl;
  auto ptr1(ptr);
  std::cout << ptr1.use_count() << std::endl;
  auto ptr2 = SharedPtr<int>(new int(6));
  std::cout << *ptr2 << std::endl;
  std::cout << ".........." << std::endl;

  // auto ptr2 = ptr;
  ptr2 = ptr;

  std::cout << ptr2.use_count() << std::endl;
  std::cout << *ptr2 << std::endl;

  return 0;
}
