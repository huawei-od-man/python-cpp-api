#ifndef PYTHONCPPAPI_OBJECT_H
#define PYTHONCPPAPI_OBJECT_H
#include <atomic>

#include "forward.h"

class Object
{
public:
    virtual ~Object();

protected:
    virtual auto __str__() -> str;
private:
    friend class object;

    std::atomic_int32_t _refcnt{};
};

class object {
public:
    
private:
    Object* _obj{};
};

#endif
