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
