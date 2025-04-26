#include "str.h"

#include <cctype>
#include <sstream>

#include "box.tcc"
#include "except.h"
#include "list.h"
#include "object.h"
#include "ref.tcc"
#include "tuple.h"
#include "type.h"

str::str(ref obj) : str(obj->to_str()) {}

str str::format(const tuple& args) const {
  std::ostringstream oss;
  size_t index = 0;
  for (size_t i = 0; i < _string.size(); ++i) {
    if (_string[i] == '{' && i + 1 < _string.size() && _string[i + 1] == '}') {
      if (index >= args.size()) {
        throw IndexError("Index out of range");
      }
      oss << args[index++];
      ++i;
    } else {
      oss << _string[i];
    }
  }
  return str(oss.str());
}

ref type(const str&) {
  static const auto str_type = ::type("str", {}, {});
  return str_type;
}

str operator""_s(const char* s, size_t size) {
  return str(std::string_view(s, size));
}

// 字符串操作
str str::capitalize() const {
  if (_string.empty()) return *this;
  std::string result = _string;
  result[0] = toupper(result[0]);
  for (size_t i = 1; i < result.size(); ++i) {
    result[i] = tolower(result[i]);
  }
  return result;
}

str str::casefold() const {
  std::string result = _string;
  for (char& c : result) {
    c = tolower(c);
  }
  return result;
}

str str::center(int width, const str& fillchar) const {
  if (width <= static_cast<int>(_string.size())) return *this;
  int padding = width - static_cast<int>(_string.size());
  int left = padding / 2;
  int right = padding - left;
  return fillchar * left + *this + fillchar * right;
}

size_t str::count(const str& sub, int start = 0, int end = -1) const {
  if (sub._string.empty()) return 0;
  size_t count = 0;
  size_t pos = (start >= 0) ? start : 0;
  size_t end_pos = (end >= 0 && end < static_cast<int>(_string.size()))
                       ? end
                       : _string.size();

  while (pos < end_pos) {
    pos = _string.find(sub._string, pos);
    if (pos == std::string::npos || pos >= end_pos) break;
    ++count;
    pos += sub._string.size();
  }
  return count;
}

bool str::endswith(const str& suffix) const {
  if (suffix._string.size() > _string.size()) return false;
  return _string.substr(_string.size() - suffix._string.size()) ==
         suffix._string;
}

str str::expandtabs(int tabsize) const {
  std::string result;
  result.reserve(_string.size());
  size_t col = 0;

  for (char c : _string) {
    if (c == '\t') {
      int spaces = tabsize - (col % tabsize);
      result.append(spaces, ' ');
      col += spaces;
    } else {
      result += c;
      ++col;
      if (c == '\n') col = 0;
    }
  }
  return result;
}

list str::split(const str& sep) const {
  list result;
  if (sep._string.empty()) {
    // 分割每个字符
    for (char c : _string) {
      result.append(to_ref(str(std::string(1, c))));
    }
    return result;
  }

  size_t start = 0;
  size_t end = _string.find(sep._string);
  while (end != std::string::npos) {
    result.append(to_ref(str(_string.substr(start, end - start))));
    start = end + sep._string.size();
    end = _string.find(sep._string, start);
  }
  result.append(to_ref(str(_string.substr(start))));
  return result;
}

bool str::startswith(const str& prefix) const {
  if (prefix._string.size() > _string.size()) return false;
  return _string.substr(0, prefix._string.size()) == prefix._string;
}

int str::find(const str& sub, int start = 0, int end = -1) const {
  size_t start_pos = (start >= 0) ? start : 0;
  size_t end_pos = (end >= 0 && end < static_cast<int>(_string.size()))
                       ? end
                       : _string.size();

  if (start_pos >= _string.size() || sub._string.empty()) return -1;

  size_t pos = _string.find(sub._string, start_pos);
  if (pos == std::string::npos || pos + sub._string.size() > end_pos) {
    return -1;
  }
  return static_cast<int>(pos);
}

int str::index(const str& sub, int start = 0, int end = -1) const {
  int pos = find(sub, start, end);
  if (pos == -1) throw std::out_of_range("substring not found");
  return pos;
}

bool str::isalnum() const {
  if (_string.empty()) return false;
  for (char c : _string) {
    if (!::isalnum(c)) return false;
  }
  return true;
}

bool str::isalpha() const {
  if (_string.empty()) return false;
  for (char c : _string) {
    if (!::isalpha(c)) return false;
  }
  return true;
}

bool str::isascii() const {
  for (char c : _string) {
    if (static_cast<unsigned char>(c) > 127) return false;
  }
  return true;
}

bool str::isdecimal() const {
  if (_string.empty()) return false;
  for (char c : _string) {
    if (!::isdigit(c)) return false;
  }
  return true;
}

bool str::isdigit() const { return isdecimal(); }

bool str::isidentifier() const {
  if (_string.empty()) return false;
  if (!::isalpha(_string[0])) return false;
  for (char c : _string) {
    if (!::isalnum(c) && c != '_') return false;
  }
  return true;
}

bool str::islower() const {
  if (_string.empty()) return false;
  for (char c : _string) {
    if (::isalpha(c) && !::islower(c)) return false;
  }
  return true;
}

bool str::isnumeric() const { return isdecimal(); }

bool str::isprintable() const {
  for (char c : _string) {
    if (!isprint(c)) return false;
  }
  return true;
}

bool str::isspace() const {
  if (_string.empty()) return false;
  for (char c : _string) {
    if (!::isspace(c)) return false;
  }
  return true;
}

bool str::istitle() const {
  if (_string.empty()) return false;
  bool new_word = true;
  for (char c : _string) {
    if (new_word) {
      if (!::isupper(c)) return false;
      new_word = false;
    } else {
      if (::isupper(c)) return false;
    }
    if (!::isalpha(c)) new_word = true;
  }
  return true;
}

bool str::isupper() const {
  if (_string.empty()) return false;
  for (char c : _string) {
    if (::isalpha(c) && !::isupper(c)) return false;
  }
  return true;
}

// str str::join(ref iterable) const {
// 简化实现，假设iterable是list<str>
// std::string result;
// bool first = true;
// for (const auto& item : iterable) {
//     if (!first) result += _string;
//     result += item.value();  // 假设item有value()方法
//     first = false;
// }
// return result;
// }

// str str::ljust(int width, const str& fillchar) {
//   if (width <= static_cast<int>(_string.size())) return *this;
//   return *this + str(fillchar._string * (width - _string.size()));
// }

str str::lower() const { return casefold(); }

str str::lstrip() const {
  size_t start = 0;
  while (start < _string.size() && ::isspace(_string[start])) {
    ++start;
  }
  return str(_string.substr(start));
}

str str::upper() const {
  std::string result = _string;
  for (char& c : result) {
    c = toupper(c);
  }
  return result;
}

// 辅助函数：字符串重复
str str::operator*(size_t n) const {
  std::string result;
  result.reserve(size() * n);
  for (size_t i = 0; i < n; ++i) {
    result += value();
  }
  return result;
}
