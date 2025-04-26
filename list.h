#ifndef LIST_H
#define LIST_H

#include <iosfwd>
#include <vector>

#include "ref.h"

class list {
 public:
  list() noexcept = default;
  ~list() noexcept = default;

  list(const list&) = default;
  list(list&&) noexcept = default;
  list& operator=(const list&) = default;
  list& operator=(list&&) noexcept = default;

  list(std::initializer_list<Any> items);

  void append(ref item);

  void sort(bool reverse = false);

  ref& operator[](size_t index);

  const ref& operator[](size_t index) const;

  size_t size() const noexcept { return _items.size(); }

  explicit operator bool() const noexcept { return !_items.empty(); }

  const std::vector<ref>& value() const { return _items; }

 private:
  std::vector<ref> _items;
};

std::ostream& operator<<(std::ostream& os, const list& lst);

#endif
