#include "tuple.h"

#include "list.h"
#include "except.h"

tuple::tuple(std::initializer_list<ref> items) {
  _items.reserve(items.size());
  for (const auto& item : items) {
    _items.push_back(item);
  }
}

tuple::tuple(const list &items) {
  _items.reserve(items.size());
  for (size_t i = 0; i < items.size(); ++i) {
    _items.push_back(items[i]);
  }
}

const ref& tuple::operator[](size_t index) const {
  if (index >= _items.size()) {
    throw IndexError("Index out of range");
  }
  return _items[index];
}

