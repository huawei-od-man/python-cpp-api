#include "python.h"

void python_initialize() {
    None = new NoneType();
    True = new bool_(true);
    False = new bool_(false);
}
