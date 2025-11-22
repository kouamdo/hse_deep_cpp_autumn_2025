#include <gtest/gtest.h>
#include "../include/BigInt.hpp"

TEST(BigIntTest, Addition) {
    BigInt a("123");
    BigInt b("456");
    BigInt c = a + b;
    EXPECT_EQ(c.toString(), "579");
}

TEST(BigIntTest, Subtraction) {
    BigInt a("1000");
    BigInt b("1");
    BigInt c = a - b;
    EXPECT_EQ(c.toString(), "999");
}