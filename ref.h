#ifndef REF_H
#define REF_H

#include <memory>

#include "object.h"

class ref {
 public:
  ref() = default;

  explicit ref(std::shared_ptr<object> ptr) noexcept : _ptr(std::move(ptr)) {}

  ref(const ref&) noexcept = default;
  ref(ref&&) noexcept = default;
  ref& operator=(const ref&) noexcept = default;
  ref& operator=(ref&&) noexcept = default;

  constexpr object* operator->() const noexcept { return _ptr.get(); }
  constexpr object& operator*() const noexcept { return *_ptr; }

 private:
  std::shared_ptr<object> _ptr;
};

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
