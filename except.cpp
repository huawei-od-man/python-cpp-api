#include "except.h"

Exception::Exception(str message) : _message(std::move(message)) {}

Exception::Exception(const char* message) {}

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

KeyError::KeyError(str message) : Exception(std::move(message)) {}
KeyError::KeyError(const char* message) : KeyError(str(message)) {}

ValueError::ValueError(str message) : Exception(std::move(message)) {}
ValueError::ValueError(const char* message) : ValueError(str(message)) {}

TypeError::TypeError(str message) : Exception(std::move(message)) {}
TypeError::TypeError(const char* message) : TypeError(str(message)) {}

OverflowError::OverflowError(str message) : Exception(std::move(message)) {}

OverflowError::OverflowError(const char* message)
    : OverflowError(str(message)) {}

UnderflowError::UnderflowError(str message) : Exception(std::move(message)) {}
UnderflowError::UnderflowError(const char* message)
    : UnderflowError(str(message)) {}
