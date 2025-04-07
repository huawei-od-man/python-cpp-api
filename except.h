#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <stdexcept>
#include <string>

#include "forward.h"

class Exception : public std::exception {
 public:
  explicit Exception(const char *message);
  const char *what() const noexcept override;

 private:
  std::string _message;
};

class NotImplementedError : public Exception {
public:
    explicit NotImplementedError(const char *message);
};

#endif
