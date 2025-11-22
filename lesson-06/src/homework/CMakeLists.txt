cmake_minimum_required(VERSION 3.14)
project(BigIntProject)

set(CMAKE_CXX_STANDARD 17)

# Ajout de Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Bibliothèque BigInt
add_library(BigInt src/BigInt.cpp src/BigInt.h)

# Exécutable de test
add_executable(BigIntTests tests/test_bigint.cpp)

target_link_libraries(BigIntTests BigInt gtest_main)

include(GoogleTest)
gtest_discover_tests(BigIntTests)
