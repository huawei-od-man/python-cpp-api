#ifndef DICT_H
#define DICT_H
#include <iosfwd>
#include <unordered_map>
#include "ref.h"

class tuple;
class dict_keys;
class dict_values;
class dict_items;

class dict {
 public:
  dict() noexcept;
  ~dict() noexcept;

  dict(std::initializer_list<tuple> items);

  dict(const dict&) = default;
  dict(dict&&) noexcept = default;
  dict& operator=(const dict&) = default;
  dict& operator=(dict&&) noexcept = default;

  ref& operator[](Any key);

  const ref& operator[](Any key) const;

  size_t size() const noexcept { return _items.size(); }
  explicit operator bool() const noexcept { return !_items.empty(); }

  friend std::ostream& operator<<(std::ostream& os, const dict& obj);

  bool contains(ref key) const;

  void clear();

  ref get(ref key, ref def = {});

  dict_items items() const;

  dict_keys keys() const;

  ref pop(ref key, ref def = {});

  ref popitem();

  void setdefault(ref key, ref def = {});

  void update(ref items);

  dict_values values() const;

 private:
  std::unordered_map<ref, ref> _items;
};

#endif  // DICT_H
