#include <gtest/gtest.h>
#include "allocator.hpp"

#include <gtest/gtest.h>

TEST(AllocatorTest, SimpleAlloc) {
    Allocator allocator(100);
    char* ptr = allocator.alloc(10);
    EXPECT_NE(ptr, nullptr);
}

TEST(DeallocatorTest, SimpleAlloc) {
    Allocator allocator(100);
    char* ptr = allocator.alloc(10);
    allocator.~Allocator();
    EXPECT_EQ(ptr, nullptr);
}