#include <gtest/gtest.h>
#include "../include/Matrix.hpp"

TEST(MatrixExtra, OutOfRange) {
    Matrix m(2,2);
    EXPECT_THROW(m[0][2] = 1, std::out_of_range);
    EXPECT_THROW(m[2][0] = 1, std::out_of_range);
}

TEST(MatrixExtra, CopyMove) {
    Matrix a(2,2);
    a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
    Matrix b = a; // copy
    EXPECT_TRUE(b == a);

    Matrix c = std::move(a);
    EXPECT_EQ(c[0][0], 1);
}

TEST(MatrixExtra, EqualitySizesMismatch) {
    Matrix a(2,2);
    Matrix b(3,2);
    EXPECT_FALSE(a == b);
}

TEST(MatrixExtra, MultiplyAndAdd) {
    Matrix a(2,2);
    a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
    a *= 3;
    EXPECT_EQ(a[0][0], 3);
    Matrix d = a + a;
    EXPECT_EQ(d[1][1], 24);
}


