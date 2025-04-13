#ifndef SET_H
#define SET_H

#include <unordered_set>

#include "ref.h"

class set {
  public:

  private:
  std::unordered_set<ref> _items;
};

#endif  // SET_H
