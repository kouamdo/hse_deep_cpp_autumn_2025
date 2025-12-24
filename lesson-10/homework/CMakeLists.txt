cmake_minimum_required(VERSION 3.14)
project(AVLTree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Main library
add_library(avl_tree
    src/avl_tree.cpp
    include/avl_tree.hpp
    include/avl_node.hpp
    include/avl_iterator.hpp
)

target_include_directories(avl_tree PUBLIC include)

# Test executable
add_executable(avl_test
    src/main.cpp
)

target_link_libraries(avl_test avl_tree)

# Demo program
add_executable(avl_demo
    src/demo.cpp
)

target_link_libraries(avl_demo avl_tree)

# Install targets
install(TARGETS avl_tree DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)