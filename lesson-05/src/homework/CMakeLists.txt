cmake_minimum_required(VERSION 3.14)
project(MatrixProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ajouter le dossier include
include_directories(include)

# Ajouter la bibliothèque statique de votre code
add_library(matrix_lib STATIC src/Matrix.cpp)

# Ajouter GoogleTest
add_subdirectory(googletest)
enable_testing()

# Ajouter l'exécutable de test
add_executable(test_matrix tests/test_matrix.cpp)

# Lier l'exécutable test à la bibliothèque et à GoogleTest
target_link_libraries(test_matrix matrix_lib gtest_main)

# Ajouter la cible de test
add_test(NAME MatrixTests COMMAND test_matrix)
