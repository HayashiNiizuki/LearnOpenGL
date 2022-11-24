project(glfw_start)

cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp glad.c)

add_executable(glfw_start ${SOURCE_FILES})

target_link_libraries(glfw_start glfw3 GL m Xrandr Xi X11 pthread dl Xinerama Xcursor)