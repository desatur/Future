cmake_minimum_required(VERSION 3.29)
project(Future)

set(CMAKE_CXX_STANDARD 20)
set(BENCHMARK_ENABLE_TESTING OFF)

# Add the source files for your library
add_library(Future STATIC
        FutureEngine/src/FutureEngine.cpp
        FutureEngine/Structs/Vector2.cpp
        FutureEngine/Structs/Vector3.cpp
        FutureEngine/Structs/Vector2.h
        FutureEngine/Structs/Vector3.h
)
