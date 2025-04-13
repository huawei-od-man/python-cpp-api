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
      throw NotImplementedError("size() method is not implemented");
    }
  }

  void format(std::ostream& os) const override {
    if constexpr (has_operator_insertion<T>::value) {
      os << _value;
    } else {
      throw NotImplementedError(
          "operator<< is not implemented for type {}"_s.format(type_name()));
    }
  }

  bool to_bool() const override {
    if constexpr (std::is_convertible<T, bool>::value) {
      return static_cast<bool>(_value);
    } else {
      throw NotImplementedError("to_bool() method is not implemented");
    }
  }

  float_ to_float() const override {
    if constexpr (std::is_same<T, float_>::value) {
      return _value;
    } else {
      throw NotImplementedError("to_float() method is not implemented");
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
  } else if constexpr (std::is_base_of<object, T>::value) {
    return ref(std::make_shared<T>(std::forward<Args>(args)...));
  } else {
    return ref(std::make_shared<box<T>>(std::forward<Args>(args)...));
  }
}

template <typename... Args>
str str::format(Args&&... args) const {
  return format(tuple(std::forward<Args>(args)...));
}

template <typename... Args>
tuple::tuple(Args&&... args) {
  _items.reserve(sizeof...(args));
  (void)std::initializer_list<int>{
      (_items.emplace_back(make_box<Args>(std::forward<Args>(args))), 0)...};
}

template <typename... Args>
list::list(Args&&... args) {
  _items.reserve(sizeof...(args));
  (void)std::initializer_list<int>{
      (_items.emplace_back(make_box<Args>(std::forward<Args>(args))), 0)...};
}

template <typename T>
void list::append(T&& item) {
  _items.emplace_back(make_box<T>(std::forward<T>(item)));
}

template <typename T>
ref& dict::operator[](T&& key) {
  return (*this)[make_box<T>(std::forward<T>(key))];
}

template <typename... Args>
set::set(Args&&... args) {
  _items.reserve(sizeof...(args));
  (void)std::initializer_list<int>{
      (_items.insert(make_box<Args>(std::forward<Args>(args))), 0)...};
}

#endif  // BOX_H
