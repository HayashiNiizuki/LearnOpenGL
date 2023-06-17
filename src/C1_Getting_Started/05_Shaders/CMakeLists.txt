set(
    SHADERS_SOURCE 
    Hello_Shader.cpp
    Shader.h
)
add_executable(shaders ${SHADERS_SOURCE})

target_link_libraries(shaders glfw3 GL X11 pthread dl lib_glad)
