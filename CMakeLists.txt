cmake_minimum_required(VERSION 3.16.0)
project(primer VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    message(TODO)
else()
    add_compile_options(-Wall -Wextra -pedantic -Wconversion -Werror)
endif()

include(cmake/CPM.cmake)
CPMAddPackage("gh:onqtam/doctest@2.4.9")

add_executable(vector_swap vector_swap.cpp)

add_executable(iterators iterators.cpp)

add_executable(minmax minmax.cpp)
target_link_libraries(minmax PRIVATE doctest::doctest_with_main)

add_executable(input input.cpp)
target_precompile_headers(input PRIVATE
    util.h
)

add_executable(adjacent_ints adjacent_ints.cpp)

add_executable(binary_search binary_search.cpp)

add_subdirectory(bookstore)