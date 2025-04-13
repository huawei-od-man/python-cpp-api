#ifndef BOX_H
#define BOX_H
#include <type_traits>

#include "except.h"
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
  box() noexcept(T()) = default;

  explicit box(const T& value) noexcept(
      std::is_nothrow_copy_constructible<T>::value)
      : _value(value) {}
  explicit box(T&& value) noexcept(std::is_nothrow_move_constructible<T>::value)
      : _value(std::move(value)) {}

  box(const box&) noexcept(T(std::declval<const T&>())) = default;
  ~box() override = default;

  const char* type_name() const override { return typeid(T).name(); }

  std::size_t size() const override {
    if constexpr (has_size_method<T>::value) {
      return _value.size();
    } else {
      throw NotImplementedError("size() method is not implemented");
    }
  }

 private:
  T _value{};
};

template <typename T, typename... Args>
ref make_box(Args&&... args) {
  return ref(std::make_shared<box<T>>(std::forward<Args>(args)...));
}
inline ref make_box(const ref& obj) { return obj; }

inline ref make_box(ref&& obj) { return std::move(obj); }

#endif  // BOX_H