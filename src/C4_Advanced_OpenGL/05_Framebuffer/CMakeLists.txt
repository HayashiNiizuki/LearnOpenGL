project(advanced_opengl)

find_package(assimp REQUIRED)

set(SOURCE
    main.cpp
    Shader.cpp
    Camera.cpp
)

add_executable(framebuffer ${SOURCE})

add_custom_command(TARGET framebuffer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders
    $<TARGET_FILE_DIR:framebuffer>/shaders
)

add_custom_command(TARGET framebuffer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:framebuffer>/resources
)

target_link_libraries(framebuffer PRIVATE imgui glfw3 GL X11 pthread dl lib_glad assimp::assimp)
