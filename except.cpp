#include "except.h"

Exception::Exception(str message) : _message(std::move(message)) {}

NotImplementedError::NotImplementedError(str message)
    : Exception(std::move(message)) {}

NotImplementedError::NotImplementedError(const char* message)
    : NotImplementedError(str(message)) {}

IndexError::IndexError(str message) : Exception(std::move(message)) {}

IndexError::IndexError(const char* message) : IndexError(str(message)) {}

ZeroDivisionError::ZeroDivisionError(str message)
    : Exception(std::move(message)) {}
    
ZeroDivisionError::ZeroDivisionError(const char* message)
    : ZeroDivisionError(str(message)) {}
