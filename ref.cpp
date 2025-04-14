#include "ref.h"

#include "bool.h"
#include "box.h"
#include "except.h"
#include "none.h"

const ref None{make_box<NoneType>()};
const ref True{make_box<bool_>(true)};
const ref False{make_box<bool_>(false)};

ref::ref() : ref(None) {}

ref operator+(ref lhs, ref rhs) {
  try {
    return lhs->add(rhs);
  } catch (NotImplementedError&) {
    return rhs->add(lhs);
  }
}

bool operator==(ref lhs, ref rhs) {
  return lhs->eq(*rhs);
}
bool operator!=(ref lhs, ref rhs) {
  return !(lhs == rhs);
}
bool operator<(ref lhs, ref rhs) {
  return lhs->lt(*rhs);
}
bool operator<=(ref lhs, ref rhs) {
  return !(lhs > rhs);
}
bool operator>(ref lhs, ref rhs) {
  return rhs < lhs;
}
bool operator>=(ref lhs, ref rhs) {
  return !(lhs < rhs);
}
