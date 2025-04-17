#include "utils.h"

#include "tuple.h"
#include "ref.h"
#include "str.h"

void print(std::initializer_list<Any> args, std::ostream& os) {
  int i = 0;
  for (const auto& arg : args) {
    os << static_cast<ref>(arg);
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

str repr(ref obj) {
  return obj->to_str();
}
