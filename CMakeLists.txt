cmake_minimum_required(VERSION 3.20)
project(polprodukty)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors -Wconversion)

include_directories(
        include
        )

set(SOURCE_FILES
        src/package.cpp
        src/storage_types.cpp
        )

add_executable(polprodukty ${SOURCE_FILES} main.cpp)
