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

  virtual float_type to_float() const = 0;
  operator float_type() const { return to_float(); }

  virtual size_t hash() const { return reinterpret_cast<uintptr_t>(this); }
  virtual size_t size() const = 0;
  virtual const char* type_name() const {
    return "object";
  }

  void format(std::ostream& os) const {
    os << type_name() << " object at " << this;
  }
  friend std::ostream& operator<<(std::ostream& os, const object& obj) {
    obj.format(os);
    return os;
  }

  virtual bool eq(const object& other) const {
    return this == &other;
  }
  virtual bool neq(const object& other) const {
    return !eq(other);
  }
  friend bool operator==(const object& lhs, const object& rhs) {
    return lhs.eq(rhs);
  }
  friend bool operator!=(const object& lhs, const object& rhs) {
    return lhs.neq(rhs);
  }

  virtual bool lt(const object& other) const {
    return this < &other;
  }
  friend bool operator<(const object& lhs, const object& rhs) {
    return lhs.lt(rhs);
  }
};


#endif  // OBJECT_H
