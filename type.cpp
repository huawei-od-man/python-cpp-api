#include "type.h"

#include <iostream>

#include "bool.h"
#include "box.tcc"
#include "floating_point.h"
#include "hash.tcc"
#include "int.h"
#include "ref.tcc"
#include "function.tcc"

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

ref type(const float_&) {
  static const auto float_type = ::type("float", tuple{}, dict{});
  return float_type;
}

ref type(const int_&) {
  static const auto int_type = ::type("int", tuple{}, dict{});
  return int_type;
}

ref type(const list&) {
  static const auto list_type = ::type("list", tuple{},
                                       dict{
                                           {"append", function(&list::append)},
                                           {"sort", function(&list::sort)},
                                           {"__len__", function(&list::size)},
                                       });
  return list_type;
}

ref type(const tuple&) {
  static const auto tuple_type = ::type("tuple", tuple{}, dict{});
  return tuple_type;
}

ref type(const dict&) {
  static const auto dict_type = ::type("dict", tuple{}, dict{});
  return dict_type;
}

ref type(const set &) {
  static const auto set_type = ::type("set", tuple{}, dict{});
  return set_type;
}

ref type(const str&) {
  static const auto str_type = ::type("str", {}, {});
  return str_type;
}
