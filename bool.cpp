#include "bool.h"

#include "str.h"

bool_ *True, *False;

bool_::bool_(bool value) : _value(value) {}

bool_::~bool_() = default;

str bool_::__str__() { return new String(_value ? "True" : "False"); }

bool_ bool_::__bool__() { return ref<bool_>(this); }

bool_ bool_::__eq__(object other) { return True; }

bool_ bool_::__ne__(object other) {
  //   auto other_bool = other.is<Bool>();
  return False;
}
