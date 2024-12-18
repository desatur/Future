cmake_minimum_required(VERSION 3.29)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
#set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(ASSIMP_BUILD_STATIC_LIB OFF)
set(SHADERS_DIR ${CMAKE_SOURCE_DIR}/Future/src/Shaders/)

project(Future)

add_subdirectory(${THIRD_PARTY_LIB_DIR}/spdlog spdlog)
add_subdirectory(${THIRD_PARTY_LIB_DIR}/SDL SDL)
add_subdirectory(${THIRD_PARTY_LIB_DIR}/glm glm)
set(BUILD_SHARED_LIBS ON)
add_subdirectory(${THIRD_PARTY_LIB_DIR}/assimp assimp)
#add_subdirectory(${THIRD_PARTY_LIB_DIR}/imgui_cmake imgui)

add_library(Future SHARED
        # GLAD
        ${THIRD_PARTY_LIB_DIR}/glad/src/glad.c

        src/Engine.cpp
        src/Engine.hpp
        src/Core.hpp
        Future.hpp
        src/EntryPoint.hpp
        src/Log.cpp
        src/Log.hpp
        src/Window/Window.cpp
        src/Window/Window.hpp
        src/Rendering/Instances.cpp
        src/Rendering/Instances.hpp
        src/Rendering/Renderer.cpp
        src/Rendering/Renderer.hpp
        src/Rendering/Shaders.cpp
        src/Rendering/Shaders.hpp
        src/Rendering/Buffers/VBO.cpp
        src/Rendering/Buffers/VBO.hpp
        src/Rendering/Buffers/VAO.cpp
        src/Rendering/Buffers/VAO.hpp
        src/Rendering/Buffers/EBO.cpp
        src/Rendering/Buffers/EBO.hpp
        src/Rendering/Buffers/FBO.cpp
        src/Rendering/Buffers/FBO.hpp
        src/Rendering/Buffers/RBO.cpp
        src/Rendering/Buffers/RBO.hpp
        src/Rendering/Buffers/Framebuffer/RectangleVAO.cpp
        src/Rendering/Buffers/Framebuffer/RectangleVAO.hpp
        src/Rendering/Buffers/Framebuffer/RectangleVBO.cpp
        src/Rendering/Buffers/Framebuffer/RectangleVBO.hpp
        src/Rendering/Textures/Texture.cpp
        src/Rendering/Textures/Texture.hpp
        src/Rendering/Camera.cpp
        src/Rendering/Camera.hpp
        src/Rendering/Mesh/Mesh.cpp
        src/Rendering/Mesh/Mesh.hpp
        src/Rendering/Mesh/Model.cpp
        src/Rendering/Mesh/Model.hpp
        src/Rendering/Vertex.hpp
)

target_include_directories(Future PUBLIC
        ${THIRD_PARTY_LIB_DIR}/spdlog/include/
        ${THIRD_PARTY_LIB_DIR}/SDL/include/
        ${THIRD_PARTY_LIB_DIR}/glad/include/
        ${THIRD_PARTY_LIB_DIR}/stb/
        ${THIRD_PARTY_LIB_DIR}/glm/glm/
        ${THIRD_PARTY_LIB_DIR}/assimp/include
        #${THIRD_PARTY_LIB_DIR}/imgui_cmake
        #${THIRD_PARTY_LIB_DIR}/imgui_cmake/backends
)

target_link_libraries(Future PUBLIC spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>)
target_link_libraries(Future PUBLIC SDL2::SDL2main)
target_link_libraries(Future PUBLIC SDL2::SDL2)
target_link_libraries(Future PUBLIC glm)
target_link_libraries(Future PUBLIC assimp)
#target_link_libraries(Future PUBLIC imgui)

add_custom_command(TARGET Future POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SHADERS_DIR} $<TARGET_FILE_DIR:Future>/Shaders
)

add_custom_command(TARGET Future POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SHADERS_DIR} $<TARGET_FILE_DIR:FutureSandbox>/Shaders
)

target_compile_definitions(Future PRIVATE FE_BUILD_LIB)
