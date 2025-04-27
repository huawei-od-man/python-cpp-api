#ifndef STR_H
#define STR_H
#include <string>
#include <iosfwd>

#include "forward.h"

class str {
 public:
  template <size_t N>
  str(const char (&str)[N]) : _string(str, N - 1) {}
  str(const char* str) : _string(str) {}
  str(std::string_view str) : _string(str) {}
  str(const std::string& str) : _string(str) {}
  str(std::string&& str) noexcept : _string(std::move(str)) {}
  str(ref obj);

  str() noexcept = default;
  ~str() = default;
  str(const str&) = default;
  str(str&&) noexcept = default;
  str& operator=(const str&) = default;
  str& operator=(str&&) noexcept = default;

  explicit operator bool() const { return !_string.empty(); }
  size_t size() const { return _string.size(); }

  str format(const tuple& args) const;

  const char* c_str() const { return _string.c_str(); }

  const std::string& value() const { return _string; }

  friend bool operator==(const str& lhs, const str& rhs) {
    return lhs._string == rhs._string;
  }

  friend bool operator<(const str& lhs, const str& rhs) {
    return lhs._string < rhs._string;
  }

  str operator*(size_t n) const;

  size_t hash() const {
    return std::hash<std::string>{}(_string);
  }

  str capitalize() const;

  str casefold() const;

  str center(int width, const str& fillchar = " ") const;

  size_t count(const str& sub, int start, int end) const;

  bool endswith(const str& suffix) const;

  str expandtabs(int tabsize = 8) const;

  list split(const str& sep) const;

  bool startswith(const str& prefix) const;

  int find(const str& sub, int start, int end) const;

  str format_map(ref mapping);

  int index(const str& sub, int start, int end) const;

  bool isalnum() const;

  bool isalpha() const;

  bool isascii() const;

  bool isdecimal() const;

  bool isdigit() const;

  bool isidentifier() const;

  bool islower() const;

  bool isnumeric() const;

  bool isprintable() const;

  bool isspace() const;

  bool istitle() const;

  bool isupper() const;

  str join(ref iterable) const;

  str ljust(int width, const str& fillchar = " ");

  str lower() const;

  str lstrip() const;

  str upper() const;

 private:

  std::string _string;
};

str operator""_s(const char* s, size_t size);

inline str operator+(const str& lhs, const str& rhs) {
  return str(lhs.value() + rhs.value());
}

std::ostream& operator<<(std::ostream& os, const str& obj);

#endif
