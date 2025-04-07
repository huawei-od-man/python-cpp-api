#ifndef NONE_H
#define NONE_H

#include "object.h"

class NoneType : public Object {
public:
    NoneType() {}
    ~NoneType() override {}

    bool_ __bool__() override;
    bool_ __eq__(object other) override;
    bool_ __ne__(object other) override;

    str __str__() override;
};

#endif // NONE_H
