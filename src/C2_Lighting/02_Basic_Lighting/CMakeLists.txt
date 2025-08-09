set(BASIC_LIGHTING_SOURCE
    Shader.cpp
    main.cpp
    Camera.cpp
)

add_executable(basic_lighting ${BASIC_LIGHTING_SOURCE})

add_custom_command(TARGET basic_lighting POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/cube_shader
    $<TARGET_FILE_DIR:basic_lighting>/cube_shader
)

add_custom_command(TARGET basic_lighting POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/lighting_shader
    $<TARGET_FILE_DIR:basic_lighting>/lighting_shader
)

target_link_libraries(basic_lighting glfw3 GL X11 pthread dl lib_glad)
