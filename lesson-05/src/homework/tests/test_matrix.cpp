#include <gtest/gtest.h>
#include "../include/Matrix.hpp"

TEST(MatrixTest, DefaultConstructor) {
    Matrix m(3, 3);
    EXPECT_EQ(m.getRows(), 3);
    EXPECT_EQ(m.getColumns(), 3);
}
