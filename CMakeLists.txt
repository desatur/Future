cmake_minimum_required(VERSION 3.29)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")

# -----------------------------------------------
project(FutureEngine)

add_library(FutureEngine SHARED
        FutureEngine/src/Dummy.cpp
        FutureEngine/src/Dummy.hpp
)

# -----------------------------------------------
project(FutureSandbox)

add_executable(FutureSandbox
        FutureSandbox/src/FutureSandbox.cpp
)

target_link_libraries(FutureSandbox PRIVATE FutureEngine)