#include "list.h"

#include "int.h"

int_ List::__len__() { return new Int(_items.size()); }