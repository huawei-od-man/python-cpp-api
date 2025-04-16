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
#include "type.h"
#include "none.h"

// Primary template: Default case, assumes no specialization exists
template <typename T, typename = void>
struct has_specialized_hash : std::false_type {};

// Specialization: Checks if std::hash<T> is well-formed
template <typename T>
struct has_specialized_hash<T,
                            std::void_t<decltype(std::declval<std::hash<T>>()(
                                std::declval<const T&>()))>> : std::true_type {
};

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
class box : public object {
  static_assert(!std::is_base_of<object, T>::value,
                "T must not be derived from object");
  static_assert(!std::is_reference_v<T>,
                "T must not be a reference type");
  static_assert(!std::is_pointer_v<T>,
                "T must not be a pointer type");
  static_assert(!std::is_void_v<T>,
                "T must not be void");
  static_assert(!std::is_const_v<T>, "T must not be const");
  static_assert(!std::is_volatile_v<T>, "T must not be volatile");
  static_assert(!std::is_same_v<T, ref>, "T must not be ref");

 public:
  box() noexcept(noexcept(T())) = default;

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
    if constexpr (has_add_method<T>::value) {
      return to_ref(_value + from_ref<T>(other));
    } else {
      return object::add(other);
    }
  }

  size_t hash() const override {
    if constexpr (has_specialized_hash<T>::value) {
      return std::hash<T>{}(_value);
    } else {
      return object::hash();
    }
  }

  bool eq(ref other) const override {
    if constexpr (has_eq_method<T>::value) {
      try {
        return _value == from_ref<T>(other);
      } catch (const TypeError&) {
        return false;
      }
    } else {
      return object::eq(other);
    }
  }

  ref type() const override {
    return ::type<T>::instance();
  }

  T& value() { return _value; }
  const T& value() const { return _value; }

 private:
  friend class ref;

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
  } else if constexpr (std::is_same_v<std::decay_t<T>, char*>) {
    return ref(std::make_shared<box<str>>(std::forward<Args>(args)...));
  } else if constexpr (std::is_base_of<object, T>::value) {
    return ref(std::make_shared<T>(std::forward<Args>(args)...));
  } else {
    return ref(std::make_shared<box<T>>(std::forward<Args>(args)...));
  }
}

template <>
inline ref make_box<bool, bool>(bool&& value) {
  return value ? True : False;
}

template <typename T>
ref to_ref(T&& value) {
  using U = std::remove_cv_t<std::remove_reference_t<T>>;
  return make_box<U>(std::forward<T>(value));
}

template <typename T>
T& from_ref(ref& r) {
  if constexpr (std::is_base_of_v<object, T>) {
    if (auto ptr = std::dynamic_pointer_cast<T>(r.value())) {
      return *ptr;
    }
  } else {
    if (auto ptr = std::dynamic_pointer_cast<box<T>>(r.value())) {
      return ptr->value();
    }
  }
  throw TypeError("Invalid type conversion from type");
}

template <typename T>
const T& from_ref(const ref& r) {
  return from_ref<T>(const_cast<ref&>(r));
}

template <typename... Args>
str str::format(Args&&... args) const {
  return format(tuple{std::forward<Args>(args)...});
}

template <typename T>
template <typename... Args>
ref type<T>::operator()(Args&&... args) {
  if constexpr (std::is_constructible_v<T, Args&&...>) {
    return T(std::forward<Args>(args)...);
  } else {
    throw TypeError("Invalid arguments for type constructor");
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

extern template class box<type<str>>;
extern template class box<type<bool_>>;
extern template class box<type<int_>>;
extern template class box<type<float_>>;
extern template class box<type<list>>;
extern template class box<type<dict>>;
extern template class box<type<set>>;
extern template class box<type<NoneType>>;
extern template class box<type<tuple>>;

#endif  // BOX_H
