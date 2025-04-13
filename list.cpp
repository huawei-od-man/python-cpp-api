#include "list.h"
#include <iostream>

#include "except.h"


std::ostream& operator<<(std::ostream& os, const list& lst) {
  os << "[";
  for (size_t i = 0; i < lst.size(); ++i) {
    if (i > 0) {
      os << ", ";
    }
    os << *lst[i];
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
