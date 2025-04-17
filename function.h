#ifndef FUNCTION_H
#define FUNCTION_H
#include <functional>
#include <iostream>

#include "except.h"
#include "forward.h"
#include "tuple.h"
#include "type.h"
#include "box.h"

template <typename>
class function;

template <typename R, typename... Args>
class function<R(Args...)> {
 public:
  template <typename F>
  function(F&& func)
      : _func(std::forward<F>(func)), _argument_types{type<Args>()...} {}

  function(const function&) = default;
  function(function&&) = default;
  function& operator=(const function&) = default;
  function& operator=(function&&) = default;
  ~function() = default;

  ref operator()(const tuple& args) {
    // 检查参数数量是否匹配
    if (args.size() != sizeof...(Args)) {
      throw TypeError("Invalid number of arguments");
    }
    // 解包 tuple 并调用函数
    return invoke_function(args, std::make_index_sequence<sizeof...(Args)>());
  }

  friend std::ostream& operator<<(std::ostream& os, const function& obj) {
    os << "<function" << obj._argument_types << ">";
    return os;
  }

 private:
  // 辅助函数：解包 tuple 并调用函数
  template <std::size_t... I>
  ref invoke_function(const tuple& args, std::index_sequence<I...>) {
    // 将 tuple 中的参数解包并传递给函数
    return to_ref(_func(from_ref<Args>(args[I])...));
  }
  std::function<R(Args...)> _func;
  tuple _argument_types;
};

#endif  // FUNCTION_H
