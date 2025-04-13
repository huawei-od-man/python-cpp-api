#ifndef ITER_H
#define ITER_H
#include "ref.h"

class iterator {
 public:
  iterator() = default;

  ref& operator*() { return _iter; }
  const ref& operator*() const { return _iter; }
  ref& operator->() { return _iter; }
  const ref& operator->() const { return _iter; }
  iterator& operator++();

 private:
  ref _iter;
};

#endif  // ITER_H
