#ifndef REF_TCC
#define REF_TCC
#include <type_traits>

#include "bool.h"
#include "box.h"
#include "floating_point.h"
#include "int.h"
#include "ref.h"
#include "except.h"

template <>
inline ref make_box<bool, bool>(bool&& value) {
  return value ? True : False;
}

template <typename T, typename... Args>
ref make_box(Args&&... args) {
  if constexpr (std::is_floating_point<T>::value) {
    return ref(std::make_shared<box<float_>>(std::forward<Args>(args)...));
  } else if constexpr (std::is_same<T, bool>::value) {
    return ref(std::make_shared<box<bool_>>(std::forward<Args>(args)...));
  } else if constexpr (std::is_integral<T>::value) {
    return ref(std::make_shared<box<int_>>(std::forward<Args>(args)...));
  } else if constexpr (std::is_same_v<std::decay_t<T>, char*>) {
    return ref(std::make_shared<box<str>>(std::forward<Args>(args)...));
  } else if constexpr (std::is_base_of<object, T>::value) {
    return ref(std::make_shared<T>(std::forward<Args>(args)...));
  } else {
    return ref(std::make_shared<box<T>>(std::forward<Args>(args)...));
  }
}

template <typename T>
ref to_ref(T&& value) {
  using U = std::remove_cv_t<std::remove_reference_t<T>>;
  return make_box<U>(std::forward<T>(value));
}

template <typename T>
std::conditional_t<std::is_scalar_v<T>, T, T&> from_ref(ref& r) {
  if constexpr (std::is_same_v<T, ref>) {
    return r;
  } else if constexpr (std::is_same_v<T, bool>) {
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
