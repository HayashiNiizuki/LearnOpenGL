set(
    TEXTURES_SOURCE 
    Hello_Textures.cpp  
    Shader.h  
    preprocessor.h
    stb_image.h
)
add_executable(textures ${TEXTURES_SOURCE})

target_link_libraries(textures glfw3 GL X11 pthread dl lib_glad)
