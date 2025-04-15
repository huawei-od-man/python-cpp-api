#ifndef REF_H
#define REF_H

#include <memory>

#include "object.h"

class ref {
 public:
  ref();

  template <typename T>
  ref(T&& value);

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

  explicit operator bool() const { return static_cast<bool>(_ptr->to_bool()); }

  object& value() { return *_ptr; }
  const object& value() const { return *_ptr; }

  template <typename T>
  T& as();

  template <typename T>
  const T& as() const;

 private:
  std::shared_ptr<object> _ptr;
};

namespace std {
template <>
struct hash<::ref> {
  size_t operator()(const ::ref& r) const { return r->hash(); }
};
template <>
struct equal_to<::ref> {
  bool operator()(const ::ref& lhs, const ::ref& rhs) const {
    return lhs.value() == rhs.value();
  }
};

}  // namespace std

#endif  // REF_H
