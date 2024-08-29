cmake_minimum_required(VERSION 3.29)
project(Future)

set(CMAKE_CXX_STANDARD 20)
set(BENCHMARK_ENABLE_TESTING OFF)

# Add the source files for your library
add_library(Future STATIC
        src/FutureEngine.cpp
        src/Structs/Vector2.cpp
        src/Structs/Vector3.cpp
        src/Structs/Vector2.h
        src/Structs/Vector3.h
)

# Benchmarks
add_subdirectory(lib/benchmark)
target_link_libraries(Future PUBLIC benchmark::benchmark benchmark::benchmark_main)
add_executable(vector_benchmark benchmarks/vector_benchmark.cpp)
target_link_libraries(vector_benchmark Future benchmark::benchmark benchmark::benchmark_main)
