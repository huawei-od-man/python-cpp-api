#ifndef NONE_H
#define NONE_H
#include <iostream>
#include <utility>

struct NoneType {
  constexpr NoneType() noexcept = default;
  ~NoneType() noexcept = default;

  constexpr explicit operator bool() const noexcept { return false; }

  friend std::ostream& operator<<(std::ostream& os, const NoneType&) {
    return os << "None";
  }
  friend bool operator==(const NoneType&, const NoneType&) noexcept {
    return true;
  }
  friend bool operator!=(const NoneType&, const NoneType&) noexcept {
    return false;
  }
  friend bool operator<(const NoneType&, const NoneType&) noexcept {
    return false;
  }
};

namespace std {
template <>
struct hash<NoneType> {
  size_t operator()(const NoneType&) const noexcept { return 0; }
};
}  // namespace std

#endif  // NONE_H
