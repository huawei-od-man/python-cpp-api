#ifndef FUNCTION_TCC
#define FUNCTION_TCC
#include <tuple>

#include "except.h"
#include "function.h"
#include "ref.tcc"
#include "tuple.h"

// 通用模板：提取函数签名
template <typename T>
struct function_signature;

template <typename T>
struct lambda_signature;

// 针对普通函数指针
template <typename R, typename... Args>
struct function_signature<R (*)(Args...)> {
  using type = std::tuple<Args...>;
  using ret = R;
  using index = std::index_sequence_for<Args...>;
};

// 针对 std::function
template <typename R, typename... Args>
struct function_signature<std::function<R(Args...)>> {
  using type = std::tuple<Args...>;
  using ret = R;
  using index = std::index_sequence_for<Args...>;
};

// 针对 lambda 或其他可调用对象
template <typename T>
struct function_signature : lambda_signature<decltype(&T::operator())> {};

template <typename C, typename R, typename... Args>
struct lambda_signature<R (C::*)(Args...) const> {
  using type = std::tuple<Args...>;
  using ret = R;
  using index = std::index_sequence_for<Args...>;
};

template <typename C, typename R, typename... Args>
struct lambda_signature<R (C::*)(Args...)> {
  using type = std::tuple<Args...>;
  using ret = R;
  using index = std::index_sequence_for<Args...>;
};

// 针对成员函数指针
template <typename C, typename R, typename... Args>
struct function_signature<R (C::*)(Args...) const> {
  using type = std::tuple<const C&, Args...>;
  using ret = R;
  using index = std::index_sequence_for<Args...>;
};

template <typename C, typename R, typename... Args>
struct function_signature<R (C::*)(Args...)> {
  using type = std::tuple<C&, Args...>;
  using ret = R;
  using index = std::index_sequence_for<Args...>;
};

template <typename Tuple, size_t... Ids>
Tuple _tuple_unpack(const tuple& t, std::index_sequence<Ids...>) {
  if (t.size() != sizeof...(Ids)) {
    throw ValueError("Failed to unpack tuple: size mismatched!");
  }
  return Tuple(from_ref<std::tuple_element_t<Ids, Tuple>>(t[Ids])...);
}

template <typename... Args>
void unpack_tuple(const tuple& tuple_in, std::tuple<Args...>& tuple_out) {
  using Tuple = std::tuple<Args...>;
  tuple_out =
      _tuple_unpack<Tuple>(tuple_in, std::index_sequence_for<Args...>());
}

template <typename... Args>
std::tuple<Args...> unpack_tuple(const tuple& tuple_in) {
  std::tuple<Args...> tuple_out;
  unpack_tuple(tuple_in, tuple_out);
  return tuple_out;
}

// template <typename Tuple>
// Tuple unpack_tuple(const tuple& tuple_in) {}

template <typename Ret, typename Func, typename T, typename Tuple,
          size_t... Ids>
ref _apply_method(Func func, T& self, const Tuple& args,
                  std::index_sequence<Ids...>) {
  if constexpr (std::is_same_v<Ret, void>) {
    (self.*func)(std::get<Ids>(args)...);
    return None;
  } else {
    return to_ref((self.*func)(std::get<Ids>(args)...));
  }
}

template <typename Ret, typename Func, typename Tuple,
          size_t... Ids>
ref _apply_func(Func func, const Tuple& args,
                  std::index_sequence<Ids...>) {
  if constexpr (std::is_same_v<Ret, void>) {
    func(std::get<Ids>(args)...);
    return None;
  } else {
    return to_ref(func(std::get<Ids>(args)...));
  }
}

template <typename Ret, typename... Args>
function::function(Ret (*func)(Args...)) {
  _argument_count = sizeof...(Args);
  _value = [func](const tuple& args) -> ref {
    return _apply_func<Ret>(func, unpack_tuple<Args...>(args),
      std::index_sequence_for<Args...>());
  };
}

template <typename Ret, typename... Args>
function::function(std::function<Ret(Args...)> func) {
  _argument_count = sizeof...(Args);
  _value = [func = std::move(func)](const tuple& args) -> ref {
    return _apply_func<Ret>(func, unpack_tuple<Args...>(args),
      std::index_sequence_for<Args...>());
  };
}

template <typename Ret, typename T, typename... Args>
function::function(Ret (T::*func)(Args...)) {
  _argument_count = 1 + sizeof...(Args);
  _value = [func](const tuple& args) -> ref {
    T& self = from_ref<T>(args[0]);
    std::tuple<Args...> args_t;
    unpack_tuple(args.slice(1), args_t);
    return _apply_method<Ret>(func, self, args_t,
                              std::index_sequence_for<Args...>());
  };
}

template <typename Ret, typename T, typename... Args>
function::function(Ret (T::*func)(Args...) const) {
  _argument_count = 1 + sizeof...(Args);
  _value = [func](const tuple& args) -> ref {
    const T& self = from_ref<T>(args[0]);
    std::tuple<Args...> args_t;
    unpack_tuple(args.slice(1), args_t);
    return _apply_method<Ret>(func, self, args_t,
                              std::index_sequence_for<Args...>());
  };
}

template <typename Func, typename>
function::function(Func func) {
  using signature = typename function_signature<Func>::type;
  using Ret = typename function_signature<Func>::ret;
  using index = typename function_signature<Func>::index;
  _argument_count = std::tuple_size_v<signature>;
  _value = [func = std::move(func)](const tuple& args) -> ref {
    signature args_t;
    unpack_tuple(args, args_t);
    return _apply_func<Ret>(func, args_t, index{});
  };
}

#endif  // FUNCTION_TCC
