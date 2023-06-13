set(HELLO_TRIANGLE_SOURCE Hello_Triangle.cpp)
add_executable(triangle ${HELLO_TRIANGLE_SOURCE})

target_link_libraries(triangle glfw3 GL X11 pthread dl lib_glad)
