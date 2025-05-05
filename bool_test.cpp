#include "bool.h"  // 假设 bool_ 类定义在这个头文件中
#include "ref.h"

#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

// 测试类
class BoolTest : public ::testing::Test {
 protected:
  void SetUp() override {
    trueBool = bool_(true);
    falseBool = bool_(false);
  }

  bool_ trueBool;
  bool_ falseBool;
};

// 测试默认构造函数
TEST_F(BoolTest, DefaultConstructor) {
  bool_ b;
  EXPECT_FALSE(b.value());
}

// 测试布尔值构造函数
TEST_F(BoolTest, BoolConstructor) {
  bool_ b(true);
  EXPECT_TRUE(b.value());
}

// 测试 ref 构造函数
TEST_F(BoolTest, RefConstructor) {
  bool_ b(True);
  EXPECT_TRUE(b.value());
}

// 测试布尔值转换
TEST_F(BoolTest, BoolConversion) {
  bool_ b(true);
  EXPECT_TRUE(static_cast<bool>(b));
}

// 测试逻辑非运算符
TEST_F(BoolTest, LogicalNot) {
  EXPECT_FALSE(!trueBool);
  EXPECT_TRUE(!falseBool);
}

// 测试等于运算符
TEST_F(BoolTest, EqualityOperator) {
  EXPECT_TRUE(trueBool == trueBool);
  EXPECT_FALSE(trueBool == falseBool);
}

// 测试小于运算符
TEST_F(BoolTest, LessThanOperator) {
  EXPECT_FALSE(trueBool < falseBool);
  EXPECT_TRUE(falseBool < trueBool);
}

// 测试输出运算符
TEST_F(BoolTest, StreamOperator) {
  std::ostringstream oss;
  oss << trueBool;
  EXPECT_EQ(oss.str(), "True");

  oss.str("");
  oss << falseBool;
  EXPECT_EQ(oss.str(), "False");
}

// 测试赋值运算符
TEST_F(BoolTest, AssignmentOperator) {
  bool_ b;
  b = trueBool;
  EXPECT_TRUE(b.value());

  b = falseBool;
  EXPECT_FALSE(b.value());
}

// 测试拷贝构造函数
TEST_F(BoolTest, CopyConstructor) {
  bool_ b(trueBool);
  EXPECT_TRUE(b.value());
}

// 测试移动构造函数
TEST_F(BoolTest, MoveConstructor) {
  bool_ b(std::move(trueBool));
  EXPECT_TRUE(b.value());
}

// 测试拷贝赋值运算符
TEST_F(BoolTest, CopyAssignmentOperator) {
  bool_ b;
  b = trueBool;
  EXPECT_TRUE(b.value());
}

// 测试移动赋值运算符
TEST_F(BoolTest, MoveAssignmentOperator) {
  bool_ b;
  b = std::move(trueBool);
  EXPECT_TRUE(b.value());
}

TEST_F(BoolTest, BoolGlobals) {
  EXPECT_FALSE(False) << False->to_bool();
  EXPECT_TRUE(True) << True->to_bool();
}

