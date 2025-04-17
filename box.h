#ifndef BOX_H
#define BOX_H
#include <type_traits>

#include "bool.h"
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
#include "type.h"

// 通用模板：提取函数签名
template <typename T>
struct function_signature;

// 针对普通函数指针
template <typename R, typename... Args>
struct function_signature<R (*)(Args...)> {
  using type = R (*)(Args...);
};

// 针对 std::function
template <typename R, typename... Args>
struct function_signature<std::function<R(Args...)>> {
  using type = R (*)(Args...);
};

// 针对 lambda 或其他可调用对象
template <typename T>
struct function_signature : function_signature<decltype(&T::operator())> {};

// 针对成员函数指针
template <typename C, typename R, typename... Args>
struct function_signature<R (C::*)(Args...) const> {
  using type = R (*)(const C&, Args...);
};

template <typename C, typename R, typename... Args>
struct function_signature<R (C::*)(Args...)> {
  using type = R (*)(C&, Args...);
};

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
  static_assert(!std::is_reference_v<T>, "T must not be a reference type");
  static_assert(!std::is_pointer_v<T>, "T must not be a pointer type");
  static_assert(!std::is_void_v<T>, "T must not be void");
  static_assert(!std::is_const_v<T>, "T must not be const");
  static_assert(!std::is_volatile_v<T>, "T must not be volatile");
  static_assert(!std::is_same_v<T, ref>, "T must not be ref");
  static_assert(!std::is_same_v<T, Any>, "T must not be Any");

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
        return object::eq(other);
      }
    } else {
      return object::eq(other);
    }
  }

  bool lt(ref other) const override {
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

  ref call(const tuple& args) override {
    if constexpr (std::is_invocable<T, const tuple&>::value) {
      return to_ref(std::invoke(_value, args));
    } else {
      return object::call(args);
    }
  }

  ref type() const override { return ::type<T>(); }

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
  } else if constexpr (has_call_method<T>::value) {
    using function_type =
        std::remove_pointer_t<typename function_signature<T>::type>;
    return ref(std::make_shared<box<function<function_type>>>(
        std::forward<Args>(args)...));
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

template <typename T>
ref type() {
  static const auto instance = to_ref(typeinfo{
      .name = get_type_name<T>(),
      .bases = tuple{type<object>()},
      .attrs = dict{},
  });
  return instance;
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

#endif  // BOX_H
