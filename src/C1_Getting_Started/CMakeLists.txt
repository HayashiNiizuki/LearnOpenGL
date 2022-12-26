project(getting_start)

cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 11)

set(HELLO_WINDOW_SOURCE hello_window.cpp glad.c)
add_executable(hello_window ${HELLO_WINDOW_SOURCE})

set(HELLO_TRIANGLE_SOURCE hello_triangle.cpp glad.c)
add_executable(hello_triangle ${HELLO_TRIANGLE_SOURCE})

set(HELLO_TRIANGLE_ASSIGNMENT_SOURCE hello_triangle_assignment.cpp glad.c)
add_executable(hello_triangle_assignment ${HELLO_TRIANGLE_ASSIGNMENT_SOURCE})

target_link_libraries(hello_window glfw3 GL X11 pthread dl)
target_link_libraries(hello_triangle glfw3 GL X11 pthread dl)
target_link_libraries(hello_triangle_assignment glfw3 GL X11 pthread dl)
