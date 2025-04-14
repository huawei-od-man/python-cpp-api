#ifndef NONE_H
#define NONE_H
#include <iostream>

class ref;

struct NoneType {
  constexpr NoneType() noexcept = default;
  ~NoneType() noexcept = default;

  constexpr explicit operator bool() const noexcept { return false; }

  friend std::ostream& operator<<(std::ostream& os, const NoneType&) {
    return os << "None";
  }
};

#endif  // NONE_H
