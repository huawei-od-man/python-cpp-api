#ifndef BOX_H
#define BOX_H
#include <type_traits>

#include "bool.h"
#include "dict.h"
#include "except.h"
#include "floating_point.h"
#include "int.h"
#include "list.h"
#include "object.h"
#include "ref.h"
#include "set.h"
#include "str.h"
#include "tuple.h"

template <typename T, typename = void>
struct has_add_method : std::false_type {};

template <typename T>
struct has_add_method<
    T, std::void_t<decltype(std::declval<T>() + std::declval<T>())>>
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
class box : public object {
  static_assert(!std::is_base_of<object, T>::value,
                "T must not be derived from object");

 public:
  box() noexcept(T()) = default;

  template <typename... Args>
  explicit box(Args&&... args) : _value(std::forward<Args>(args)...) {}

  box(const box&) = default;
  ~box() override = default;

  const char* type_name() const override { return typeid(T).name(); }

  std::size_t size() const override {
    if constexpr (has_size_method<T>::value) {
      return _value.size();
    } else {
      return object::size();
    }
  }

  void format(std::ostream& os) const override {
    if constexpr (has_operator_insertion<T>::value) {
      os << _value;
    } else {
      object::format(os);
    }
  }

  bool to_bool() const override {
    if constexpr (std::is_convertible<T, bool>::value) {
      return static_cast<bool>(_value);
    } else {
      return object::to_bool();
    }
  }

  float_ to_float() const override {
    if constexpr (std::is_same<T, float_>::value) {
      return _value;
    } else {
      return object::to_float();
    }
  }

  ref add(ref other) const override {
    if constexpr (has_add_method<T>::value && std::is_constructible_v<T, ref>) {
      const auto rhs = T(other);
      const auto result = _value + rhs;
      return make_box<decltype(result)>(result);
    } else {
      return object::add(other);
    }
  }

 private:
  T _value{};
};

template <typename T, typename... Args>
ref make_box(Args&&... args) {
  if constexpr (std::is_floating_point<T>::value) {
    return ref(std::make_shared<box<float_>>(std::forward<Args>(args)...));
  } else if constexpr (std::is_same<T, bool>::value) {
    return ref(std::make_shared<box<bool_>>(std::forward<Args>(args)...));
  } else if constexpr (std::is_integral<T>::value) {
    return ref(std::make_shared<box<int_>>(std::forward<Args>(args)...));
  } else if constexpr (std::is_same_v<std::decay_t<T>, const char*>) {
    return ref(std::make_shared<box<str>>(std::forward<Args>(args)...));
  } else if constexpr (std::is_base_of<object, T>::value) {
    return ref(std::make_shared<T>(std::forward<Args>(args)...));
  } else {
    return ref(std::make_shared<box<T>>(std::forward<Args>(args)...));
  }
}

template <typename T>
ref::ref(T&& value)
    : ref(make_box<T>(std::forward<T>(value))) {}

template <typename T>
T& ref::as() {
  if constexpr (std::is_base_of_v<object, T>) {
    if (auto ptr = std::dynamic_pointer_cast<T>(_ptr)) {
      return *ptr;
    }
  } else {
    if (auto ptr = std::dynamic_pointer_cast<box<T>>(_ptr)) {
      return ptr->_value;
    }
  }
  throw TypeError("Invalid type conversion from type");
}

template <typename T>
const T& ref::as() const {
  return const_cast<const T&>(const_cast<ref*>(this)->as<T>());
}

template <typename... Args>
str str::format(Args&&... args) const {
  return format(tuple{std::forward<Args>(args)...});
}

#endif  // BOX_H
