#include "funcs.h"

#include "tuple.h"

void print(std::initializer_list<Any> args, std::ostream& os) { int i = 0;
  for (const auto& arg : args) {
    os << arg.r;
    if (i < args.size() - 1) {
      os << " ";
    }
    ++i;
  }
  os << std::endl;
}

void print(Any arg, std::ostream& os) {
  os << static_cast<ref>(arg) << std::endl;
}
