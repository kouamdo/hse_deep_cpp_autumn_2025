#include <cstdint>
#include <iostream>
#include "allocator.hpp"

#include <gtest/gtest.h>

int main(int argc, char **argv)
{
    Allocator allocator(1024); // 1 KB

    // Allocate 256 bytes
    char* ptr1 = allocator.alloc(2024);
    if (ptr1) {
        std::cout << "Allocated 256 bytes at " << static_cast<void*>(ptr1) << std::endl;
    } else {
        std::cout << "Allocation failed for 256 bytes" << std::endl;
    }

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
