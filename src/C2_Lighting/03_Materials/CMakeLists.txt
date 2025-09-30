set(MATERIALS_SOURCE
    Shader.cpp
    main.cpp
    Camera.cpp
)

add_executable(materials ${MATERIALS_SOURCE})

add_custom_command(TARGET materials POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/cube_shader
    $<TARGET_FILE_DIR:materials>/cube_shader
)

add_custom_command(TARGET materials POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/lighting_shader
    $<TARGET_FILE_DIR:materials>/lighting_shader
)

target_link_libraries(materials glfw3 GL X11 pthread dl lib_glad)
