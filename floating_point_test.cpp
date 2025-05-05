#include "floating_point.h"  // 假设 float_ 类定义在这个头文件中

#include <gtest/gtest.h>

#include <limits>

// 测试类
class FloatTest : public ::testing::Test {
 protected:
  float_ zero = 0.0_f;
  float_ one = 1.0_f;
  float_ two = 2.0_f;
  float_ negativeOne = -1.0_f;
  float_ smallValue = float_::epsilon();
  float_ largeValue = float_::maximum();
};

// 测试默认构造函数
TEST_F(FloatTest, DefaultConstructor) {
  float_ f;
  EXPECT_EQ(f.value(), 0.0);
}

// 测试类型转换构造函数
TEST_F(FloatTest, TypeConversionConstructors) {
  float_ fromLongDouble(1.0L);
  float_ fromDouble(1.0);
  float_ fromFloat(1.0f);

  EXPECT_EQ(fromLongDouble.value(), 1.0L);
  EXPECT_EQ(fromDouble.value(), 1.0);
  EXPECT_EQ(fromFloat.value(), 1.0f);
}

// 测试类型转换
TEST_F(FloatTest, TypeConversions) {
  long double ld = static_cast<long double>(zero);
  double d = static_cast<double>(zero);
  float f = static_cast<float>(zero);

  EXPECT_EQ(ld, 0.0L);
  EXPECT_EQ(d, 0.0);
  EXPECT_EQ(f, 0.0f);
}

// 测试一元负运算符
TEST_F(FloatTest, UnaryMinus) {
  float_ negated = -one;
  EXPECT_EQ(negated.value(), -1.0);
}

// 测试加法运算符
TEST_F(FloatTest, Addition) {
  float_ result = one + one;
  EXPECT_EQ(result.value(), 2.0);
}

// 测试减法运算符
TEST_F(FloatTest, Subtraction) {
  float_ result = two - one;
  EXPECT_EQ(result.value(), 1.0);
}

// 测试乘法运算符
TEST_F(FloatTest, Multiplication) {
  float_ result = two * two;
  EXPECT_EQ(result.value(), 4.0);
}

// 测试除法运算符
TEST_F(FloatTest, Division) {
  float_ result = two / one;
  EXPECT_EQ(result.value(), 2.0);
}

// 测试比较运算符
TEST_F(FloatTest, ComparisonOperators) {
  EXPECT_TRUE(one == one);
  EXPECT_FALSE(one == two);

  EXPECT_TRUE(one < two);
  EXPECT_FALSE(two < one);
}

// 测试静态方法
TEST_F(FloatTest, StaticMethods) {
  EXPECT_EQ(float_::minimum().value(), LDBL_MIN);
  EXPECT_EQ(float_::maximum().value(), LDBL_MAX);
  EXPECT_EQ(float_::epsilon().value(), LDBL_EPSILON);
}

// 测试输出运算符
TEST_F(FloatTest, StreamOperator) {
  std::ostringstream oss;
  oss << one;
  EXPECT_EQ(oss.str(), "1");
}
