#ifndef INT_H
#define INT_H
#include <cstdint>
#include <ostream>

class int_ {
 public:
  constexpr int_() noexcept = default;
  ~int_() noexcept = default;

  constexpr int_(int value) noexcept : _value(value) {}
  constexpr int_(unsigned int value) noexcept : _value(value) {}
  constexpr int_(long value) noexcept : _value(value) {}
  constexpr int_(unsigned long value) noexcept : _value(value) {}
  constexpr int_(long long value) noexcept : _value(value) {}
  constexpr int_(unsigned long long value) noexcept : _value(value) {}

  constexpr int_(const int_&) noexcept = default;
  constexpr int_(int_&&) noexcept = default;
  constexpr int_& operator=(const int_&) noexcept = default;
  constexpr int_& operator=(int_&&) noexcept = default;

  constexpr explicit operator bool() const noexcept { return _value != 0; }
  constexpr explicit operator int64_t() const noexcept { return _value; }
  constexpr int64_t value() const noexcept { return _value; }
  constexpr explicit operator int() const noexcept {
    return static_cast<int>(_value);
  }
  constexpr explicit operator long double() const noexcept {
    return static_cast<long double>(_value);
  }
  constexpr explicit operator double() const noexcept {
    return static_cast<double>(_value);
  }

  friend std::ostream& operator<<(std::ostream& os, const int_& i) {
    return os << i._value;
  }

  friend bool operator==(const int_& lhs, const int_& rhs) {
    return lhs._value == rhs._value;
  }
  friend bool operator!=(const int_& lhs, const int_& rhs) {
    return lhs._value != rhs._value;
  }
  friend bool operator<(const int_& lhs, const int_& rhs) {
    return lhs._value < rhs._value;
  }
  friend bool operator<=(const int_& lhs, const int_& rhs) {
    return lhs._value <= rhs._value;
  }
  friend bool operator>(const int_& lhs, const int_& rhs) {
    return lhs._value > rhs._value;
  }
  friend bool operator>=(const int_& lhs, const int_& rhs) {
    return lhs._value >= rhs._value;
  }

 private:
  int64_t _value{0};
};

inline int_ operator""_i(unsigned long long value) {
  return int_(static_cast<int64_t>(value));
}

#endif
