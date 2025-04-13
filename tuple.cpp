#include "tuple.h"

#include "list.h"
#include "except.h"


tuple::tuple(const list &items) {
  _items.reserve(items.size());
  for (size_t i = 0; i < items.size(); ++i) {
    _items.push_back(items[i]);
  }
}
