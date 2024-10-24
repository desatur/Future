cmake_minimum_required(VERSION 3.29)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
#set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")

project(FutureSandbox)

add_executable(FutureSandbox
        src/FutureSandbox.cpp
)

target_link_libraries(FutureSandbox PRIVATE Future)

add_custom_command(TARGET FutureSandbox POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Future>
        $<TARGET_FILE_DIR:FutureSandbox>
)