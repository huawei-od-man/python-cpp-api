#include "str.h"

#include <sstream>

#include "except.h"
#include "object.h"
#include "ref.h"
#include "tuple.h"

str::str(ref obj) : str(obj->to_str()) {}

str str::format(tuple args) const {
  std::ostringstream oss;
  size_t index = 0;
  for (size_t i = 0; i < _string.size(); ++i) {
    if (_string[i] == '{' && i + 1 < _string.size() && _string[i + 1] == '}') {
      if (index >= args.size()) {
        throw IndexError("Index out of range");
      }
      oss << args[index++];
      ++i;  // Skip the '}'
    } else {
      oss << _string[i];
    }
  }
  return str(oss.str());
}
