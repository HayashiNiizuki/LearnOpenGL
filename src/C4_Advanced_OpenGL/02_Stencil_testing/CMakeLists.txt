project(advanced_opengl)

find_package(assimp REQUIRED)

set(SOURCE
    main.cpp
    Mesh.cpp
    Model.cpp
    Shader.cpp
    Camera.cpp
)

add_executable(stencil_testing ${SOURCE})

add_custom_command(TARGET stencil_testing POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders
    $<TARGET_FILE_DIR:stencil_testing>/shaders
)

add_custom_command(TARGET stencil_testing POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:stencil_testing>/resources
)

target_link_libraries(stencil_testing PRIVATE imgui glfw3 GL X11 pthread dl lib_glad assimp::assimp)
