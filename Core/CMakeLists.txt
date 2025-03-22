cmake_minimum_required(VERSION 3.29)
project(FutureCore VERSION 0.0.0 LANGUAGES C CXX)
string(TIMESTAMP CURRENT_DATETIME "%Y%m%d_%H%M%S" UTC)

# --- Props ---
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(Future_VERSION "${CURRENT_DATETIME}")
else()
    set(Future_VERSION "0.0.0_0001")
endif()

add_compile_definitions(Future_VERSION="${Future_VERSION}")
message(STATUS "Future Version: ${Future_VERSION}")
# -------------
add_compile_definitions(FUTURE_EXPORT)

include(FetchContent)

set(SPDLOG_VERSION 1.15.1)

FetchContent_Declare(
	spdlog
	URL https://github.com/gabime/spdlog/archive/refs/tags/v${SPDLOG_VERSION}.tar.gz
	FIND_PACKAGE_ARGS ${SPDLOG_VERSION}
    DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_MakeAvailable(spdlog)

file (GLOB_RECURSE FutureCore_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file (GLOB_RECURSE FutureCore_HEADERS CONFIGURE_DEPENDS "src/*.hpp")

set (FutureCore_INCLUDE_DIRS "")

foreach (_headerFile ${FutureCore_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND FutureCore_INCLUDE_DIRS ${_dir})
endforeach()

list (REMOVE_DUPLICATES FutureCore_INCLUDE_DIRS)

add_library(${PROJECT_NAME} SHARED ${FutureCore_SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)