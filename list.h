#ifndef LIST_H
#define LIST_H

#include <stdexcept>
#include <vector>

#include "object.h"
#include "ref.h"

class List : public Object {
 public:
  List() = default;
  ~List() override;
  bool_ __eq__(object other) override;
  bool_ __ne__(object other) override;
  str __str__() override;
  int_ __len__() override;
  object __getitem__(object index) override;
  void __setitem__(object index, object value) override;
  void __delitem__(object index) override;

  virtual void insert(object index, object value);
  virtual void append(object value);

 private:
  std::vector<object> _items;
};

#endif
