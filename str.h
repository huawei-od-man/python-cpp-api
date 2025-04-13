#ifndef STR_H
#define STR_H
#include <string>

#include "forward.h"

class str {
 public:
  template <size_t N>
  str(const char (&str)[N]) : _string(str, N - 1) {}
  str(const char* str) : _string(str) {}
  str(std::string_view str) noexcept : _string(str) {}
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

  str format(tuple args) const;

  template <typename... Args>
  str format(Args&&... args) const;

  const char* c_str() const { return _string.c_str(); }

  friend std::ostream& operator<<(std::ostream& os, const str& obj) {
    os << obj._string;
    return os;
  }
 private:
  std::string _string;
};

inline str operator""_s(const char* s, size_t) {
  return str(s);
}

#endif
