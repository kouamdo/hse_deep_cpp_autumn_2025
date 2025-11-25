cmake_minimum_required(VERSION 3.14)
project(SerializerTest)

set(CMAKE_CXX_STANDARD 17)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(SerializerLib
    src/Serializer.cpp
    src/Deserializer.cpp
)

add_executable(SerializerTest tests/main_test.cpp)

target_link_libraries(SerializerTest
    SerializerLib
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(SerializerTest)
