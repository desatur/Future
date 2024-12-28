cmake_minimum_required(VERSION 3.29)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
#set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(ASSIMP_BUILD_STATIC_LIB OFF)
set(SHADERS_DIR ${CMAKE_SOURCE_DIR}/Future/src/Rendering/Shaders/GLSL)

if(MSVC) 
add_compile_options(/arch:AVX2) #make sure SIMD optimizations take place
endif()

project(Future)

add_subdirectory(${THIRD_PARTY_LIB_DIR}/spdlog spdlog)
add_subdirectory(${THIRD_PARTY_LIB_DIR}/SDL SDL)
add_subdirectory(${THIRD_PARTY_LIB_DIR}/glm glm)
set(BUILD_SHARED_LIBS ON)
add_subdirectory(${THIRD_PARTY_LIB_DIR}/assimp assimp)

add_library(Future SHARED
        # GLAD
        ${THIRD_PARTY_LIB_DIR}/glad/src/glad.c

        # Imgui
        ${THIRD_PARTY_LIB_DIR}/imgui/imgui.cpp
        ${THIRD_PARTY_LIB_DIR}/imgui/imgui_demo.cpp
        ${THIRD_PARTY_LIB_DIR}/imgui/imgui_draw.cpp
        ${THIRD_PARTY_LIB_DIR}/imgui/imgui_tables.cpp
        ${THIRD_PARTY_LIB_DIR}/imgui/imgui_widgets.cpp
        ${THIRD_PARTY_LIB_DIR}/imgui/backends/imgui_impl_sdl2.cpp
        ${THIRD_PARTY_LIB_DIR}/imgui/backends/imgui_impl_opengl3.cpp

        src/Engine.cpp
        src/Engine.hpp
        src/Core.hpp
        Future.hpp
        src/EntryPoint.hpp
        src/Log.cpp
        src/Log.hpp
        src/Window/Window.cpp
        src/Window/Window.hpp
        src/Window/ImGUIHandler.cpp
        src/Window/ImGUIHandler.hpp
        #src/.cpp
        #src/.hpp
        src/Rendering/Renderer.cpp
        src/Rendering/Renderer.hpp
        src/Rendering/Shaders/Shaders.cpp
        src/Rendering/Shaders/Shaders.hpp
        src/Rendering/Buffers/VBO.cpp
        src/Rendering/Buffers/VBO.hpp
        src/Rendering/Buffers/VAO.cpp
        src/Rendering/Buffers/VAO.hpp
        src/Rendering/Buffers/EBO.cpp
        src/Rendering/Buffers/EBO.hpp
        src/Rendering/DrawLayers/Buffers/FBO.cpp
        src/Rendering/DrawLayers/Buffers/FBO.hpp
        src/Rendering/DrawLayers/Buffers/RBO.cpp
        src/Rendering/DrawLayers/Buffers/RBO.hpp
        src/Rendering/DrawLayers/Buffers/RectangleVAO.cpp
        src/Rendering/DrawLayers/Buffers/RectangleVAO.hpp
        src/Rendering/DrawLayers/Buffers/RectangleVBO.cpp
        src/Rendering/DrawLayers/Buffers/RectangleVBO.hpp
        src/Rendering/Textures/Texture.cpp
        src/Rendering/Textures/Texture.hpp
        src/Rendering/Textures/TexTypeHelpers.cpp
        src/Rendering/Textures/TexTypeHelpers.hpp
        src/Rendering/Textures/TexType.hpp
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
        ${THIRD_PARTY_LIB_DIR}/imgui_cmake
        ${THIRD_PARTY_LIB_DIR}/imgui_cmake/backends
        ${THIRD_PARTY_LIB_DIR}/imgui/
        ${THIRD_PARTY_LIB_DIR}/imgui/backends
)

target_link_libraries(Future PUBLIC spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>)
target_link_libraries(Future PUBLIC SDL2::SDL2main)
target_link_libraries(Future PUBLIC SDL2::SDL2)
target_link_libraries(Future PUBLIC glm)
target_link_libraries(Future PUBLIC assimp)

add_custom_command(TARGET Future POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SHADERS_DIR} $<TARGET_FILE_DIR:Future>/Shaders
)

add_custom_command(TARGET Future POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SHADERS_DIR} $<TARGET_FILE_DIR:FutureSandbox>/Shaders
)

target_compile_definitions(Future PRIVATE FE_BUILD_LIB)
