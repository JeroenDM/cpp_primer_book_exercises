cmake_minimum_required(VERSION 3.16.0)
project(primer VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    message(TODO)
else()
    add_compile_options(-Wall -Wextra -pedantic -Wconversion -Werror)
endif()

add_executable(vector_swap vector_swap.cpp)

add_executable(iterators iterators.cpp)

add_executable(input input.cpp)
target_precompile_headers(input PRIVATE
    util.h
)

add_executable(adjacent_ints adjacent_ints.cpp)

add_executable(binary_search binary_search.cpp)