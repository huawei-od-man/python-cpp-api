#ifndef FUNCTION_TCC
#define FUNCTION_TCC
#include <tuple>

#include "except.h"
#include "function.h"
#include "ref.tcc"
#include "tuple.h"

template <typename Tuple, size_t... Ids>
Tuple _tuple_unpack(const tuple& t, std::index_sequence<Ids...>) {
  if (t.size() != sizeof...(Ids)) {
    throw ValueError("Failed to unpack tuple: size mismatched!");
  }
  return Tuple(from_ref<std::tuple_element_t<Ids, Tuple>>(t[Ids])...);
}

template <typename... Args>
std::tuple<Args...> tuple::unpack() const {
  using Tuple = std::tuple<Args...>;
  return _tuple_unpack<Tuple>(*this, std::index_sequence_for<Args...>());
}

template <typename Ret, typename... Args>
function::function(Ret (*func)(Args...)) {
  _hash = reinterpret_cast<uintptr_t>(func);
  _value = [func](const tuple& args) -> ref {
    if (args.size() != sizeof...(Args)) {
      throw TypeError("Argument count mismatched!");
    }
    return to_ref(std::apply(func, args.unpack<Args...>()));
  };
}

#endif  // FUNCTION_TCC
