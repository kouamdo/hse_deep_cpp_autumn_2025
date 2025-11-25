cmake_minimum_required(VERSION 3.14)
project(FormatTestProject)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(FormatTests ../tests/format_test.cpp ../src/Format.cpp) 

target_link_libraries(FormatTests gtest_main)

include(GoogleTest)
gtest_discover_tests(FormatTests)