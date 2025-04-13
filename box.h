#ifndef BOX_H
#define BOX_H
#include <type_traits>

#include "object.h"

// 检查 T 是否有一个返回类型为 size_t 的 size() 方法
template <typename T, typename = void>
struct has_size_method : std::false_type {};

template <typename T>
struct has_size_method<T, std::void_t<decltype(std::declval<T>().size())>>
    : std::is_same<decltype(std::declval<T>().size()), std::size_t> {};

template <typename T>
class box : public object {
  static_assert(!std::is_base_of<object, T>::value,
                "T must not be derived from object");

 public:
  explicit box(const T& value) : _value(value) {}
  explicit box(T&& value) : _value(std::move(value)) {}

  ~box() override = default;

  const char* type_name() const override { return typeid(T).name(); }

  // 仅当 T 有 size() 方法时重写 size()
  template <typename U = T,
            typename std::enable_if<has_size_method<U>::value, int>::type = 0>
  std::size_t size() const override {
    return _value.size();
  }

 private:
  T _value{};
};

template <typename T>
ref make_ref(T&& obj) {
  return ref(std::make_shared<box<T>>(std::forward<T>(obj)));
}

template <typename T, typename... Args>
ref make_box(Args&&... args) {
  return ref(std::make_shared<box<T>>(std::forward<Args>(args)...));
}

#endif  // BOX_H