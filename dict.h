#ifndef DICT_H
#define DICT_H
#include <iosfwd>
#include <unordered_map>

#include "ref.h"

class dict {
 public:
  dict() noexcept = default;
  ~dict() noexcept = default;

  template <typename K, typename V>
  dict(std::initializer_list<std::pair<K, V>> items) {
    for (const auto& item : items) {
      _map[make_ref(item.first)] = make_ref(item.second);
    }
  }

  dict(const dict&) = default;
  dict(dict&&) noexcept = default;
  dict& operator=(const dict&) = default;
  dict& operator=(dict&&) noexcept = default;

 private:
  std::unordered_map<const ref, ref> _map;
};

#endif  // DICT_H
