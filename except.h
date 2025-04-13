#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <stdexcept>
#include <string>

#include "forward.h"
#include "str.h"

class Exception : public std::exception {
 public:
  explicit Exception(str message) : _message(std::move(message)) {};
  const char *what() const noexcept override {
    return _message.c_str();
  }

  const str& message() const noexcept { return _message; }

 private:
  str _message;
};

class NotImplementedError : public Exception {
 public:
  explicit NotImplementedError(str message) : Exception(std::move(message)) {}
};

class IndexError : public Exception {
 public:
  explicit IndexError(str message) : Exception(std::move(message)) {}
};

#endif
