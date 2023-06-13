
set(HELLO_WINDOW_SOURCE Hello_Window.cpp)
add_executable(window ${HELLO_WINDOW_SOURCE})

target_link_libraries(window glfw3 GL X11 pthread dl lib_glad)
