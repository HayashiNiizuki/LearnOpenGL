project(getting_start)

cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 11)

# Default is debug build
if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE Debug)
endif ()

add_library(lib_glad STATIC glad.c)

add_subdirectory(03_Hello_Window)
add_subdirectory(04_Hello_Triangle)
add_subdirectory(05_Shaders)
add_subdirectory(06_Textures)
add_subdirectory(07_Transformations)