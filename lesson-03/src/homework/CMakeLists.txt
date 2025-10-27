# CMakeList.txt: проект CMake для CMake_Parser; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required(VERSION 3.20)
project(ParserProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Подключение GoogleTest
include(GoogleTest)
enable_testing()
add_library(parser_lib src/homework/TokenParser.cpp src/homework/include/TokenParser.hpp)
add_executable(ParserProject tests/test_Parser.cpp)
target_link_libraries(ParserProject PUBLIC parser_lib GTest::gtest GTest::gtest_main)
gtest_discover_tests(ParserProject)


