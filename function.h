#ifndef FUNCTION_H
#define FUNCTION_H
#include <cstdint>

#include <functional>
#include <iosfwd>

#include "str.h"

class tuple;
class ref;

class function {
 public:
  template <typename Ret, typename... Args>
  function(Ret (*func)(Args...));

  function(const function&) = default;
  function(function&&) = default;
  function& operator=(const function&) = default;
  function& operator=(function&&) = default;
  ~function() = default;

  ref operator()(const tuple& args);

 private:
  friend size_t hash(const function& obj);

  friend std::ostream& operator<<(std::ostream& os, const function& obj);

  uintptr_t _hash{};
  std::function<ref(const tuple&)> _value;
};


#endif  // FUNCTION_H
