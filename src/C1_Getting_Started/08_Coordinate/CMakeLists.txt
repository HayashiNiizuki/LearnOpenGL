set(
    COORDINATE_SOURCE 
    Coordinate.cpp  
    Shader.cpp
    preprocessor.h
    stb_image.h
)
add_executable(coordinate ${COORDINATE_SOURCE})

target_link_libraries(coordinate glfw3 GL X11 pthread dl lib_glad)
