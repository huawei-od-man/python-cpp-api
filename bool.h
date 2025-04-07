#ifndef BOOL_H
#define BOOL_H

#include "object.h"

class Bool : public Object {
public:
    explicit Bool(bool value);
    ~Bool() override;

    bool_ __eq__(object other) override;
    bool_ __ne__(object other) override;

    bool_ __bool__() override;
    str __str__() override;

    bool value() const {
        return _value;
    }

private:
    bool _value;
};


#endif
