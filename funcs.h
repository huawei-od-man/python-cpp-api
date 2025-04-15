#ifndef FUNCS_H
#define FUNCS_H
#include <initializer_list>
#include <iostream>

#include "forward.h"
#include "ref.h"

inline void print(std::initializer_list<ref> args,
                  std::ostream& os = std::cout) {
  size_t i = 0;
  for (const auto& arg : args) {
    os << *arg;
    if (i < args.size() - 1) {
      os << ", ";
    }
    ++i;
  }
  os << std::endl;
}

#endif  // FUNCS_H
