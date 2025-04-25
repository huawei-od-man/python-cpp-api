#ifndef HASH_TCC
#define HASH_TCC
#include <type_traits>

#include "ref.h"

// Primary template: Default case, assumes no specialization exists
template <typename T, typename = void>
struct has_specialized_hash : std::false_type {};

// Specialization: Checks if std::hash<T> is well-formed
template <typename T>
struct has_specialized_hash<T,
                            std::void_t<decltype(std::declval<std::hash<T>>()(
                                std::declval<const T&>()))>> : std::true_type {
};

template <typename T>
size_t hash(const T& value) {
  if constexpr (std::is_same_v<T, bool_> || std::is_same_v<T, float_> ||
                std::is_same_v<T, int_> || std::is_same_v<T, str>) {
    return ::hash(value.value());
  } else if constexpr (has_specialized_hash<T>::value) {
    return std::hash<T>{}(value);
  } else {
    return ::hash(&value);
  }
}

#endif
