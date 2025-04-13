#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <stdexcept>

#include "forward.h"
#include "str.h"

class Exception : public std::exception {
 public:
  explicit Exception(str message);
  explicit Exception(const char* message);

  const char* what() const noexcept override { return _message.c_str(); }

  const str& message() const noexcept { return _message; }

 private:
  str _message;
};

class NotImplementedError : public Exception {
 public:
  explicit NotImplementedError(str message);
  explicit NotImplementedError(const char* message);
};

class IndexError : public Exception {
 public:
  explicit IndexError(str message);
  explicit IndexError(const char* message);
};

class ZeroDivisionError : public Exception {
 public:
  explicit ZeroDivisionError(str message);
  explicit ZeroDivisionError(const char* message);
};

class KeyError : public Exception {
 public:
  explicit KeyError(str message);
  explicit KeyError(const char* message);
};

class ValueError : public Exception {
 public:
  explicit ValueError(str message);
  explicit ValueError(const char* message);
};

#endif
