#include "python.h"

void python_initialize() {
    None = new NoneType();
    True = new Bool(true);
    False = new Bool(false);
}
