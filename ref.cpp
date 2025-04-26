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

ref to_ref(ref r) { return r; }

ref to_ref(Any any) { return static_cast<ref>(any); }

ref to_ref(void) { return None; }

ref ref::operator()(const tuple& args) { return _ptr->call(args); }
