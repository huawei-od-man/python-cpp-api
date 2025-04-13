#include "dict.h"

#include <ostream>

#include "except.h"
#include "ref.h"
#include "tuple.h"

ref& dict::operator[](ref key) {
    auto it = _map.find(key);
    if (it != _map.end()) {
        return it->second;
    }
    throw KeyError("Key not found");
}

std::ostream& operator<<(std::ostream& os, const dict& obj) {
  os << "{";
  size_t i = 0;
  for (const auto& [key, value] : obj._map) {
    os << *key << ": " << *value << (i < obj._map.size() - 1 ? ", " : "");
    ++i;
  }
  os << "}";
  return os;
}

dict::dict(std::initializer_list<tuple> items) {
  for (const auto& item : items) {
    if (item.size() != 2) {
      throw ValueError("Dictionary items must be tuples of size 2");
    }
    _map[item[0]] = item[1];
  }
}
