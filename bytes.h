#ifndef BYTES_H
#define BYTES_H
#include <utility>
#include <vector>

class bytes {
 public:
  bytes() = default;

  size_t size() const { return _data.size(); }

  bool operator==(const bytes& other) const;

  const std::vector<uint8_t>& value() const {
    return _data;
  }

 private:
  std::vector<uint8_t> _data;
};


#endif  // BYTES_H
