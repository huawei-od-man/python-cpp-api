#ifndef REF_H
#define REF_H

#include "forward.h"

template <typename T>
class ref {
 public:
  ref() : ptr_(nullptr) {}

  ref(std::nullptr_t) : ref() {}

  template <typename U, std::enable_if_t<std::is_convertible<U*, T*>::value &&
                                         !std::is_same<U, T>::value>>
  ref(U* ptr) : ref(static_cast<T*>(ptr)) {}

  ref(T* ptr = nullptr) : ptr_(ptr) {
    if (ptr_) {
      ptr_->add_ref();
    }
  }
  ref(const ref& other) : ptr_(other.ptr_) {
    if (ptr_) {
      ptr_->add_ref();
    }
  }
  ref(ref&& other) noexcept : ptr_(other.ptr_) { other.ptr_ = nullptr; }
  ~ref() {
    if (ptr_) {
      ptr_->release();
    }
  }
  ref& operator=(const ref& other) {
    if (ptr_ != other.ptr_) {
      if (ptr_) {
        ptr_->release();
      }
      ptr_ = other.ptr_;
      if (ptr_) {
        ptr_->add_ref();
      }
    }
    return *this;
  }
  ref& operator=(ref&& other) noexcept {
    if (ptr_!= other.ptr_) {
      if (ptr_) {
        ptr_->release();
      }
      ptr_ = other.ptr_;
      other.ptr_ = nullptr;
    }
    return *this;
  }
  T* operator->() const {
    return ptr_;
  }

  explicit operator bool() const { return ptr_->__bool__().value(); }
  explicit operator double() const { return ptr_->__float__().value(); }

 private:
  T* ptr_;
};

template <typename T, typename U>
bool operator==(ref<T> lhs, ref<U> rhs) {
  return lhs->__eq__(rhs);
}

#endif
