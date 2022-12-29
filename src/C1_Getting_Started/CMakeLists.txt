project(getting_start)

cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 11)

set(HELLO_WINDOW_SOURCE 03_Hello_Window.cpp glad.c)
add_executable(window ${HELLO_WINDOW_SOURCE})

set(HELLO_TRIANGLE_SOURCE 04_Hello_Triangle.cpp glad.c)
add_executable(triangle ${HELLO_TRIANGLE_SOURCE})

set(HELLO_TRIANGLE_ASSIGNMENT_SOURCE 04A1_Hello_Triangle.cpp glad.c)
add_executable(triangle_a1 ${HELLO_TRIANGLE_ASSIGNMENT_SOURCE})

target_link_libraries(window glfw3 GL X11 pthread dl)
target_link_libraries(triangle glfw3 GL X11 pthread dl)
target_link_libraries(triangle_a1 glfw3 GL X11 pthread dl)
