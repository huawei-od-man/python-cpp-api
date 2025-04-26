#ifndef TUPLE_H
#define TUPLE_H

#include <initializer_list>
#include <ostream>

#include "forward.h"
#include "ref.h"

class tuple {
 public:
  tuple() noexcept = default;

  explicit tuple(const list& items);
  explicit tuple(const set& items);

  tuple(std::initializer_list<Any> items);

  ~tuple() noexcept = default;
  tuple(const tuple&) = default;
  tuple(tuple&&) noexcept = default;
  tuple& operator=(const tuple&) = default;
  tuple& operator=(tuple&&) noexcept = default;

  explicit operator bool() const noexcept { return size() > 0; }
  size_t size() const noexcept { return _items.size(); }

  ref& operator[](size_t index) const;

  ref& operator[](size_t index) {
    return const_cast<const tuple&>(*this)[index];
  }

  tuple slice(size_t start, size_t end = -1) const;

  const std::vector<ref>& value() const { return _items; }
  friend tuple operator+(const tuple& lhs, const tuple& rhs);

  friend bool operator<(const tuple& lhs, const tuple& rhs) noexcept;
  friend bool operator>(const tuple& lhs, const tuple& rhs) noexcept;
  friend bool operator<=(const tuple& lhs, const tuple& rhs) noexcept;
  friend bool operator>=(const tuple& lhs, const tuple& rhs) noexcept;
  friend bool operator==(const tuple& lhs, const tuple& rhs) noexcept;
  friend bool operator!=(const tuple& lhs, const tuple& rhs) noexcept;

  // template <typename... Args>
  // std::tuple<Args...> unpack() const;

 private:
  std::vector<ref> _items;
};

std::ostream& operator<<(std::ostream& os, const tuple& obj);

template <typename... Args>
void unpack_tuple(const tuple& tuple_in, std::tuple<Args...>& tuple_out);

template <typename... Args>
std::tuple<Args...> unpack_tuple(const tuple& tuple_in);

#endif  // TUPLE_H
