#include "str.h"  // 假设 str 类定义在这个头文件中
#include "ref.h"
#include "tuple.h"
#include "list.h"
#include "ref.tcc"

#include <gtest/gtest.h>

#include <sstream>
#include <string>

// 测试类
class StrTest : public ::testing::Test {
 protected:
  void SetUp() override {
    s1 = str("hello");
    s2 = str("world");
    s3 = str("Hello, World!");
    s4 = str("12345");
    s5 = str("abc123");
    s6 = str("ABC");
    s7 = str(" ");
    s8 = str("\t\n");
    s9 = str("a\tb");
    s10 = str("Python");
    s11 = str("python");
    s12 = str("Python3.8");
    s13 = str("Python_3_8");
    s14 = str("Python 3.8");
  }

  str s1;
  str s2;
  str s3;
  str s4;
  str s5;
  str s6;
  str s7;
  str s8;
  str s9;
  str s10;
  str s11;
  str s12;
  str s13;
  str s14;
};

// 测试构造函数
TEST_F(StrTest, Constructors) {
  str s1("hello");
  str s2(std::string("world"));
  str s3(std::string_view("test"));
  char temp[] = "hello";
  str s4(temp);

  EXPECT_EQ(s1.value(), "hello");
  EXPECT_EQ(s2.value(), "world");
  EXPECT_EQ(s3.value(), "test");
  EXPECT_EQ(s4.value(), "hello");
}

// 测试布尔值转换
TEST_F(StrTest, BoolConversion) {
  str empty;
  str nonEmpty("test");

  EXPECT_FALSE(static_cast<bool>(empty));
  EXPECT_TRUE(static_cast<bool>(nonEmpty));
}

// 测试比较运算符
TEST_F(StrTest, ComparisonOperators) {
  EXPECT_TRUE(s1 == str("hello"));
  EXPECT_FALSE(s1 == s2);

  EXPECT_TRUE(s1 < s2);
  EXPECT_FALSE(s2 < s1);
}

// 测试大小
TEST_F(StrTest, Size) {
  EXPECT_EQ(s1.size(), 5);
  EXPECT_EQ(s3.size(), 13);
}

// 测试 c_str
TEST_F(StrTest, CStr) {
  const char* cstr = s1.c_str();
  EXPECT_STREQ(cstr, "hello");
}

// 测试 value
TEST_F(StrTest, Value) {
  std::string value = s1.value();
  EXPECT_EQ(value, "hello");
}

// 测试 format
TEST_F(StrTest, Format) {
  tuple args = tuple({ref("world")});
  str formatted = str("Hello, {}!").format(args);
  EXPECT_EQ(formatted.value(), "Hello, world!");
}

// 测试 capitalize
TEST_F(StrTest, Capitalize) {
  str capitalized = s3.capitalize();
  EXPECT_EQ(capitalized.value(), "Hello, world!");
}

// 测试 casefold
TEST_F(StrTest, Casefold) {
  str folded = s6.casefold();
  EXPECT_EQ(folded.value(), "abc");
}

// 测试 center
TEST_F(StrTest, Center) {
  str centered = s1.center(11, str("-"));
  EXPECT_EQ(centered.value(), "---hello---");
}

// 测试 count
TEST_F(StrTest, Count) {
  size_t count = s1.count(str("l"), 0, 5);
  EXPECT_EQ(count, 2);
}

// 测试 endswith
TEST_F(StrTest, Endswith) {
  EXPECT_TRUE(s3.endswith(str("World!")));
  EXPECT_FALSE(s3.endswith(str("hello")));
}

// 测试 expandtabs
TEST_F(StrTest, Expandtabs) {
  str expanded = s9.expandtabs(4);
  EXPECT_EQ(expanded.value(), "a   b");
}

// 测试 split
TEST_F(StrTest, Split) {
  list splitList = s3.split(str(" "));
  EXPECT_EQ(splitList.size(), 2);
  EXPECT_EQ(splitList[0], "Hello,"_s);
  EXPECT_EQ(splitList[1], "World!"_s);
}

// 测试 startswith
TEST_F(StrTest, Startswith) {
  EXPECT_TRUE(s3.startswith(str("Hello")));
  EXPECT_FALSE(s3.startswith(str("world")));
}

// 测试 find
TEST_F(StrTest, Find) {
  int pos = s3.find(str("World"), 0, s3.size());
  EXPECT_EQ(pos, 7);
}

// 测试 format_map
// TEST_F(StrTest, FormatMap) {
//   ref mapping = ref("world");
//   str formatted = str("Hello, {}!").format_map(mapping);
//   EXPECT_EQ(formatted.value(), "Hello, world!");
// }

// 测试 index
TEST_F(StrTest, Index) {
  int pos = s3.index(str("World"), 0, s3.size());
  EXPECT_EQ(pos, 7);
}

// 测试 isalnum
TEST_F(StrTest, Isalnum) {
  EXPECT_TRUE(s5.isalnum());
  EXPECT_FALSE(s3.isalnum());
}

// 测试 isalpha
TEST_F(StrTest, Isalpha) {
  EXPECT_TRUE(s6.isalpha());
  EXPECT_FALSE(s5.isalpha());
}

// 测试 isdecimal
TEST_F(StrTest, Isdecimal) {
  EXPECT_TRUE(s4.isdecimal());
  EXPECT_FALSE(s5.isdecimal());
}

// 测试 isdigit
TEST_F(StrTest, Isdigit) {
  EXPECT_TRUE(s4.isdigit());
  EXPECT_FALSE(s5.isdigit());
}

// 测试 isidentifier
TEST_F(StrTest, Isidentifier) {
  EXPECT_TRUE(s13.isidentifier());
  EXPECT_FALSE(s14.isidentifier());
}

// 测试 islower
TEST_F(StrTest, Islower) {
  EXPECT_TRUE(s11.islower());
  EXPECT_FALSE(s6.islower());
}

// 测试 isnumeric
TEST_F(StrTest, Isnumeric) {
  EXPECT_TRUE(s4.isnumeric());
  EXPECT_FALSE(s5.isnumeric());
}

// 测试 isprintable
TEST_F(StrTest, Isprintable) {
  EXPECT_TRUE(s1.isprintable());
  EXPECT_FALSE(s8.isprintable());
}

// 测试 isspace
TEST_F(StrTest, Isspace) {
  EXPECT_TRUE(s7.isspace());
  EXPECT_FALSE(s1.isspace());
}

// 测试 istitle
TEST_F(StrTest, Istitle) {
  EXPECT_TRUE(s3.istitle());
  EXPECT_FALSE(s1.istitle());
}

// 测试 isupper
TEST_F(StrTest, Isupper) {
  EXPECT_TRUE(s6.isupper());
  EXPECT_FALSE(s1.isupper());
}

// 测试 join
// TEST_F(StrTest, Join) {
//   ref iterable = ref("abc");
//   str joined = s1.join(iterable);
//   EXPECT_EQ(joined.value(), "ahellobchelloc");
// }

// 测试 ljust
TEST_F(StrTest, Ljust) {
  str justified = s1.ljust(10, str("-"));
  EXPECT_EQ(justified.value(), "hello-----");
}

// 测试 lower
TEST_F(StrTest, Lower) {
  str lowercased = s6.lower();
  EXPECT_EQ(lowercased.value(), "abc");
}

// 测试 lstrip
TEST_F(StrTest, Lstrip) {
  str stripped = s7.lstrip();
  EXPECT_EQ(stripped.value(), "");
}

// 测试 upper
TEST_F(StrTest, Upper) {
  str uppercased = s1.upper();
  EXPECT_EQ(uppercased.value(), "HELLO");
}

// 测试乘法运算符
TEST_F(StrTest, MultiplyOperator) {
  str multiplied = s1 * 3;
  EXPECT_EQ(multiplied.value(), "hellohellohello");
}

// 测试输出运算符
TEST_F(StrTest, StreamOperator) {
  std::ostringstream oss;
  oss << s1;
  EXPECT_EQ(oss.str(), "hello");
}
