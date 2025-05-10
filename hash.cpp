#include "hash.tcc"

#include <functional>
#include <numeric>

#include "dict.h"
#include "except.h"
#include "list.h"
#include "set.h"
#include "tuple.h"
#include "type.h"
#include "none.h"

template <typename Iter>
size_t _hash_combine(Iter first, Iter last, size_t init = 0ULL) {
  return std::accumulate(first, last, 0ULL, [](size_t seed, const auto& val) {
    return seed ^ (::hash(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
  });
}

size_t hash(const tuple& obj) {
  return _hash_combine(obj.value().begin(), obj.value().end());
}

size_t hash(const list& /* obj */) {
  throw TypeError("unhashable type: 'list'");
}

size_t hash(const typeinfo& obj) { return ::hash(obj.name()); }

size_t hash(const dict& /* obj */) {
  throw TypeError("unhashable type: 'dict'");
}

size_t hash(const set& /* obj */) { throw TypeError("unhashable type: 'set'"); }

size_t hash(const ref& obj) { return obj->hash(); }

size_t hash(const NoneType& obj) { return ::hash(&obj); }

size_t hash(const object& value) { return reinterpret_cast<size_t>(&value); }
