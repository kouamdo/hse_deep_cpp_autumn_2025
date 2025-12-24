#include <gtest/gtest.h>
#include "../include/BigInt.hpp"

TEST(BigIntExtra, Multiplication) {
    BigInt a("123");
    BigInt b("456");
    BigInt c = a * b;
    EXPECT_EQ(c.toString(), "56088");
}

TEST(BigIntExtra, NegativeNumbers) {
    BigInt a("100");
    BigInt b("-50");
    EXPECT_EQ((a + b).toString(), "50");
    EXPECT_EQ((a - b).toString(), "150");
}

TEST(BigIntExtra, IntRhs) {
    BigInt a("100");
    EXPECT_EQ((a + 23).toString(), "123");
    EXPECT_EQ((a - 23).toString(), "77");
    EXPECT_EQ((a * 3).toString(), "300");
}
