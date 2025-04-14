#ifndef OBJECT_H
#define OBJECT_H
#include <iostream>

#include "forward.h"


class object {
 public:
  object() = default;
  virtual ~object() = default;

  // To prevent slicing objects.
  object(const object&) = delete;
  object(object&&) = delete;
  object& operator=(const object&) = delete;
  object& operator=(object&&) = delete;

  virtual str to_str() const;

  virtual bool to_bool() const { return true; }

  virtual float_ to_float() const;

  virtual size_t hash() const { return reinterpret_cast<uintptr_t>(this); }
  virtual size_t size() const;
  virtual const char* type_name() const { return "object"; }

  virtual void format(std::ostream& os) const {
    os << "<" << type_name() << " object at " << this << ">";
  }

  virtual bool eq(const object& other) const { return this == &other; }
  virtual bool neq(const object& other) const { return !eq(other); }

  virtual bool lt(const object& other) const { return this < &other; }

  virtual ref call(tuple args);

  virtual iterator get_iter() const;
  const iterator begin() const;
  const iterator end() const;

  virtual ref next();

  virtual ref add(ref other) const;
  virtual ref sub(ref other) const;
  virtual ref mul(ref other) const;
  virtual ref div(ref other) const;

};

#endif  // OBJECT_H
