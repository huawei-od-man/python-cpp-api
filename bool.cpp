#include "bool.h"

#include "box.tcc"

const ref True{make_box<bool_>(true)};
const ref False{make_box<bool_>(false)};

bool_::bool_(ref obj) : bool_(static_cast<bool>(obj)) {}

ref type(const bool_&) {
  static const auto bool_type = ::type("bool", tuple{}, dict{});
  return bool_type;
}

std::ostream& operator<<(std::ostream& os, const bool_& b) {
  return os << (b.value() ? "True" : "False");
}
