// main_test.cpp
#include <gtest/gtest.h>
#include "../include/Serializer.hpp"
#include "../include/Deserializer.hpp"
#include <sstream>

TEST(SerializationTest, BasicSerialization) {
    Data x = {1, true, 2};

    std::stringstream stream;

    Serializer serializer(stream);
    ASSERT_EQ(serializer.save(x), Error::NoError);

    Data y = {0, false, 0};

    Deserializer deserializer(stream);
    ASSERT_EQ(deserializer.load(y), Error::NoError);

    ASSERT_EQ(x.a, y.a);
    ASSERT_EQ(x.b, y.b);
    ASSERT_EQ(x.c, y.c);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
