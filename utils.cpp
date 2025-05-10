#include "forward.h"

#include "ref.h"
#include "str.h"
#include "tuple.h"
#include "ref.tcc"

void print(const tuple& args, std::ostream& os) {
  int i = 0;
  for (const auto& arg : args.value()) {
    os << arg;
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

str repr(ref obj) { return obj->to_str(); }

ref id(ref obj) { return Any{reinterpret_cast<size_t>(obj.get())}; }
