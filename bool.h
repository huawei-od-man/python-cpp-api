#ifndef BOOL_H
#define BOOL_H

#include <ostream>
#include <utility>

class ref;

class bool_ {
 public:
  bool_(ref obj);

  constexpr explicit bool_(bool value) noexcept : _value(value) {}
  constexpr bool_() noexcept = default;
  ~bool_() noexcept = default;

  constexpr bool_(const bool_&) noexcept = default;
  constexpr bool_(bool_&&) noexcept = default;
  constexpr bool_& operator=(const bool_&) noexcept = default;
  constexpr bool_& operator=(bool_&&) noexcept = default;
  constexpr explicit operator bool() const noexcept { return value(); }
  constexpr bool value() const noexcept { return _value; }

  constexpr bool operator!() const noexcept { return !value(); }
  constexpr bool operator==(const bool_& other) const noexcept {
    return value() == other.value();
  }
  constexpr bool operator!=(const bool_& other) const noexcept {
    return value() != other.value();
  }
  constexpr bool operator==(bool other) const noexcept {
    return value() == other;
  }
  constexpr bool operator!=(bool other) const noexcept {
    return value() != other;
  }
  friend std::ostream& operator<<(std::ostream& os, const bool_& b) {
    return os << (b.value() ? "True" : "False");
  }

 private:
  bool _value{false};
};

namespace std {
template <>
struct hash<bool_> {
  size_t operator()(const bool_& b) const noexcept {
    return std::hash<bool>{}(b.value());
  }
};
}  // namespace std

#endif
