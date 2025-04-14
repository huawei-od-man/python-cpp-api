#ifndef REF_H
#define REF_H

#include <memory>

#include "object.h"

class ref {
 public:
  template <typename T>
  ref(T&& value);

  ref() = default;

  explicit ref(std::shared_ptr<object> ptr) noexcept : _ptr(std::move(ptr)) {}

  template <typename T>
  explicit ref(std::shared_ptr<box<T>> box_ptr) noexcept
      : _ptr(std::move(box_ptr)) {}

  ref(ref& other) noexcept : _ptr(other._ptr) {}
  ref(const ref&) noexcept = default;
  ref(ref&&) noexcept = default;
  ref& operator=(const ref&) noexcept = default;
  ref& operator=(ref&&) noexcept = default;

  constexpr object* operator->() const noexcept { return _ptr.get(); }
  constexpr object& operator*() const noexcept { return *_ptr; }
  explicit operator bool() const noexcept { return _ptr != nullptr; }

  template <typename T>
  T& as();

  template <typename T>
  const T& as() const;

 private:
  std::shared_ptr<object> _ptr;
};

inline
std::ostream& operator<<(std::ostream& os, const ref& obj) {
  if (obj) {
    obj->format(os);
  } else {
    os << "None";
  }
  return os;
}

ref operator+(ref lhs, ref rhs);

namespace std {
template <>
struct hash<::ref> {
  size_t operator()(const ::ref& r) const noexcept { return r->hash(); }
};
template <>
struct equal_to<::ref> {
  bool operator()(const ::ref& lhs, const ::ref& rhs) const noexcept {
    return *lhs == *rhs;
  }
};
template <>
struct less<::ref> {
  bool operator()(const ::ref& lhs, const ::ref& rhs) const noexcept {
    return *lhs < *rhs;
  }
};

}  // namespace std

#endif  // REF_H
