cmake_minimum_required(VERSION 3.14)
project(TokenParserProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
    TokenParser.cpp
)

add_executable(TokenParserExe ${SOURCES})

target_include_directories(TokenParserExe PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
