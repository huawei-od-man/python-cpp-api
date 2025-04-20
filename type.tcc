#ifndef TYPE_TCC
#define TYPE_TCC
#include "type.h"

#include "tuple.h"
#include "dict.h"
#include "bool.h"
#include "float.h"
#include "int.h"
#include "str.h"

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
  } else {
    static const auto T_type = ::type(get_type_name<T>(), tuple{}, dict{});
    return T_type;
  }
}

#endif
