cmake_minimum_required(VERSION 3.29)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(SHADERS_DIR ${CMAKE_SOURCE_DIR}/Future/src/Shaders/)

project(Future)

add_subdirectory(${THIRD_PARTY_LIB_DIR}/spdlog spdlog)
add_subdirectory(${THIRD_PARTY_LIB_DIR}/SDL SDL)
add_subdirectory(${THIRD_PARTY_LIB_DIR}/glfw glfw)
add_subdirectory(${THIRD_PARTY_LIB_DIR}/glm glm)

add_library(Future SHARED
        src/Engine.cpp
        src/Engine.hpp
        src/Core.hpp
        Future.hpp
        src/EntryPoint.hpp
        src/Log.cpp
        src/Log.hpp
        src/Window/Window.cpp
        src/Window/Window.hpp
        src/Rendering/OpenGL/OpenGL.cpp
        src/Rendering/OpenGL/OpenGL.hpp
        src/Rendering/OpenGL/Shaders.cpp
        src/Rendering/OpenGL/Shaders.hpp
        src/Rendering/OpenGL/Buffers/VBO.cpp
        src/Rendering/OpenGL/Buffers/VBO.hpp
        src/Rendering/OpenGL/Buffers/VAO.cpp
        src/Rendering/OpenGL/Buffers/VAO.hpp
        src/Rendering/OpenGL/Buffers/EBO.cpp
        src/Rendering/OpenGL/Buffers/EBO.hpp

        # GLAD
        ${THIRD_PARTY_LIB_DIR}/glad/src/glad.c
        src/Rendering/OpenGL/Textures/Texture.cpp
        src/Rendering/OpenGL/Textures/Texture.hpp
        src/Rendering/OpenGL/Camera.cpp
        src/Rendering/OpenGL/Camera.hpp
        src/Rendering/OpenGL/Mesh.cpp
        src/Rendering/OpenGL/Mesh.hpp
)

target_include_directories(Future PUBLIC
        ${THIRD_PARTY_LIB_DIR}/spdlog/include/
        ${THIRD_PARTY_LIB_DIR}/SDL/include/
        ${THIRD_PARTY_LIB_DIR}/glad/include/
        ${THIRD_PARTY_LIB_DIR}/stb/
        ${THIRD_PARTY_LIB_DIR}/glm/glm/
)

target_link_libraries(Future PUBLIC spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>)
target_link_libraries(Future PUBLIC SDL2::SDL2main)
target_link_libraries(Future PUBLIC SDL2::SDL2)
target_link_libraries(Future PUBLIC glfw)
target_link_libraries(Future PUBLIC glm)

add_custom_command(TARGET Future POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SHADERS_DIR} $<TARGET_FILE_DIR:Future>/Shaders
)

add_custom_command(TARGET Future POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SHADERS_DIR} $<TARGET_FILE_DIR:FutureSandbox>/Shaders
)

target_compile_definitions(Future PRIVATE FE_BUILD_LIB)
