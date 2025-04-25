#ifndef SET_H
#define SET_H

#include <unordered_set>

#include "ref.h"

class set {
 public:
  set() noexcept = default;
  ~set() noexcept = default;
  set(std::initializer_list<Any> items);

  set(const set&) = default;
  set(set&&) noexcept = default;
  set& operator=(const set&) = default;
  set& operator=(set&&) noexcept = default;
  explicit operator bool() const noexcept { return !_items.empty(); }

  size_t size() const noexcept { return _items.size(); }
  void add(ref item) { _items.insert(item); }
  void remove(ref item) { _items.erase(item); }
  void clear() { _items.clear(); }
  bool contains(ref item) const { return _items.find(item) != _items.end(); }

  friend std::ostream& operator<<(std::ostream& os, const set& obj);

  const std::unordered_set<ref>& value() const { return _items; }

 private:
  std::unordered_set<ref> _items;
};

#endif  // SET_H
