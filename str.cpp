#include "str.h"

#include "object.h"
#include "ref.h"

str::str(ref obj) : str(obj->to_str()) {}
