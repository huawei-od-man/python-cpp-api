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

std::ostream& operator<<(std::ostream& os, const tuple& obj) {
  os << "(";
  for (size_t i = 0; i < obj.size(); ++i) {
    if (i > 0) {
      os << ", ";
    }
    os << obj[i].value();
  }
  os << ")";
  return os;
}

tuple operator+(const tuple& lhs, const tuple& rhs) {
  tuple result;
  result._items.reserve(lhs.size() + rhs.size());
  for (size_t i = 0; i < lhs.size(); ++i) {
    result._items.push_back(lhs[i]);
  }
  for (size_t i = 0; i < rhs.size(); ++i) {
    result._items.push_back(rhs[i]);
  }
  return result;
}

bool operator==(const tuple& lhs, const tuple& rhs) noexcept {
  if (lhs.size() != rhs.size()) {
    return false;
  }
  for (size_t i = 0; i < lhs.size(); ++i) {
    if (lhs[i].value() != rhs[i].value()) {
      return false;
    }
  }
  return true;
}
