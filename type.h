#ifndef TYPE_H
#define TYPE_H
#include <iosfwd>

#include "str.h"
#include "tuple.h"
#include "dict.h"

class typeinfo {
 public:
  explicit typeinfo(const str& name, const tuple& bases, const dict& attrs);

  const str& name() const { return _name; }

 private:
  str _name;
  tuple _bases;
  dict _attrs;
};

std::ostream& operator<<(std::ostream& os, const typeinfo& obj);

str repr(const typeinfo& obj);

bool operator==(const typeinfo& lhs, const typeinfo& rhs);

bool operator<(const typeinfo& lhs, const typeinfo& rhs);

#endif
