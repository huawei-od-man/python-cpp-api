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

class bool_ {
public:
    bool_(bool value) : _ref(value ? True : False) {}

    bool_(ref<Bool> ref) : _ref(ref) {}

    bool_(const bool_& other) : _ref(other._ref) {}
    bool_(bool_&& other) noexcept : _ref(std::move(other._ref)) {}
    bool_& operator=(const bool_& other) {
        if (this != &other) {
            _ref = other._ref;
        }
        return *this;
    }
    bool_& operator=(bool_&& other) noexcept {
        if (this != &other) {
            _ref = std::move(other._ref);
        }
        return *this;
    }
    operator bool() const {
        return _ref->value();
    }
private:
    ref<Bool> _ref;
};

#endif
