cmake_minimum_required(VERSION 3.29)

project(FutureMain)

set(THIRD_PARTY_LIB_DIR "${CMAKE_SOURCE_DIR}/thirdParty")
message(STATUS "Third Party library Directory: ${THIRD_PARTY_LIB_DIR}")

add_subdirectory(Future)
add_subdirectory(FutureSandbox)