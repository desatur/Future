cmake_minimum_required(VERSION 3.29)
project(imgui)

add_library(imgui)

target_sources(imgui PRIVATE 
    ${THIRD_PARTY_LIB_DIR}/imgui/imgui.cpp
    ${THIRD_PARTY_LIB_DIR}/imgui/imgui_demo.cpp
    ${THIRD_PARTY_LIB_DIR}/imgui/imgui_draw.cpp
    ${THIRD_PARTY_LIB_DIR}/imgui/imgui_tables.cpp
    ${THIRD_PARTY_LIB_DIR}/imgui/imgui_widgets.cpp
    ${THIRD_PARTY_LIB_DIR}/imgui/backends/imgui_impl_sdl2.cpp
    ${THIRD_PARTY_LIB_DIR}/imgui/backends/imgui_impl_opengl3.cpp
)

