#include "set.h"

#include <ostream>

#include "str.h"
#include "ref.h"
#include "tuple.h"
#include "dict.h"

set::set(std::initializer_list<Any> items) {
  for (const auto& item : items) {
    _items.insert(item);
  }
}

std::ostream& operator<<(std::ostream& os, const set& obj) {
  os << "{";
  size_t i = 0;
  for (const auto& item : obj._items) {
    os << item << (i < obj._items.size() - 1 ? ", " : "");
    ++i;
  }
  os << "}";
  return os;
}

ref type(const set &) {
  static const auto set_type = ::type("set", tuple{}, dict{});
  return set_type;
}
