#include <array>
#include <algorithm> // for find()
#include "dict.h"
#include "forward.h"
#include "list.h"
#include "object.h"
#include "ref.tcc"
#include "tuple.h"

namespace {
const std::array<ref, 5> immutable_types = {
    type(tuple{}), type(str{}), type(bool_{}), type(int_{}), type(float_{}),
};
}

ref object::copy() const { return make_box<object>(*this); }

ref object::deepcopy(dict& memo) const { return copy(); }

ref copy(ref obj) {
  if (std::find(immutable_types.begin(), immutable_types.end(), type(obj)) !=
      immutable_types.end()) {
    return obj;
  }
  return obj->copy();
}

ref deepcopy(ref obj, dict& memo) {
  auto obj_id = id(obj);
  if (memo.contains(obj_id)) {
    return memo[obj_id];
  }
  if (std::find(immutable_types.begin(), immutable_types.end(), type(obj)) !=
      immutable_types.end()) {
    return obj;
  }
  auto result = obj->deepcopy(memo);
  memo[obj_id] = result;
  return result;
}

ref deepcopy(const list& obj, dict& memo) {
  list temp;
  for (const auto& item : obj.value()) {
    temp.append(deepcopy(item, memo));
  }
  return make_box<list>(std::move(temp));
}
