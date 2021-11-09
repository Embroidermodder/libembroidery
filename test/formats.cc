#include "gtest/gtest.h"

extern "C" {
#include "tests.h"
}

class formats : public ::testing::Test {
 public:
};

TEST(formats, testEmbCircle) {
  ASSERT_EQ(testEmbCircle(), 0);
}

TEST(formats, testThreadColor) {
  ASSERT_EQ(testThreadColor(), 0);
}

TEST(formats, testEmbFormat) {
  ASSERT_EQ(testEmbFormat(), 0);
}

TEST(formats, testGeomArc) {
  ASSERT_EQ(testGeomArc(), 0);
}

TEST(formats, create_test_file_1) {
  ASSERT_EQ(create_test_file_1("test01.csv", EMB_FORMAT_CSV), 0);
}

TEST(formats, create_test_file_2) {
  ASSERT_EQ(create_test_file_2("test02.csv", EMB_FORMAT_CSV), 0);
}

TEST(formats, convert1) {
  ASSERT_EQ(convert("test02.csv", "test02.svg"), 0);
}

/* TEST(formats, convert2) {
  ASSERT_EQ(convert("test01.csv", "test01.dst"), 0);
}

TEST(formats, convert3) {
  ASSERT_EQ(convert("test02.csv", "test02.dst"), 0);
} */
