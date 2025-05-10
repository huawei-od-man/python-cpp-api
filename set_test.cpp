#include "set.h"  // 假设 set 类定义在这个头文件中
#include "ref.tcc"

#include <gtest/gtest.h>

#include <iostream>

// 测试类
class SetTest : public ::testing::Test {
 protected:
  set s;
};

// 测试默认构造函数
TEST_F(SetTest, DefaultConstructor) {
  EXPECT_FALSE(s);
  EXPECT_EQ(s.size(), 0);
}

// 测试初始化列表构造函数
TEST_F(SetTest, InitializerListConstructor) {
  set s({1, 2, 3});
  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains(ref(1)));
  EXPECT_TRUE(s.contains(ref(2)));
  EXPECT_TRUE(s.contains(ref(3)));
}

// 测试布尔值转换
TEST_F(SetTest, BoolConversion) {
  set emptySet;
  EXPECT_FALSE(static_cast<bool>(emptySet));

  s.add(ref(1));
  EXPECT_TRUE(static_cast<bool>(s));
}

// 测试添加元素
TEST_F(SetTest, AddElement) {
  s.add(ref(1));
  s.add(ref(2));
  EXPECT_EQ(s.size(), 2);
  EXPECT_TRUE(s.contains(ref(1)));
  EXPECT_TRUE(s.contains(ref(2)));
}

// 测试删除元素
TEST_F(SetTest, RemoveElement) {
  s.add(ref(1));
  s.add(ref(2));
  s.remove(ref(1));
  EXPECT_EQ(s.size(), 1);
  EXPECT_FALSE(s.contains(ref(1)));
  EXPECT_TRUE(s.contains(ref(2)));
}

// 测试清空集合
TEST_F(SetTest, ClearSet) {
  s.add(ref(1));
  s.add(ref(2));
  s.clear();
  EXPECT_EQ(s.size(), 0);
  EXPECT_FALSE(s.contains(ref(1)));
  EXPECT_FALSE(s.contains(ref(2)));
}

// 测试查找元素
TEST_F(SetTest, ContainsElement) {
  s.add(ref(1));
  s.add(ref(2));
  EXPECT_TRUE(s.contains(ref(1)));
  EXPECT_TRUE(s.contains(ref(2)));
  EXPECT_FALSE(s.contains(ref(3)));
}

// 测试输出运算符
TEST_F(SetTest, StreamOperator) {
  s.add(ref(1));
  s.add(ref(2));
  std::ostringstream oss;
  oss << s;
  EXPECT_TRUE(oss.str() == "{1, 2}" || oss.str() == "{2, 1}");
}
