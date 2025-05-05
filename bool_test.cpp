#include <gtest/gtest.h>

#include <sstream>

#include "bool.h"
#include "ref.h"

TEST(BoolTest, BoolGlobals) {
  EXPECT_FALSE(False) << False->to_bool();
  EXPECT_TRUE(True) << True->to_bool();
}

TEST(BoolTest, Format) {
    std::ostringstream oss;
    oss << bool_{false} << " " << bool_{true};
    EXPECT_EQ(oss.str(), "False True");
}
