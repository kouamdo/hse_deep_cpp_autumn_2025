cmake_minimum_required(VERSION 3.14)
project(AVLTree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Main library
add_library(avl_tree
    class/avl_tree.cpp
    include/avl_tree.hpp
    include/avl_node.hpp
    include/avl_iterator.hpp
)

target_include_directories(avl_tree PUBLIC include)

# Enable CTest so that add_test registers tests
enable_testing()

# Test executable
add_executable(avl_test
    class/main.cpp
)

target_link_libraries(avl_test avl_tree)

# Register avl_test with CTest so it is discoverable by `ctest`
add_test(NAME avl_test COMMAND avl_test)

# Demo program (add only if demo.cpp exists)
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/class/demo.cpp)
    add_executable(avl_demo
        class/demo.cpp
    )
    target_link_libraries(avl_demo avl_tree)
endif()

# Catch2-based unit tests removed — use the `avl_test` executable (class/main.cpp) which performs assertions.
# If you prefer to re-enable Catch2 tests, add them back and reintroduce FetchContent for Catch2.

# Install targets
install(TARGETS avl_tree DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)