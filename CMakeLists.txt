cmake_minimum_required(VERSION 3.16)
project(long_number_project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib/googletest)

add_library(long_number_lib
    long_number/long_number.cpp
    long_number/long_number.hpp
)

target_include_directories(long_number_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/long_number
)

add_executable(long_number_tests
    tests/long_number_tests.cpp
)

target_link_libraries(long_number_tests
    PRIVATE
        long_number_lib
        gtest_main
)

enable_testing()
add_test(NAME long_number_tests COMMAND long_number_tests)
