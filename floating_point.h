#ifndef FLOATING_POINT_H
#define FLOATING_POINT_H
#include <cfloat>
#include <iostream>
#include <utility>

class ref;

class float_ {
 public:
  constexpr explicit float_(long double value) noexcept : _value(value) {}
  constexpr explicit float_(double value) noexcept : _value(value) {}
  constexpr explicit float_(float value) noexcept : _value(value) {}
  float_(ref obj);

  constexpr float_() noexcept = default;
  ~float_() noexcept = default;

  constexpr float_(const float_&) noexcept = default;
  constexpr float_(float_&&) noexcept = default;
  constexpr float_& operator=(const float_&) noexcept = default;
  constexpr float_& operator=(float_&&) noexcept = default;

  constexpr explicit operator long double() const noexcept { return _value; }
  constexpr explicit operator double() const {
    return static_cast<double>(_value);
  }

  constexpr explicit operator float() const {
    return static_cast<float>(_value);
  }

  constexpr long double value() const noexcept { return _value; }
  float_ operator-() const;

  static constexpr float_ minimum() noexcept { return float_(LDBL_MIN); }
  static constexpr float_ maximum() noexcept { return float_(LDBL_MAX); }
  static constexpr float_ epsilon() noexcept { return float_(LDBL_EPSILON); }

 private:
  long double _value{};
};

inline float_ operator""_f(long double value) { return float_(value); }

std::ostream& operator<<(std::ostream& os, const float_& f);

float_ operator/(const float_& lhs, const float_& rhs);
float_ operator+(const float_& lhs, const float_& rhs);
float_ operator-(const float_& lhs, const float_& rhs);
float_ operator*(const float_& lhs, const float_& rhs);

bool operator==(const float_& lhs, const float_& rhs);
bool operator<(const float_& lhs, const float_& rhs);

#endif  // FLOATING_POINT_H
