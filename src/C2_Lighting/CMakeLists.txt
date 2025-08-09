cmake_minimum_required(VERSION 3.14)

project(lighting)

set(CMAKE_CXX_STANDARD 17)

# Default is debug build
if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE Debug)
endif ()

add_library(lib_glad STATIC glad.c)

add_subdirectory(01_Colors)
add_subdirectory(02_Basic_Lighting)