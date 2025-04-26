#include "list.h"

#include <iostream>

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

void list::append(Any item) { _items.push_back(item); }

void list::sort(bool reverse) {
  std::sort(_items.begin(), _items.end(),
            [reverse](const ref& a, const ref& b) {
              return reverse ? a > b : a < b;
            });
}

ref type(const list&) {
  static const auto list_type = ::type("list", tuple{}, dict{
    {"append", function(&list::append)},
    {"sort", function(&list::sort)},
    {"__len__", function(&list::size)},
  });
  return list_type;
}
