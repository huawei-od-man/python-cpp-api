#ifndef WEAK_REF_H
#define WEAK_REF_H
#include <memory>

#include "ref.h"

class weak_ref {
 public:
  weak_ref() noexcept = default;
  weak_ref(const ref& r) : _ptr(r.value()) {}
  weak_ref(ref&& r) : _ptr(std::move(r.value())) {}

  ref lock() const { return _ptr.lock(); }

  explicit operator bool() const { return static_cast<bool>(lock()); }

 private:
  std::weak_ptr<object> _ptr;
};

#endif
