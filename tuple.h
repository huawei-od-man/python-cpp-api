#ifndef TUPLE_H
#define TUPLE_H

#include "object.h"
#include <vector>

class Tuple : public Object {
public:
    Tuple() = default;
    ~Tuple() override;

    bool_ __eq__(object other) override;
    bool_ __ne__(object other) override;

    object __getitem__(object key) override;
    void __setitem__(object key, object value) override;
    
    str __str__() override;


private:
    std::vector<object> _elements;
};

#endif // TUPLE_H
