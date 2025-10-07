set(LIGHT_CASTERS_SOURCE
    Shader.cpp
    main.cpp
    Camera.cpp
)

add_executable(light_casters ${LIGHT_CASTERS_SOURCE})

add_custom_command(TARGET light_casters POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/cube_shader
    $<TARGET_FILE_DIR:light_casters>/cube_shader
)

add_custom_command(TARGET light_casters POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/lighting_shader
    $<TARGET_FILE_DIR:light_casters>/lighting_shader
)

add_custom_command(TARGET light_casters POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/container2.png
    $<TARGET_FILE_DIR:light_casters>/container2.png
)

add_custom_command(TARGET light_casters POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/container2_specular.png
    $<TARGET_FILE_DIR:light_casters>/container2_specular.png
)

target_link_libraries(light_casters glfw3 GL X11 pthread dl lib_glad)
