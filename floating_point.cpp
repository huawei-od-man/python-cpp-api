#include "floating_point.h"

#include "except.h"
#include "ref.h"

float_ operator/(const float_& lhs, const float_& rhs) {
  if (rhs.value() == 0.0) {
    throw ZeroDivisionError("division by zero");
  }
  return float_(lhs.value() / rhs.value());
}

float_::float_(ref obj) : float_(obj->to_float()) {}

bool operator==(const float_& lhs, const float_& rhs) {
  return std::fabs(lhs.value() - rhs.value()) < float_::epsilon().value();
}

bool operator<(const float_& lhs, const float_& rhs) {
  return lhs.value() < rhs.value() + float_::epsilon().value();
}

float_ operator+(const float_& lhs, const float_& rhs) {
  if (lhs.value() > float_::maximum().value() - rhs.value()) {
    throw OverflowError("float addition overflow");
  }
  return float_(lhs.value() + rhs.value());
}

float_ operator-(const float_& lhs, const float_& rhs) {
  if (lhs.value() < float_::minimum().value() + rhs.value()) {
    throw UnderflowError("float subtraction underflow");
  }
  return float_(lhs.value() - rhs.value());
}

float_ operator*(const float_& lhs, const float_& rhs) {
  if (lhs.value() > float_::maximum().value() / rhs.value()) {
    throw OverflowError("float multiplication overflow");
  }
  return float_(lhs.value() * rhs.value());
}

float_ float_::operator-() const { return float_() - *this; }
