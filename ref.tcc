#ifndef REF_TCC
#define REF_TCC
#include <type_traits>

#include "box.h"
#include "ref.h"

template <typename T>
ref to_ref(T&& value) {
  using U = std::remove_cv_t<std::remove_reference_t<T>>;
  return make_box<U>(std::forward<T>(value));
}

template <typename T>
std::conditional_t<std::is_scalar_v<T>, T, T&> from_ref(ref& r) {
  if constexpr (std::is_same_v<T, bool>) {
    if (auto ptr = std::dynamic_pointer_cast<box<bool_>>(r.value())) {
      return static_cast<T>(ptr->value());
    }
  } else if constexpr (std::is_integral_v<T>) {
    if (auto ptr = std::dynamic_pointer_cast<box<int_>>(r.value())) {
      return static_cast<T>(ptr->value());
    }
  } else if constexpr (std::is_floating_point_v<T>) {
    if (auto ptr = std::dynamic_pointer_cast<box<float_>>(r.value())) {
      return static_cast<T>(ptr->value());
    }
  } else if constexpr (std::is_base_of_v<object, T>) {
    if (auto ptr = std::dynamic_pointer_cast<T>(r.value())) {
      return *ptr;
    }
  } else {
    if (auto ptr = std::dynamic_pointer_cast<box<T>>(r.value())) {
      return ptr->value();
    }
  }
  throw TypeError("Invalid type conversion");
}

template <typename T>
std::conditional_t<std::is_scalar_v<T>, T, const T&> from_ref(const ref& r) {
  return from_ref<T>(const_cast<ref&>(r));
}

#endif
