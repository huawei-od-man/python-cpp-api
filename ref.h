#ifndef REF_H
#define REF_H

#include <memory>

#include "object.h"

class ref {
 public:
  ref() = default;

  explicit ref(std::shared_ptr<object> ptr) noexcept
   : _ptr(std::move(ptr))  {}

  ref(const ref&) noexcept = default;
   ref(ref&&) noexcept = default;
  ref& operator=(const ref&) noexcept = default;
   ref& operator=(ref&&) noexcept = default;

  constexpr object* operator->() const noexcept { return _ptr.get(); }
  constexpr object& operator*() const noexcept { return *_ptr; }

 private:
  std::shared_ptr<object> _ptr;
};


#endif  // REF_H
