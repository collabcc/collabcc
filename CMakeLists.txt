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


# Third-party libraries
# Directory "3rdparty/${THIRDPARTY_XXX}" shall exist
set(THIRDPARTY_BOOST boost_1_68_0)


# Add source files and 3rd-party directory to include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/${THIRDPARTY_BOOST})


# Configure config.h and add the destination to include directories
configure_file(
    "src/config.h.cmakein"
    "cmakein/generated/config.h"
    @ONLY)
include_directories("${CMAKE_CURRENT_BINARY_DIR}/cmakein")


# Source files and executables
set(COMMON_SOURCE_FILES
    src/common/assertion.h
    src/common/basic.h
    src/common/common.h
    src/common/macros.h
    "${CMAKE_CURRENT_BINARY_DIR}/cmakein/generated/config.h")

set(MAIN_COMMON_SOURCE_FILES
    src/main.cpp
    ${COMMON_SOURCE_FILES})

# collabcc
add_executable(collabcc ${MAIN_COMMON_SOURCE_FILES})
target_compile_definitions(collabcc PRIVATE -DBUILD_COLLABCC=1)

# collabccd
add_executable(collabccd ${MAIN_COMMON_SOURCE_FILES})
target_compile_definitions(collabccd PRIVATE -DBUILD_COLLABCCD=1)

# collabccctl
add_executable(collabccctl ${MAIN_COMMON_SOURCE_FILES})
target_compile_definitions(collabccctl PRIVATE -DBUILD_COLLABCCCTL=1)


# Unit tests
set(UNITTEST_COMMON_SOURCE_FILES
    test/driver/driver.cpp
    test/driver/driver.h
    test/driver/assertion.h
    ${COMMON_SOURCE_FILES})

option(COLLABCC_ENABLE_UNITTEST "Build unit tests." ON)
if (COLLABCC_ENABLE_UNITTEST)
    enable_testing()
endif()

macro(AddTest testname)
    add_executable(${testname} ${UNITTEST_COMMON_SOURCE_FILES} "test/${testname}.cpp" ${ARGN})
    target_compile_definitions(${testname} PRIVATE -DBUILD_UNITTEST=1)
    add_test(NAME ${testname} COMMAND ${testname})
endmacro()

AddTest(test_assertions)
target_compile_definitions(test_assertions PRIVATE -DBUILD_UNITTEST_ASSERTIONS=1)
