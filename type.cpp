#include "type.h"

#include <iostream>

#include "box.tcc"
#include "hash.tcc"
#include "ref.tcc"

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

ref type(const NoneType&) {
  static const auto NoneType_type = ::type("NoneType", tuple{}, dict{});
  return NoneType_type;
}

ref type(const bool_&) {
  static const auto bool_type = ::type("bool", tuple{}, dict{});
  return bool_type;
}
