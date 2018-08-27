cmake_minimum_required(VERSION 2.8.4 FATAL_ERROR)

project(collabcc C CXX)


# collabcc version number format:
#   <major>.<minor>.<patch> <suffix>
# <suffix> could be:
#   "stable" "rc" "beta" "alpha" "unstable"
set(COLLABCC_VERSION_MAJOR 0)
set(COLLABCC_VERSION_MINOR 0)
set(COLLABCC_VERSION_PATCH 1)
set(COLLABCC_VERSION_SUFFIX "unstable")


# Add source files directory to include directories
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")


# Configure config.h and add the destination to include directories
configure_file(
    "src/config.h.cmakein"
    "cmakein/generated/config.h"
    @ONLY)
include_directories("${CMAKE_CURRENT_BINARY_DIR}/cmakein")


# Source files and executables
set(COMMON_SOURCE_FILES
    src/common/basic.h
    src/common/common.h
    src/main.cpp
    "${CMAKE_CURRENT_BINARY_DIR}/cmakein/generated/config.h")

# collabcc
add_executable(collabcc ${COMMON_SOURCE_FILES})
target_compile_definitions(collabcc PRIVATE -DBUILD_COLLABCC=1)

# collabccd
add_executable(collabccd ${COMMON_SOURCE_FILES})
target_compile_definitions(collabccd PRIVATE -DBUILD_COLLABCCD=1)

# collabccctl
add_executable(collabccctl ${COMMON_SOURCE_FILES})
target_compile_definitions(collabccctl PRIVATE -DBUILD_COLLABCCCTL=1)
