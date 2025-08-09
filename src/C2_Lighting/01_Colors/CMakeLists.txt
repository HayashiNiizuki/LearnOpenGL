set(COLORS_SOURCE
    Shader.cpp
    Colors.cpp
    Camera.cpp
)

add_executable(colors ${COLORS_SOURCE})

add_custom_command(TARGET colors POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/cube_shader
    $<TARGET_FILE_DIR:colors>/cube_shader
)

add_custom_command(TARGET colors POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/lighting_shader
    $<TARGET_FILE_DIR:colors>/lighting_shader
)

target_link_libraries(colors glfw3 GL X11 pthread dl lib_glad)
