set(LIGHTING_MAPS_SOURCE
    Shader.cpp
    main.cpp
    Camera.cpp
)

add_executable(lighting_maps ${LIGHTING_MAPS_SOURCE})

add_custom_command(TARGET lighting_maps POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/cube_shader
    $<TARGET_FILE_DIR:lighting_maps>/cube_shader
)

add_custom_command(TARGET lighting_maps POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/lighting_shader
    $<TARGET_FILE_DIR:lighting_maps>/lighting_shader
)

add_custom_command(TARGET lighting_maps POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/container2.png
    $<TARGET_FILE_DIR:lighting_maps>/container2.png
)

add_custom_command(TARGET lighting_maps POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/container2_specular.png
    $<TARGET_FILE_DIR:lighting_maps>/container2_specular.png
)

target_link_libraries(lighting_maps glfw3 GL X11 pthread dl lib_glad)
