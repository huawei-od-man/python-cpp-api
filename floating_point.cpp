#include "floating_point.h"

#include <cmath>
#include <iostream>

#include "dict.h"
#include "except.h"
#include "ref.h"
#include "str.h"
#include "tuple.h"

float_::float_(ref obj) : float_(obj->to_float()) {}

std::ostream& operator<<(std::ostream& os, const float_& f) {
  os << f.value();
  return os;
}

bool operator==(const float_& lhs, const float_& rhs) {
  return lhs.value() == rhs.value();
}

bool operator<(const float_& lhs, const float_& rhs) {
  return lhs.value() < rhs.value();
}

float_ operator+(const float_& lhs, const float_& rhs) {
  return float_(lhs.value() + rhs.value());
}

float_ operator-(const float_& lhs, const float_& rhs) {
  return float_(lhs.value() - rhs.value());
}

float_ operator*(const float_& lhs, const float_& rhs) {
  return float_(lhs.value() * rhs.value());
}

float_ operator/(const float_& lhs, const float_& rhs) {
  if (rhs.value() == 0.0) {
    throw ZeroDivisionError("division by zero");
  }
  return float_(lhs.value() / rhs.value());
}

float_ float_::operator-() const { return float_() - *this; }
