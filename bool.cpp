#include "bool.h"

#include "str.h"

Bool *True, *False;

Bool::Bool(bool value) : _value(value) {}

Bool::~Bool() = default;

str Bool::__str__() { return new String(_value ? "True" : "False"); }

bool_ Bool::__bool__() { return ref<Bool>(this); }

bool_ Bool::__eq__(object other) { return True; }

bool_ Bool::__ne__(object other) {
  //   auto other_bool = other.is<Bool>();
  return False;
}
