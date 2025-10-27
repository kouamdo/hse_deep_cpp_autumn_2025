cmake_minimum_required(VERSION 3.14)
project(ParserProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

add_library(parser_lib TokenParser.cpp TokenParser.hpp)

add_executable(ParserProject main.cpp TokenParser.cpp)
target_link_libraries(ParserProject PRIVATE parser_lib)

add_executable(ParserTests tests/test_Parser.cpp)
target_link_libraries(ParserTests PRIVATE parser_lib GTest::gtest GTest::gtest_main)
gtest_discover_tests(ParserTests)