#include "list.h"

#include <iostream>
#include <algorithm> // sort

#include "except.h"
#include "tuple.h"
#include "dict.h"
#include "function.tcc"
#include "box.tcc"

list::list(std::initializer_list<Any> items) {
  _items.reserve(items.size());
  for (const auto& item : items) {
    _items.push_back(item);
  }
}

std::ostream& operator<<(std::ostream& os, const list& lst) {
  os << "[";
  for (size_t i = 0; i < lst.size(); ++i) {
    if (i > 0) {
      os << ", ";
    }
    os << lst[i];
  }
  os << "]";
  return os;
}

ref& list::operator[](size_t index) {
  if (index >= _items.size()) {
    throw IndexError("Index out of range");
  }
  return _items[index];
}

const ref& list::operator[](size_t index) const {
  if (index >= _items.size()) {
    throw IndexError("Index out of range");
  }
  return _items[index];
}

void list::append(ref item) { _items.push_back(item); }

void list::sort(bool reverse) {
  std::sort(_items.begin(), _items.end(),
            [reverse](const ref& a, const ref& b) {
              return reverse ? a > b : a < b;
            });
}
