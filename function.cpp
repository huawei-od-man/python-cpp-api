#include "function.h"

#include "dict.h"
#include "ref.h"
#include "tuple.h"
#include "except.h"

ref function::operator()(const tuple& args) {
  if (args.size() != _argument_count) {
    throw TypeError("Argument count mismatched!");
  }
  return _value(args);
}

std::ostream& operator<<(std::ostream& os, const function& obj) {
  return os << "<" << type(obj) << ">";
}

ref type(const function&) {
  static const auto function_type =
      ::type("builtin_function_or_method", tuple{}, dict{});
  return function_type;
}
