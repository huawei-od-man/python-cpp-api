#include "tuple.h"

#include <utility>
#include <iostream>

#include "dict.h"
#include "except.h"
#include "list.h"
#include "set.h"
#include "str.h"

tuple::tuple(std::initializer_list<Any> items) {
  _items.reserve(items.size());
  for (const auto& item : items) {
    _items.push_back(item);
  }
}

tuple::tuple(const list& items) {
  _items.reserve(items.size());
  for (size_t i = 0; i < items.size(); ++i) {
    _items.push_back(items[i]);
  }
}

ref& tuple::operator[](size_t index) const {
  if (index >= _items.size()) {
    throw IndexError("Index out of range");
  }
  return const_cast<ref&>(_items[index]);
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
    if (lhs[i] != rhs[i]) {
      return false;
    }
  }
  return true;
}

bool operator<(const tuple& lhs, const tuple& rhs) noexcept {
  std::less<std::vector<ref>> less;
  return less(lhs._items, rhs._items);
}

bool operator>(const tuple& lhs, const tuple& rhs) noexcept {
  return rhs < lhs;
}
bool operator<=(const tuple& lhs, const tuple& rhs) noexcept {
  return !(lhs > rhs);
}
bool operator>=(const tuple& lhs, const tuple& rhs) noexcept {
  return !(lhs < rhs);
}
bool operator!=(const tuple& lhs, const tuple& rhs) noexcept {
  return !(lhs == rhs);
}

tuple tuple::slice(size_t start, size_t end) const {
  if (end == -1) {
    end = size();
  }
  if (start >= size() || end > size() || start > end) {
    return {};
  }
  tuple result;
  result._items.reserve(end - start);
  for (size_t i = start; i < end; ++i) {
    result._items.push_back(_items[i]);
  }
  return result;
}
