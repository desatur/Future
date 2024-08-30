cmake_minimum_required(VERSION 3.29)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")

project(Future)


add_library(Future SHARED
        src/Engine.cpp
        src/Engine.hpp
        include/Core.hpp
        include/Future.hpp
)

target_compile_definitions(Future PRIVATE FE_BUILD_LIB)
target_include_directories(Future PUBLIC ./${CMAKE_CURRENT_SOURCE_DIR}/include/)
