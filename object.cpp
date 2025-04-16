#include "object.h"

#include <sstream>

#include "except.h"
#include "floating_point.h"
#include "iter.h"
#include "ref.h"
#include "str.h"
#include "tuple.h"
#include "type.h"
#include "box.h"  // make_box()

str object::to_str() const {
  std::ostringstream oss;
  format(oss);
  return oss.str();
}

float_ object::to_float() const {
  throw NotImplementedError("to_float method not implemented");
}

bool object::eq(ref other) const { return this == other.get(); }

bool object::neq(ref other) const { return this != other.get(); }

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
  os << "<" << type() << " object at " << this << ">";
}

std::ostream& operator<<(std::ostream& os, const object& obj) {
  obj.format(os);
  return os;
}

ref object::type() const {
  return ::type<object>::instance();
}
