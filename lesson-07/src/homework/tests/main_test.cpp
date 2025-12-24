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

TEST(DeserializerTest, BoolCorrupted) {
    std::stringstream stream("not_bool ");
    Deserializer d(stream);
    bool b;
    EXPECT_EQ(d.load(b), Error::CorruptedArchive);
}

TEST(DeserializerTest, UintCorrupted) {
    std::stringstream stream("12x ");
    Deserializer d(stream);
    uint64_t v;
    EXPECT_EQ(d.load(v), Error::CorruptedArchive);
}

TEST(DeserializerTest, MissingTokens) {
    std::stringstream stream("1 true"); // manque le 3ᵉ champ
    Data y{0,false,0};
    Deserializer d(stream);
    EXPECT_EQ(d.load(y), Error::CorruptedArchive);
}

TEST(SerializationTest, Uint64Limits) {
    Data x{0, false, std::numeric_limits<uint64_t>::max()};
    std::stringstream s;
    Serializer ser(s);
    ASSERT_EQ(ser.save(x), Error::NoError);
    Data y{0,false,0};
    Deserializer d(s);
    ASSERT_EQ(d.load(y), Error::NoError);
    EXPECT_EQ(x.c, y.c);
}

TEST(SerializationTest, MultipleObjects) {
    Data x1{1,true,2}, x2{3,false,4};
    std::stringstream s;
    Serializer ser(s);
    ASSERT_EQ(ser.save(x1), Error::NoError);
    ASSERT_EQ(ser.save(x2), Error::NoError);
    Data y1{}, y2{};
    Deserializer d(s);
    ASSERT_EQ(d.load(y1), Error::NoError);
    ASSERT_EQ(d.load(y2), Error::NoError);
    EXPECT_EQ(x1.a, y1.a);
    EXPECT_EQ(x2.a, y2.a);
}

TEST(SerializerVarargs, Basic) {
    std::stringstream s;
    Serializer ser(s);
    ASSERT_EQ(ser(10, true, 20), Error::NoError);
    EXPECT_EQ(s.str(), "10 true 20 ");
    uint64_t a; bool b; uint64_t c;
    Deserializer d(s);
    ASSERT_EQ(d(a, b, c), Error::NoError);
    EXPECT_EQ(a, 10); EXPECT_EQ(b, true); EXPECT_EQ(c, 20);
}

TEST(DeserializerTest, MultipleSpaces) {
    std::stringstream s("1   true\t 2");
    Deserializer d(s);
    Data y;
    ASSERT_EQ(d.load(y), Error::NoError);
    EXPECT_EQ(y.a,1); EXPECT_EQ(y.b,true); EXPECT_EQ(y.c,2);
}

TEST(DeserializerTest, OrderMismatch) {
    std::stringstream s("true 1 2 ");
    Deserializer d(s);
    uint64_t a; bool b; uint64_t c;
    EXPECT_EQ(d(a, b, c), Error::CorruptedArchive);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
