#include <gtest/gtest.h>

#include "python.h"

struct A {};

TEST(TestFormat, ClassWithInsertOperator) {
  A a{};
  auto s = "{}"_s.format({a});
  EXPECT_TRUE(s.startswith("<A object at"));
  EXPECT_TRUE(s.endswith(">"));
}

TEST(TestFormat, FormatBoolAndNone) {
  EXPECT_EQ(str(False), "False");
  EXPECT_EQ(str(True), "True");
  EXPECT_EQ(str(None), "None");
}

