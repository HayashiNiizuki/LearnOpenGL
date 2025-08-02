set(COLORS_SOURCE
    Shader.cpp
    Colors.cpp
    Camera.cpp
)

add_executable(colors ${COLORS_SOURCE})

target_link_libraries(colors glfw3 GL X11 pthread dl lib_glad)
