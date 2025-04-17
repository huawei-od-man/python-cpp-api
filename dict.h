#ifndef DICT_H
#define DICT_H
#include <iosfwd>
#include <unordered_map>

#include "ref.h"

class tuple;

class dict {
 public:
  dict() noexcept = default;
  ~dict() noexcept = default;

  dict(std::initializer_list<tuple> items);

  dict(const dict&) = default;
  dict(dict&&) noexcept = default;
  dict& operator=(const dict&) = default;
  dict& operator=(dict&&) noexcept = default;

  ref& operator[](Any key);

  const ref& operator[](Any key) const {
    return const_cast<const dict&>(*this)[key];
  }

  size_t size() const noexcept { return _map.size(); }
  explicit operator bool() const noexcept { return !_map.empty(); }

  friend std::ostream& operator<<(std::ostream& os, const dict& obj);

 private:
  std::unordered_map<ref, ref> _map;
};

#endif  // DICT_H
