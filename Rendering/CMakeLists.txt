cmake_minimum_required(VERSION 3.29)
project(FutureRendering VERSION 0.0.0 LANGUAGES C CXX)

add_compile_definitions(FUTURE_EXPORT)

find_package(Vulkan REQUIRED)
set(GLFW_VERSION 3.4)
include(FetchContent)

FetchContent_Declare(
    glfw
    URL https://github.com/glfw/glfw/archive/refs/tags/${GLFW_VERSION}.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP true
)
#add_definitions(-DGLFW_INCLUDE_VULKAN)
FetchContent_MakeAvailable(glfw)

file(GLOB_RECURSE FutureRendering_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE FutureRendering_HEADERS CONFIGURE_DEPENDS "src/*.hpp")

set(FutureRendering_INCLUDE_DIRS "")
foreach (_headerFile ${FutureRendering_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list(APPEND FutureRendering_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES FutureRendering_INCLUDE_DIRS)

add_library(${PROJECT_NAME} SHARED ${FutureRendering_SOURCES})
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES} Vulkan::Vulkan)
target_include_directories(${PROJECT_NAME} PRIVATE ${FutureRendering_INCLUDE_DIRS})

