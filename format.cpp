#include "python.h"

#include <ostream>

std::ostream& operator<<(std::ostream& os, const str& obj) {
  os << obj.value();
  return os;
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

std::ostream& operator<<(std::ostream& os, const tuple& obj) {
  os << "(";
  for (size_t i = 0; i < obj.size(); ++i) {
    if (i > 0) {
      os << ", ";
    }
    os << obj[i];
  }
  os << ")";
  return os;
}

std::ostream& operator<<(std::ostream& os, const dict& obj) {
  os << "{";
  size_t i = 0;
  for (const auto& [key, value] : obj._items) {
    os << key << ": " << value << (i < obj._items.size() - 1 ? ", " : "");
    ++i;
  }
  os << "}";
  return os;
}

std::ostream& operator<<(std::ostream& os, const set& obj) {
  os << "{";
  size_t i = 0;
  for (const auto& item : obj._items) {
    os << item << (i < obj._items.size() - 1 ? ", " : "");
    ++i;
  }
  os << "}";
  return os;
}

std::ostream& operator<<(std::ostream& os, const typeinfo& obj) {
  os << obj.name();
  return os;
}

std::ostream& operator<<(std::ostream& os, const function& obj) {
  return os << "<" << type(obj) << ">";
}

std::ostream& operator<<(std::ostream& os, const object& obj) {
  obj.format(os);
  return os;
}
