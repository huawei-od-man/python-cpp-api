#include "bool.h"

#include "ref.tcc"

const ref True{make_box<bool_>(true)};
const ref False{make_box<bool_>(false)};

bool_::bool_(ref obj) : bool_(obj->to_bool()) {}

std::ostream& operator<<(std::ostream& os, const bool_& b) {
  return os << (b.value() ? "True" : "False");
}
