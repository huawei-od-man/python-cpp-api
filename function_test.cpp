#include "python.h"

#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <string>
#include <functional>

#include "tuple.h"

// 测试用的简单函数和类
int add(int a, int b) { return a + b; }

struct A {
  int member_function(int a) { return a + 1; }
  int const_member_function(int a) const { return a + 2; }

  void print_member_function(int a) {
    std::cout << "Member function result: " << (a + 1) << std::endl;
  }

  void print_const_member_function(int a) const {
    std::cout << "Const member function result: " << (a + 2) << std::endl;
  }
};

// 测试用的简单函数和类
void print_sum(int a, int b) {
  std::cout << "Sum: " << (a + b) << std::endl;
}

// 测试 function 类
class FunctionTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // 初始化操作
  }

  void TearDown() override {
    // 清理操作
  }
};

// 测试默认构造函数
TEST_F(FunctionTest, DefaultConstructor) {
  function f;
  EXPECT_EQ(f.argument_count(), 0);
}

// 测试普通函数的构造函数
TEST_F(FunctionTest, FunctionPointerConstructor) {
  function f(add);
  EXPECT_EQ(f.argument_count(), 2);

  // 调用并验证结果
  tuple args{1, 2}; // 假设 tuple 可以存储参数
  ref result = f(args);
  EXPECT_EQ(result, ref{3});
}

// 测试 std::function 的构造函数
TEST_F(FunctionTest, StdFunctionConstructor) {
  std::function<int(int, int)> std_func = add;
  function f(std_func);
  EXPECT_EQ(f.argument_count(), 2);

  // 调用并验证结果
  tuple args{1, 2}; // 假设 tuple 可以存储参数
  ref result = f(args);
  EXPECT_EQ(result, ref{3});
}

// 测试成员函数的构造函数
TEST_F(FunctionTest, MemberFunctionConstructor) {
  A a;
  function f(&A::member_function);
  EXPECT_EQ(f.argument_count(), 2);

  // 调用并验证结果
  tuple args{a, 1}; // 假设 tuple 可以存储参数
  ref result = f(args);
  EXPECT_EQ(result, ref(2));
}

// 测试 const 成员函数的构造函数
TEST_F(FunctionTest, ConstMemberFunctionConstructor) {
  const A a;
  function f(&A::const_member_function);
  EXPECT_EQ(f.argument_count(), 2);

  // 调用并验证结果
  tuple args{a, 2}; // 假设 tuple 可以存储参数
  ref result = f(args);
  EXPECT_EQ(result, ref(4));
}

// 测试 Lambda 表达式的构造函数
TEST_F(FunctionTest, LambdaConstructor) {
  auto lambda = [](int a, int b) { return a + b; };
  function f(lambda);
  EXPECT_EQ(f.argument_count(), 2);

  // 调用并验证结果
  tuple args{1, 2}; // 假设 tuple 可以存储参数
  ref result = f(args);
  EXPECT_EQ(result, ref(3));
}

// 测试拷贝构造函数
TEST_F(FunctionTest, CopyConstructor) {
  function f1(add);
  function f2(f1);
  EXPECT_EQ(f2.argument_count(), 2);

  // 调用并验证结果
  tuple args{1, 2}; // 假设 tuple 可以存储参数
  ref result = f2(args);
  EXPECT_EQ(result, ref(3));
}

// 测试移动构造函数
TEST_F(FunctionTest, MoveConstructor) {
  function f1(add);
  function f2(std::move(f1));
  EXPECT_EQ(f2.argument_count(), 2);

  // 调用并验证结果
  tuple args{1, 2}; // 假设 tuple 可以存储参数
  ref result = f2(args);
  EXPECT_EQ(result, ref(3));
}

// 测试赋值运算符
TEST_F(FunctionTest, AssignmentOperator) {
  function f1(add);
  function f2;
  f2 = f1;
  EXPECT_EQ(f2.argument_count(), 2);

  // 调用并验证结果
  tuple args{1, 2}; // 假设 tuple 可以存储参数
  ref result = f2(args);
  EXPECT_EQ(result, ref(3));
}

// 测试移动赋值运算符
TEST_F(FunctionTest, MoveAssignmentOperator) {
  function f1(add);
  function f2;
  f2 = std::move(f1);
  EXPECT_EQ(f2.argument_count(), 2);

  // 调用并验证结果
  tuple args{1, 2}; // 假设 tuple 可以存储参数
  ref result = f2(args);
  EXPECT_EQ(result, ref(3));
}

// 测试 operator()
TEST_F(FunctionTest, CallOperator) {
  function f(add);
  tuple args{1, 2}; // 假设 tuple 可以存储参数
  ref result = f(args);
  EXPECT_EQ(result, ref(3));
}

// 测试 operator<<
TEST_F(FunctionTest, StreamOperator) {
  function f(add);
  std::ostringstream oss;
  oss << f;
  std::string output = oss.str();
  EXPECT_FALSE(output.empty());
}


// 测试返回 void 的 std::function 的构造函数
TEST_F(FunctionTest, VoidStdFunctionConstructor) {
  std::function<void(int, int)> std_func = print_sum;
  function f(std_func);
  EXPECT_EQ(f.argument_count(), 2);

  // 调用并验证结果
  tuple args{1, 2}; // 假设 tuple 可以存储参数
  ref result = f(args);
  EXPECT_EQ(result, ref());
}

// 测试返回 void 的成员函数的构造函数
TEST_F(FunctionTest, VoidMemberFunctionConstructor) {
  A a;
  function f(&A::print_member_function);
  EXPECT_EQ(f.argument_count(), 2);

  // 调用并验证结果
  tuple args{a, 2}; // 假设 tuple 可以存储参数
  ref result = f(args);
  EXPECT_EQ(result, ref());
}

// 测试返回 void 的 const 成员函数的构造函数
TEST_F(FunctionTest, VoidConstMemberFunctionConstructor) {
  const A a;
  function f(&A::print_const_member_function);
  EXPECT_EQ(f.argument_count(), 2);

  // 调用并验证结果
  tuple args{a, 2}; // 假设 tuple 可以存储参数
  ref result = f(args);
  EXPECT_EQ(result, ref());
}

// 测试返回 void 的 Lambda 表达式的构造函数
TEST_F(FunctionTest, VoidLambdaConstructor) {
  auto lambda = [](int a, int b) { std::cout << "Lambda result: " << (a + b) << std::endl; };
  function f(lambda);
  EXPECT_EQ(f.argument_count(), 2);

  // 调用并验证结果
  tuple args{1, 2}; // 假设 tuple 可以存储参数
  ref result = f(args);
  EXPECT_EQ(result, ref());
}
