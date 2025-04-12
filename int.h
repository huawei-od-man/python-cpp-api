#ifndef INT_H
#define INT_H

#include "object.h"

class Int : public object {
public:
    explicit Int(int value);
    ~Int() override;

    bool_ __eq__(object other) override;
    bool_ __ne__(object other) override;

    bool_ __lt__(object other) override;
    bool_ __le__(object other) override;
    bool_ __gt__(object other) override;
    bool_ __ge__(object other) override;
    object __add__(object other) override;
    object __sub__(object other) override;
    object __mul__(object other) override;
    object __truediv__(object other) override;
    object __mod__(object other) override;
    object __pow__(object other) override;
    object __neg__();
    object __abs__();
    object __floordiv__(object other);

    int_ __int__() override;
    str __str__() override;

private:
    int _value;
};

int_ operator""_I(unsigned long long value);

#endif
