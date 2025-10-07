set(MULTIPLE_LIGHTS_SOURCE
    Shader.cpp
    main.cpp
    Camera.cpp
)

add_executable(multiple_lights ${MULTIPLE_LIGHTS_SOURCE})

add_custom_command(TARGET multiple_lights POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/cube_shader
    $<TARGET_FILE_DIR:multiple_lights>/cube_shader
)

add_custom_command(TARGET multiple_lights POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/lighting_shader
    $<TARGET_FILE_DIR:multiple_lights>/lighting_shader
)

add_custom_command(TARGET multiple_lights POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/container2.png
    $<TARGET_FILE_DIR:multiple_lights>/container2.png
)

add_custom_command(TARGET multiple_lights POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/container2_specular.png
    $<TARGET_FILE_DIR:multiple_lights>/container2_specular.png
)

target_link_libraries(multiple_lights glfw3 GL X11 pthread dl lib_glad)
