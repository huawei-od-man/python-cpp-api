#include "ref.h"

#include "except.h"

ref operator+(ref lhs, ref rhs) {
    if (lhs && rhs) {
        try {
            return lhs->add(rhs);
        } catch (NotImplementedError&) {
            return rhs->add(lhs);
        }
    }
    return {};
}
