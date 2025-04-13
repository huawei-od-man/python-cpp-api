#ifndef TUPLE_H
#define TUPLE_H

#include <initializer_list>
#include <memory>
#include <ostream>

#include "except.h"
#include "forward.h"
#include "ref.h"

class tuple {
 public:
  constexpr tuple() noexcept = default;

  explicit tuple(const list& items);
  explicit tuple(const set& items);

  template <typename... Args>
  explicit tuple(Args&&... args) {
    _items.reserve(sizeof...(args));
    size_t i = 0;
    (void)std::initializer_list<int>{
        (_items[i++] = make_ref(std::forward<Args>(args)), 0)...};
  }

  tuple(std::initializer_list<ref> items);

  ~tuple() noexcept = default;
  tuple(const tuple&) = default;
  tuple(tuple&&) noexcept = default;
  tuple& operator=(const tuple&) = default;
  tuple& operator=(tuple&&) noexcept = default;

  explicit operator bool() const noexcept { return size() > 0; }
  size_t size() const noexcept { return _items.size(); }

  const ref operator[](size_t index) const;

  const ref operator[](size_t index) {
    return const_cast<const tuple&>(*this)[index];
  }

 private:
  std::vector<ref> _items;
};

bool operator<(const tuple& lhs, const tuple& rhs) noexcept;
bool operator>(const tuple& lhs, const tuple& rhs) noexcept;
bool operator<=(const tuple& lhs, const tuple& rhs) noexcept;
bool operator>=(const tuple& lhs, const tuple& rhs) noexcept;
bool operator==(const tuple& lhs, const tuple& rhs) noexcept;
bool operator!=(const tuple& lhs, const tuple& rhs) noexcept;

std::ostream& operator<<(std::ostream& os, const tuple& obj);

#endif  // TUPLE_H
