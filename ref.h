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

  template <typename T>
  T& as();

  template <typename T>
  const T& as() const;

  template <typename... Args>
  ref operator()(Args&&... args);

 private:
  std::shared_ptr<object> _ptr;
};

inline std::ostream& operator<<(std::ostream& os, const ref& obj) {
  obj->format(os);
  return os;
}

bool operator==(ref lhs, ref rhs);
bool operator!=(ref lhs, ref rhs);
bool operator<(ref lhs, ref rhs);
bool operator<=(ref lhs, ref rhs);
bool operator>(ref lhs, ref rhs);
bool operator>=(ref lhs, ref rhs);

ref operator+(ref lhs, ref rhs);

namespace std {
template <>
struct hash<::ref> {
  size_t operator()(const ::ref& r) const noexcept { return r->hash(); }
};
}  // namespace std

#endif  // REF_H
