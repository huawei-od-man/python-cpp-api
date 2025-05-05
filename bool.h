#ifndef BOOL_H
#define BOOL_H

#include <iosfwd>
#include <utility>

class ref;

class bool_ {
 public:
  explicit bool_(ref obj);

  constexpr explicit bool_(bool value) noexcept : _value(value) {}
  constexpr bool_() noexcept = default;
  ~bool_() noexcept = default;

  constexpr bool_(const bool_&) noexcept = default;
  constexpr bool_(bool_&&) noexcept = default;
  constexpr bool_& operator=(const bool_&) noexcept = default;
  constexpr bool_& operator=(bool_&&) noexcept = default;
  constexpr /* implicit */ operator bool() const noexcept { return value(); }
  constexpr bool value() const noexcept { return _value; }

  constexpr bool operator!() const noexcept { return !value(); }
  constexpr bool operator==(const bool_& other) const noexcept {
    return value() == other.value();
  }
  constexpr bool operator<(const bool_& other) const noexcept {
    return value() < other.value();
  }

 private:
  bool _value{false};
};

extern const ref True, False;

std::ostream& operator<<(std::ostream& os, const bool_& b);


#endif
