#include "type.h"

#include <iostream>

#include "box.tcc"
#include "ref.tcc"
#include "hash.tcc"

typeinfo::typeinfo(const str& name, const tuple& bases, const dict& attrs)
    : _name(name), _bases(bases), _attrs(attrs) {}

ref type(const str& name, const tuple& bases, const dict& attrs) {
  return make_box<typeinfo>(name, bases, attrs);
}

ref type(const ref& obj) { return obj->type(); }

ref type(const typeinfo&) {
  static const auto type_type = type("type", {}, {});
  return type_type;
}

std::ostream& operator<<(std::ostream& os, const typeinfo& obj) {
  os << obj.name();
  return os;
}

str repr(const typeinfo& obj) { return "<class '" + obj.name() + "'>"; }

bool operator==(const typeinfo& lhs, const typeinfo& rhs) {
  return lhs.name() == rhs.name();
}

bool operator<(const typeinfo& lhs, const typeinfo& rhs) {
  return lhs.name() < rhs.name();
}
