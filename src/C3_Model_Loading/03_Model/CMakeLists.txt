find_package(assimp REQUIRED)

set(SOURCE
    main.cpp
    Mesh.cpp
    Model.cpp
    Shader.cpp
    Camera.cpp
)

add_executable(main ${SOURCE})

add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/model_loading
    $<TARGET_FILE_DIR:main>/model_loading
)

add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:main>/resources
)

target_link_libraries(main glfw3 GL X11 pthread dl lib_glad assimp::assimp)
