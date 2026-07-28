#include "unit_test.h"
#include "string_manip.h"
#include <string>
#include <vector>

TEST(string_trim) {
    ASSERT_EQ(strutil::trim("  hello  "), "hello");
    ASSERT_EQ(strutil::trim("\t\n\r"), "");
    ASSERT_EQ(strutil::trim("world"), "world");
    return true;
}

TEST(string_split) {
    auto parts = strutil::split("a,b,c", ',');
    ASSERT_EQ(parts.size(), 3u);
    ASSERT_EQ(parts[0], "a");
    ASSERT_EQ(parts[1], "b");
    ASSERT_EQ(parts[2], "c");

    auto empty = strutil::split("", ',');
    ASSERT_EQ(empty.size(), 0u);
    return true;
}

TEST(string_join) {
    std::vector<std::string> parts = {"x", "y", "z"};
    ASSERT_EQ(strutil::join(parts, "-"), "x-y-z");
    ASSERT_EQ(strutil::join({}, ","), "");
    return true;
}

TEST(string_starts_ends) {
    ASSERT_TRUE(strutil::starts_with("hello world", "hello"));
    ASSERT_FALSE(strutil::starts_with("hello", "world"));
    ASSERT_TRUE(strutil::ends_with("hello.cpp", ".cpp"));
    ASSERT_FALSE(strutil::ends_with("hello.cpp", ".h"));
    return true;
}

TEST(string_replace) {
    ASSERT_EQ(strutil::replace("aaa", "a", "b"), "bbb");
    ASSERT_EQ(strutil::replace("abcabc", "ab", ""), "cc");
    return true;
}

TEST(arithmetic) {
    ASSERT_EQ(1 + 1, 2);
    ASSERT_GT(10, 5);
    ASSERT_LT(-1, 0);
    ASSERT_GE(5, 5);
    return true;
}

int main() {
    return RUN_TESTS();
}
