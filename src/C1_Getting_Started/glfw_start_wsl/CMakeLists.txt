project(glfw_start) # glfw_start是你的项目名
cmake_minimum_required(VERSION 3.14) # 3.14是你的cmake版本，自动生成的
set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp glad.c) # 这里的部分自动添加的
add_executable(glfw_start ${SOURCE_FILES}) # glfw_start是项目名
target_link_libraries(glfw_start glfw3 GL m Xrandr Xi X11 pthread dl Xinerama Xcursor) # 这里可以直接复制，项目名称要更改