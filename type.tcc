#ifndef TYPE_TCC
#define TYPE_TCC
#include "type.h"

#include "bool.h"
#include "float.h"
#include "int.h"
#include "str.h"

template <typename T>
std::string get_type_name() {
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

template <typename T>
ref type(const T&) {
  if constexpr (std::is_same_v<T, bool>) {
    return ::type(bool_{});
  } else if constexpr (std::is_floating_point_v<T>) {
    return ::type(float_{});
  } else if constexpr (std::is_integral_v<T>) {
    return ::type(int_{});
  } else if constexpr (std::is_same_v<std::decay_t<T>, const char*>) {
    return ::type(str{});
  } else if constexpr (std::is_same_v<T, void>) {
    return ::type(NoneType{});
  } else {
    static const auto T_type = ::type(get_type_name<T>(), tuple{}, dict{});
    return T_type;
  }
}

#endif
