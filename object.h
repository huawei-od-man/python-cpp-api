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
  explicit operator bool() const { return to_bool(); }

  virtual float_ to_float() const;
  operator double() const;

  virtual size_t hash() const { return reinterpret_cast<uintptr_t>(this); }
  virtual size_t size() const;
  virtual const char* type_name() const { return "object"; }

  virtual void format(std::ostream& os) const {
    os << type_name() << " object at " << this;
  }
  friend std::ostream& operator<<(std::ostream& os, const object& obj) {
    obj.format(os);
    return os;
  }

  virtual bool eq(const object& other) const { return this == &other; }
  virtual bool neq(const object& other) const { return !eq(other); }
  friend bool operator==(const object& lhs, const object& rhs) {
    return lhs.eq(rhs);
  }
  friend bool operator!=(const object& lhs, const object& rhs) {
    return lhs.neq(rhs);
  }

  virtual bool lt(const object& other) const { return this < &other; }
  friend bool operator<(const object& lhs, const object& rhs) {
    return lhs.lt(rhs);
  }

  virtual ref call(tuple args);

  template <typename... Args>
  ref operator()(Args&&... args);

  virtual iterator get_iter() const;
  const iterator begin() const;
  const iterator end() const;

  virtual ref next();

};

#endif  // OBJECT_H
