#include "object.h"

#include "str.h"
#include "tuple.h"
#include "iter.h"

str object::to_str() const { return ""; }

float_type object::to_float() const {
  throw NotImplementedError("to_float method not implemented");
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

ref object::next() {
  throw NotImplementedError("next method not implemented");
}

const iterator object::begin() const {
  return get_iter();
}

const iterator object::end() const { return {}; }
