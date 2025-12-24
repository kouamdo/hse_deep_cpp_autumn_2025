cmake_minimum_required(VERSION 3.14)
project(MatrixProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ajouter le dossier include
include_directories(include)

# Ajouter la bibliothèque statique de votre code
add_library(matrix_lib STATIC src/Matrix.cpp)


# Ajouter GoogleTest via FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Ajouter l'exécutable de test
add_executable(test_matrix tests/test_matrix.cpp tests/test_matrix_extra.cpp)

# Lier l'exécutable test à la bibliothèque et à GoogleTest
target_link_libraries(test_matrix matrix_lib gtest_main)

# Ajouter la cible de test
include(GoogleTest)
gtest_discover_tests(test_matrix)
