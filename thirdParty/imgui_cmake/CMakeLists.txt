set(_target "imgui")

add_library(${_target}
    imconfig.h
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui.cpp
    misc/cpp/imgui_stdlib.cpp
    misc/cpp/imgui_stdlib.h
    backends/imgui_impl_opengl3.cpp
    backends/imgui_impl_opengl3.h
    backends/imgui_impl_sdl2.cpp
    backends/imgui_impl_sdl2.h
)

target_include_directories(${_target}
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/imgui"
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(${_target} PUBLIC SDL2::SDL2main)
target_link_libraries(${_target} PUBLIC SDL2::SDL2)