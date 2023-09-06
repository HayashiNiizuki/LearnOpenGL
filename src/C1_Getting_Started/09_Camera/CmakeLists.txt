set(
    CAMERA_SOURCE 
    ChapterCamera.cpp  
    Camera.h
    Shader.h  
    preprocessor.h
    stb_image.h
)
add_executable(camera ${CAMERA_SOURCE})

target_link_libraries(camera glfw3 GL X11 pthread dl lib_glad)
