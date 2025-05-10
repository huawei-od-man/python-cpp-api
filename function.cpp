#include "function.h"

#include "dict.h"
#include "ref.tcc"
#include "tuple.h"
#include "except.h"

ref function::operator()(const tuple& args) {
  if (args.size() != _argument_count) {
    throw TypeError("Argument count mismatched! {} {}"_s.format({args.size(), _argument_count}));
  }
  return _value(args);
}

ref type(const function&) {
  static const auto function_type =
      ::type("builtin_function_or_method", tuple{}, dict{});
  return function_type;
}
