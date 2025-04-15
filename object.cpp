#include "object.h"

#include "except.h"
#include "floating_point.h"
#include "iter.h"
#include "str.h"
#include "tuple.h"
#include "type.h"
#include "ref.h"

str object::to_str() const { return ""; }

float_ object::to_float() const {
  throw NotImplementedError("to_float method not implemented");
}

bool object::eq(ref other) const { return this == &other.value(); }

bool object::neq(ref other) const { return this != &other.value(); }

bool object::lt(ref other) const {
  throw NotImplementedError("lt method not implemented");
}

size_t object::size() const {
  throw NotImplementedError("size method not implemented");
}

ref object::call(tuple args) {
  throw NotImplementedError("call method not implemented");
}

iterator object::get_iter() const {
  throw NotImplementedError("get_iter method not implemented");
}

ref object::next() { throw NotImplementedError("next method not implemented"); }

const iterator object::begin() const { return get_iter(); }

const iterator object::end() const { return {}; }

ref object::add(ref other) const {
  throw NotImplementedError("add method not implemented");
}

ref object::sub(ref other) const {
  throw NotImplementedError("sub method not implemented");
}
ref object::mul(ref other) const {
  throw NotImplementedError("mul method not implemented");
}
ref object::div(ref other) const {
  throw NotImplementedError("div method not implemented");
}

void object::format(std::ostream& os) const {
  os << "<" << type_name() << " object at " << this << ">";
}

std::ostream& operator<<(std::ostream& os, const object& obj) {
  obj.format(os);
  return os;
}

bool operator==(const object& lhs, const object& rhs) {
  return lhs.eq(rhs);
}
bool operator!=(const object& lhs, const object& rhs) {
  return lhs.neq(rhs);
}
