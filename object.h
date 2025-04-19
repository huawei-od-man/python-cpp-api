#ifndef OBJECT_H
#define OBJECT_H
#include <iosfwd>
#include <utility>

#include "forward.h"

class object {
 public:
  object() = default;
  virtual ~object() = default;

  object(const object&) = default;
  object(object&&) noexcept = default;
  object& operator=(const object&) = default;
  object& operator=(object&&) noexcept  = default;

  virtual str to_str() const;

  virtual bool to_bool() const { return true; }

  virtual float_ to_float() const;

  virtual std::size_t hash() const { return reinterpret_cast<uintptr_t>(this); }
  virtual std::size_t size() const;
  virtual void format(std::ostream& os) const;

  virtual bool eq(ref other) const;
  virtual bool neq(ref other) const;
  virtual bool lt(ref other) const;

  virtual ref call(const tuple& args);

  virtual iterator get_iter() const;
  const iterator begin() const;
  const iterator end() const;

  virtual ref next();

  virtual ref add(ref other) const;
  virtual ref sub(ref other) const;
  virtual ref mul(ref other) const;
  virtual ref div(ref other) const;
  virtual ref type() const;
};

std::ostream& operator<<(std::ostream& os, const object& obj);

#endif  // OBJECT_H
