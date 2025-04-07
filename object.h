#ifndef OBJECT_H
#define OBJECT_H

#include <atomic>

#include "forward.h"
#include "ref.h"

class Object {
 public:
  Object();
  virtual ~Object() = default;
  virtual bool_ __bool__();
  virtual str __str__();
  virtual int_ __int__();
  virtual float_ __float__();

  virtual bool_ __eq__(object other);
  virtual bool_ __ne__(object other);
  virtual bool_ __lt__(ref<Object> other);
  virtual bool_ __le__(ref<Object> other);
  virtual bool_ __gt__(ref<Object> other);
  virtual bool_ __ge__(ref<Object> other);

  virtual object __getitem__(object key);
  virtual void __setitem__(object key, object value);
  virtual void __delitem__(object key);
  virtual int_ __len__();

  virtual object __add__(object other);
  virtual object __sub__(object other);
  virtual object __mul__(object other);
  virtual object __truediv__(object other);
  virtual object __mod__(object other);
  virtual object __pow__(object other);

  void add_ref();
  void dec_ref();
  void release();
  int32_t ref_count() const;

 private:
  std::atomic_int32_t _ref_count;
};

#endif
