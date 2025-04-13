#ifndef LIST_H
#define LIST_H

#include <vector>
#include "except.h"
#include "ref.h"

class list {
 public:
  list() noexcept = default;
  ~list() noexcept = default;

  list(const list&) = default;
  list(list&&) noexcept = default;
  list& operator=(const list&) = default;
  list& operator=(list&&) noexcept = default;

  void append(ref item) {
    _items.push_back(item);
  }

  template <typename T>
  void append(T&& item) {
    _items.push_back(make_ref(std::forward<T>(item)));
  }

  ref& operator[](size_t index);

  const ref& operator[](size_t index) const;

  size_t size() const noexcept { return _items.size(); }

  explicit operator bool() const noexcept {
    return !_items.empty();
  }

  class iter : public object {
    public:
    // explicit 
     ref next() override;

  };

 private:
  std::vector<ref> _items;
};

#endif
