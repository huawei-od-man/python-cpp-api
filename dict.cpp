#include "dict.h"

#include <ostream>

#include "except.h"
#include "tuple.h"
#include "str.h"

dict::dict() noexcept = default;

dict::~dict() noexcept = default;

ref& dict::operator[](Any key) {
    const auto it = _items.find(key);
    if (it != _items.end()) {
        return it->second;
    }
    throw KeyError("Key not found");
}

dict::dict(std::initializer_list<tuple> items) {
  for (const auto& item : items) {
    if (item.size() != 2) {
      throw ValueError("Dictionary items must be tuples of size 2");
    }
    _items[item[0]] = item[1];
  }
}

void dict::clear() { _items.clear(); }

bool dict::contains(ref item) const {
  return _items.find(item) != _items.end();
}
