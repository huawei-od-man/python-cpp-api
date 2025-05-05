#ifndef BOX_TCC
#define BOX_TCC
#include "bool.h"
#include "box.h"
#include "dict.h"
#include "except.h"
#include "floating_point.h"
#include "function.h"
#include "int.h"
#include "list.h"
#include "none.h"
#include "object.h"
#include "ref.h"
#include "set.h"
#include "str.h"
#include "tuple.h"
#include "type.tcc"
#include "hash.tcc"

template <typename T, typename = void>
struct has_bool_method : std::false_type {};

template <typename T>
struct has_bool_method<T, std::void_t<decltype(static_cast<bool>(std::declval<const T&>()))>>
    : std::true_type {};

template <typename T, typename = void>
struct has_call_method : std::false_type {};

template <typename T>
struct has_call_method<T, std::void_t<decltype(&T::operator())>>
    : std::true_type {};

template <typename T, typename = void>
struct has_type_method : std::false_type {};

template <typename T>
struct has_type_method<T, std::void_t<decltype(T::type())>>
    : std::is_same<decltype(T::type()), ref> {};

template <typename T, typename = void>
struct has_lt_method : std::false_type {};

template <typename T>
struct has_lt_method<
    T, std::void_t<decltype(std::declval<T>() < std::declval<T>())>>
    : std::true_type {};

template <typename T, typename = void>
struct has_add_method : std::false_type {};

template <typename T>
struct has_add_method<
    T, std::void_t<decltype(std::declval<T>() + std::declval<T>())>>
    : std::true_type {};

template <typename T, typename = void>
struct has_eq_method : std::false_type {};

template <typename T>
struct has_eq_method<
    T, std::void_t<decltype(std::declval<T>() == std::declval<T>())>>
    : std::true_type {};

// 检查 T 是否有一个返回类型为 size_t 的 size() 方法
template <typename T, typename = void>
struct has_size_method : std::false_type {};

template <typename T>
struct has_size_method<T, std::void_t<decltype(std::declval<T>().size())>>
    : std::is_same<decltype(std::declval<T>().size()), std::size_t> {};

template <typename T, typename = void>
struct has_operator_insertion : std::false_type {};

template <typename T>
struct has_operator_insertion<
    T,
    std::void_t<decltype(std::declval<std::ostream&>() << std::declval<T>())>>
    : std::true_type {};

template <typename T>
ref box<T>::type() const {
  return ::type(_value);
}

template <typename T>
std::size_t box<T>::size() const {
  if constexpr (has_size_method<T>::value) {
    return _value.size();
  } else {
    return object::size();
  }
}

template <typename T>
void box<T>::format(std::ostream& os) const {
  if constexpr (has_operator_insertion<T>::value) {
    os << _value;
  } else {
    object::format(os);
  }
}

template <typename T>
bool box<T>::to_bool() const {
  if constexpr (has_bool_method<T>::value) {
    return static_cast<bool>(_value);
  } else {
    return object::to_bool();
  }
}

template <typename T>
float_ box<T>::to_float() const {
  if constexpr (std::is_same<T, float_>::value) {
    return _value;
  } else {
    return object::to_float();
  }
}

template <typename T>
ref box<T>::add(ref other) const {
  if constexpr (has_add_method<T>::value) {
    return to_ref(_value + from_ref<T>(other));
  } else {
    return object::add(other);
  }
}

template <typename T>
std::size_t box<T>::hash() const {
  try {
    return ::hash(_value);
  } catch (NotImplementedError&) {
    return object::hash();
  }
}

template <typename T>
bool box<T>::eq(ref other) const {
  if constexpr (has_eq_method<T>::value) {
    try {
      return _value == from_ref<T>(other);
    } catch (const TypeError&) {
      return object::eq(other);
    }
  } else {
    return object::eq(other);
  }
}

template <typename T>
bool box<T>::lt(ref other) const {
  if constexpr (has_lt_method<T>::value) {
    try {
      return _value < from_ref<T>(other);
    } catch (const TypeError&) {
      return object::lt(other);
    }
  } else {
    return object::lt(other);
  }
}

template <typename T>
ref box<T>::call(const tuple& args) {
  if constexpr (std::is_invocable<T, const tuple&>::value) {
    return to_ref(std::invoke(_value, args));
  } else {
    return object::call(args);
  }
}

extern template class box<str>;
extern template class box<bool_>;
extern template class box<int_>;
extern template class box<float_>;
extern template class box<list>;
extern template class box<dict>;
extern template class box<set>;
extern template class box<NoneType>;
extern template class box<tuple>;
extern template class box<typeinfo>;
extern template class box<function>;

#endif
