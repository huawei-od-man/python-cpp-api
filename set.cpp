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

void set::remove(ref item) {
  if (!contains(item)) {
    throw KeyError("Item not in set");
  }
  _items.erase(item);
}

void set::clear() { _items.clear(); }

bool set::contains(ref item) const { return _items.find(item) != _items.end(); }
