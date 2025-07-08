set(
    TRANSFORMATIONS_SOURCE 
    Transformations.cpp  
    Shader.cpp  
    preprocessor.h
    stb_image.h
)
add_executable(transformations ${TRANSFORMATIONS_SOURCE})

target_link_libraries(transformations glfw3 GL X11 pthread dl lib_glad)
