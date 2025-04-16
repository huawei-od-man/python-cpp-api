#ifndef TYPE_H
#define TYPE_H

#include <iostream>

#include "forward.h"
#include "ref.h"
#include "str.h"

template <typename T>
class type {
 public:
  constexpr type() noexcept = default;

  static ref instance();

  template <typename... Args>
  ref operator()(Args&&... args);

  str name() const {
    if constexpr (std::is_same_v<T, void>) {
      return "type";
    } else {
      return get_type_name();
    }
  }

 private:
  std::string get_type_name() const {
    // Use __PRETTY_FUNCTION__ to get the type name in a more readable format
#ifdef __GNUC__
    std::string s = __PRETTY_FUNCTION__;
    size_t start = s.find("T = ");
    if (start != std::string::npos) {
      start += 4;  // Length of "T = "
      size_t end = s.find(']', start);
      return s.substr(start, end - start);
    }
    return "unknown";
#elif defined(_MSC_VER)
    std::string s = __FUNCSIG__;
    size_t start = s.find("T = ");
    if (start != std::string::npos) {
      start += 4;  // Length of "T = "
      size_t end = s.find('>', start);
      return s.substr(start, end - start);
    }
    return "unknown";
#else
    return typeid(T).name();
#endif
  }
};

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const type<T>& tp) {
  os << tp.name();
  return os;
}

template <typename T>
const ref type_instance = make_box<type<T>>();

template <typename T>
const ref type_instance<type<T>> = make_box<type<void>>();

template <typename T>
inline ref type<T>::instance() {
  return type_instance<T>;
}

#endif
