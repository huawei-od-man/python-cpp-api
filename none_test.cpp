#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include "none.h"  // 假设 NoneType 类定义在这个头文件中

// 测试类
class NoneTypeTest : public ::testing::Test {
 protected:
  NoneType none;
};

// 测试默认构造函数
TEST_F(NoneTypeTest, DefaultConstructor) {
  NoneType n;
  EXPECT_FALSE(static_cast<bool>(n));  // 测试布尔值转换
}

// 测试布尔值转换
TEST_F(NoneTypeTest, BoolConversion) { EXPECT_FALSE(static_cast<bool>(none)); }

// 测试比较运算符
TEST_F(NoneTypeTest, ComparisonOperators) {
  NoneType n1;
  NoneType n2;

  EXPECT_TRUE(n1 == n2);   // 测试相等运算符
  EXPECT_FALSE(n1 != n2);  // 测试不等运算符
  EXPECT_FALSE(n1 < n2);   // 测试小于运算符
}

// 测试输出运算符
TEST_F(NoneTypeTest, StreamOperator) {
  std::ostringstream oss;
  oss << none;
  EXPECT_EQ(oss.str(), "None");
}
