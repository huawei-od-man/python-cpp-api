#ifndef REF_H
#define REF_H

#include <memory>
#include <iosfwd>

#include "object.h"

class ref {
 public:
  ref();

  explicit ref(Any&& value) noexcept;

  explicit ref(std::shared_ptr<object> ptr) noexcept : _ptr(std::move(ptr)) {}

  template <typename T>
  explicit ref(std::shared_ptr<box<T>> box_ptr) noexcept
      : _ptr(std::move(box_ptr)) {}

  ref(const ref&) noexcept = default;
  ref(ref&&) noexcept = default;
  ref& operator=(const ref&) noexcept = default;
  ref& operator=(ref&&) noexcept = default;

  constexpr object* operator->() const noexcept { return _ptr.get(); }

  explicit operator bool() const { return static_cast<bool>(_ptr->to_bool()); }

  std::shared_ptr<object> value() const noexcept { return _ptr; }
  const object* get() const noexcept { return _ptr.get(); }

  bool operator==(const ref& other) const;
  bool operator!=(const ref& other) const;

  bool operator<(const ref& other) const;
  bool operator>(const ref& other) const;

  friend std::ostream& operator<<(std::ostream& os, const ref& r);

  template <typename... Args>
  ref operator()(Args&&... args) {
    return _ptr->call(tuple(std::forward<Args>(args)...));
  }

 private:
  std::shared_ptr<object> _ptr;
};

struct Any {
  template <typename T>
  Any(T&& value) : r(to_ref(std::forward<T>(value))) {}

  Any(const Any&) noexcept = default;
  Any(Any&&) noexcept = default;
  Any(Any&) noexcept;
  Any(const Any&&) noexcept;

  Any(ref r) : r(r) {}

  operator ref() const { return r; }

  ref r;
};

namespace std {
template <>
struct hash<::ref> {
  size_t operator()(const ::ref& r) const { return r->hash(); }
};

}  // namespace std

#endif  // REF_H
