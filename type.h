#ifndef TYPE_H
#define TYPE_H

#include <iostream>

#include "dict.h"
#include "forward.h"
#include "ref.h"
#include "str.h"
#include "tuple.h"

struct typeinfo {
  // typeinfo(const str& name, const tuple& bases, const dict& attrs)
  //     : name(name), bases(bases), attrs(attrs) {}
  str name;
  tuple bases;
  dict attrs;
};

inline str repr(const typeinfo& obj) { return "<class '" + obj.name + "'>"; }

template <typename T>
std::string get_type_name() {
  // Use __PRETTY_FUNCTION__ to get the type name in a more readable format
#ifdef __GNUC__
  std::string s = __PRETTY_FUNCTION__;
  size_t start = s.find("T = ");
  if (start != std::string::npos) {
    start += 4;  // Length of "T = "
    size_t end = s.find(']', start);
    return s.substr(start, end - start);
  }
  return "unknown";
#elif defined(_MSC_VER)
  std::string s = __FUNCSIG__;
  size_t start = s.find("T = ");
  if (start != std::string::npos) {
    start += 4;  // Length of "T = "
    size_t end = s.find('>', start);
    return s.substr(start, end - start);
  }
  return "unknown";
#else
  return typeid(T).name();
#endif
}

template<> ref type<typeinfo>();

ref type(ref obj);

ref type(const str& name, const tuple& bases, const dict& attrs);

#endif
