project(advanced_opengl)

find_package(assimp REQUIRED)

set(SOURCE
    main.cpp
    Mesh.cpp
    Model.cpp
    Shader.cpp
    Camera.cpp
)

add_executable(face_culling ${SOURCE})

add_custom_command(TARGET face_culling POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders
    $<TARGET_FILE_DIR:face_culling>/shaders
)

add_custom_command(TARGET face_culling POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:face_culling>/resources
)

target_link_libraries(face_culling PRIVATE imgui glfw3 GL X11 pthread dl lib_glad assimp::assimp)
