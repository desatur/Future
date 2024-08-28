cmake_minimum_required(VERSION 3.29)
project(Future)

set(CMAKE_CXX_STANDARD 20)

add_library(Future STATIC FutureEngine.cpp
        Structs/Vector2.cpp
        Structs/Vector3.cpp
)
