set(
    SHADERS_SOURCE 
    Hello_Shader.cpp
    Shader.cpp
)
add_executable(shaders ${SHADERS_SOURCE})

target_link_libraries(shaders glfw3 GL X11 pthread dl lib_glad)
