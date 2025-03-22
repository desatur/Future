cmake_minimum_required(VERSION 3.29)

project(FutureSandbox)
#add_compile_definitions(FUTURE_EXPORT)

add_executable(FutureSandbox
        src/Sandbox.cpp
)

target_link_libraries(FutureSandbox PRIVATE FutureCore)