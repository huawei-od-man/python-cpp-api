#include "ref.h"

#include "bool.h"
#include "box.h"
#include "except.h"
#include "none.h"

const ref None{make_box<NoneType>()};
const ref True{make_box<bool_>(true)};
const ref False{make_box<bool_>(false)};

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
