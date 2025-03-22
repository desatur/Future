cmake_minimum_required(VERSION 3.29)

project(FutureSandbox)
add_executable(FutureSandbox src/Sandbox.cpp)
target_link_libraries(FutureSandbox PUBLIC FutureCore)
#target_link_libraries(FutureSandbox PUBLIC FutureRendering)