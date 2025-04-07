#ifndef SET_H
#define SET_H

#include <unordered_set>

#include "object.h"

class Set : public Object {
 public:
  Set() = default;
  ~Set() override;
  virtual void add(object item);

 private:
  std::unordered_set<object> _elements;
};

template <typename V>
class set : public ref<Set> {
 public:
  set() : ref<Set>(new Set()) {}
  ~set() = default;
  void add(V value);
};

#endif  // SET_H
