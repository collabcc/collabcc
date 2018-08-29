# target_compile_definitions requires CMake 2.8.11
cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)


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


# Enable C11, C++11
# Enable C/C++ 11
if (CMAKE_VERSION VERSION_LESS 3.1)
    # Add the C++11 flag, whatever it is
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG(-std=c++11 COMPILER_SUPPORTS_CXX11)
    if (COMPILER_SUPPORTS_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    else()
        # TODO: Maybe other flags?
        message(FATAL_ERROR "The C++ compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Consider using a different C++ compiler.")
    endif()

    # Add the C11 flag, whatever it is
    include(CheckCCompilerFlag)
    CHECK_C_COMPILER_FLAG(-std=c11 COMPILER_SUPPORTS_C11)
    if (COMPILER_SUPPORTS_C11)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
    else()
        # TODO: Maybe other flags?
        message(FATAL_ERROR "The C compiler ${CMAKE_C_COMPILER} has no C11 support. Consider using a different C compiler.")
    endif()
else()
    # Require C++11 support, prefer ISO C++ over GNU variants,
    # as relying solely on ISO C++ is more portable.
    SET(CMAKE_CXX_STANDARD 11)
    SET(CMAKE_CXX_STANDARD_REQUIRED ON)
    #SET(CMAKE_CXX_EXTENSIONS OFF)

    SET(CMAKE_C_STANDARD 11)
    SET(CMAKE_C_STANDARD_REQUIRED ON)
    #SET(CMAKE_C_EXTENSIONS OFF)
endif()


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
    if (COLLABCC_ENABLE_UNITTEST)
        add_executable(${testname} ${UNITTEST_COMMON_SOURCE_FILES} "test/${testname}.cpp" ${ARGN})
    else()
        add_executable(${testname} EXCLUDE_FROM_ALL ${UNITTEST_COMMON_SOURCE_FILES} "test/${testname}.cpp" ${ARGN})
    endif()
    target_compile_definitions(${testname} PRIVATE -DBUILD_UNITTEST=1)
    add_dependencies(${testname} collabcc collabccd collabccctl)
    add_test(NAME ${testname} COMMAND ${testname})
endmacro()

AddTest(test_assertions)
target_compile_definitions(test_assertions PRIVATE -DBUILD_UNITTEST_ASSERTIONS=1)
