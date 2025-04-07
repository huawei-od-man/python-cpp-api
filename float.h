#ifndef FLOAT_H
#define FLOAT_H

#include "forward.h"
#include "object.h"

class Float : public Object {
 public:
  explicit Float(double value);
  ~Float() override;
  float_ __float__() override;
  str __str__() override;
  double value() const { return _value; }

 private:
  double _value;
};

float_ operator""_F(long double value);

#endif
