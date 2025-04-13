#include "set.h"

#include <ostream>

std::ostream& operator<<(std::ostream& os, const set& obj) {
  os << "{";
  size_t i = 0;
  for (const auto& item : obj._items) {
    os << *item << (i < obj._items.size() - 1 ? ", " : "");
    ++i;
  }
  os << "}";
  return os;
}
