project(advanced_opengl)

find_package(assimp REQUIRED)

set(SOURCE
    main.cpp
    Mesh.cpp
    Model.cpp
    Shader.cpp
    Camera.cpp
)

add_executable(depth_testing ${SOURCE})

add_custom_command(TARGET depth_testing POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/model_loading
    $<TARGET_FILE_DIR:depth_testing>/model_loading
)

add_custom_command(TARGET depth_testing POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:depth_testing>/resources
)

target_link_libraries(depth_testing PRIVATE imgui glfw3 GL X11 pthread dl lib_glad assimp::assimp)
