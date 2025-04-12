#ifndef FLOATING_POINT_H
#define FLOATING_POINT_H

#include <cfloat>

#include "forward.h"

class float_ {
 public:
  constexpr float_(long double value) noexcept : _value(value) {}
  constexpr float_(double value) noexcept : _value(value) {}
  constexpr float_(float value) noexcept : _value(value) {}

  constexpr float_() noexcept = default;
  ~float_() noexcept = default;
  constexpr float_(const float_&) noexcept = default;
  constexpr float_(float_&&) noexcept = default;
  constexpr float_& operator=(const float_&) noexcept = default;
  constexpr float_& operator=(float_&&) noexcept = default;

  constexpr operator long double() const noexcept { return _value; }

  friend bool operator==(const float_& lhs, const float_& rhs) {
    // LDBL_EPSILON
    return false;
  }

  constexpr operator double() const { return static_cast<double>(_value); }

  constexpr operator float() const { return static_cast<float>(_value); }

  constexpr long double value() const { return _value; }

  static constexpr float_ minimum() noexcept { return float_(LDBL_MIN); }
  static constexpr float_ maximum() noexcept { return float_(LDBL_MAX); }

 private:
  long double _value{};
};

inline float_ operator""_f(long double value) { return float_(value); }

#endif  // FLOATING_POINT_H
