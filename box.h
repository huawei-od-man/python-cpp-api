#ifndef BOX_H
#define BOX_H
#include <type_traits>

#include "object.h"

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

  std::size_t size() const override;

  void format(std::ostream& os) const override;

  bool to_bool() const override;

  float_ to_float() const override;

  ref add(ref other) const override;

  size_t hash() const override;

  bool eq(ref other) const override;

  bool lt(ref other) const override;

  ref call(const tuple& args) override;

  ref type() const override;

  T& value() { return _value; }
  const T& value() const { return _value; }

 private:
  friend class ref;

  T _value{};
};

#endif  // BOX_H
