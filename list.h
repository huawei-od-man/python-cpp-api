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

  void append(Any item);

  void sort(bool reverse = false);

  ref& operator[](size_t index);

  const ref& operator[](size_t index) const;

  size_t size() const noexcept { return _items.size(); }

  explicit operator bool() const noexcept { return !_items.empty(); }

  class iter {
   public:
    // explicit
    ref next();
  };

 private:
  std::vector<ref> _items;
};

std::ostream& operator<<(std::ostream& os, const list& lst);

template<> ref type<list>();

#endif
