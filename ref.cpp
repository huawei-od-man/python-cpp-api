#include "ref.h"

#include "except.h"

ref::ref() : ref(None) {}

ref::ref(Any&& any) noexcept : ref(any) {}

bool ref::operator==(const ref& other) const { return _ptr->eq(other); }

bool ref::operator!=(const ref& other) const { return _ptr->neq(other); }

std::ostream& operator<<(std::ostream& os, const ref& r) {
  r->format(os);
  return os;
}

bool ref::operator<(const ref& other) const { return _ptr->lt(other); }

bool ref::operator>(const ref& other) const { return false; }

Any::Any(const Any&& other) noexcept : r(other.r) {}

Any::Any(Any& other) noexcept : r(other.r) {}
