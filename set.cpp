#include "set.h"

#include <ostream>

#include "except.h"
#include "ref.h"
#include "str.h"

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

void set::remove(ref item) {
  if (!contains(item)) {
    throw KeyError("Item not in set");
  }
  _items.erase(item);
}

void set::clear() { _items.clear(); }

bool set::contains(ref item) const { return _items.find(item) != _items.end(); }
