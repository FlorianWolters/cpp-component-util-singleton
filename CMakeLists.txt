# CMakeLists.txt
#
# The top-level configuration file for the build system "CMake".
#
# Copyright Florian Wolters 2014 (http://blog.florianwolters.de).
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

set(PROJECT_NAME "cpp-component-util-singleton")

project(${PROJECT_NAME})
cmake_minimum_required(VERSION 2.8.11)

set(GTEST_MINIMUM_VERSION 1.7)

if(WIN32)
    set(GTEST_ROOT "C:/usr/lib")
    set(GTEST_INCLUDE_DIR "C:/usr/include")
endif()

set(PROJECT_FILE_EXTENSION_DECLARATION_FILE "h")
set(PROJECT_FILE_EXTENSION_DEFINITION_FILE "cc")
set(PROJECT_SOURCE_DIR_DECLARATION "include")
set(PROJECT_SOURCE_DIR_TEST "test")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${PROJECT_SOURCE_DIR_DECLARATION})

file(GLOB_RECURSE
     PROJECT_SOURCE_DECLARATION_FILES
     "${PROJECT_SOURCE_DIR_DECLARATION}/*.${PROJECT_FILE_EXTENSION_DECLARATION_FILE}")

option(BUILD_TESTS "Build the automated tests of the project (requires Boost.Test)." ON)
if(BUILD_TESTS)
    enable_testing()

    # Find "Threading" package.
    find_package(Threads REQUIRED)
    set(PROJECT_USED_TESTING_LIBRARIES ${PROJECT_USED_TESTING_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

    # Find "Google Test (GTest)".
    find_package(GTest ${GTEST_MINIMUM_VERSION} REQUIRED)

    include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})
    set(PROJECT_USED_TESTING_LIBRARIES ${PROJECT_USED_TESTING_LIBRARIES} ${GTEST_BOTH_LIBRARIES})
    file(GLOB_RECURSE
         PROJECT_SOURCE_DEFINITION_TEST_FILES
         "${PROJECT_SOURCE_DIR_TEST}/*.${PROJECT_FILE_EXTENSION_DEFINITION_FILE}")

    foreach(TEST_FILE ${PROJECT_SOURCE_DEFINITION_TEST_FILES})
        get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
        add_executable(${TEST_NAME} ${TEST_FILE})
        target_link_libraries(${TEST_NAME} ${PROJECT_USED_TESTING_LIBRARIES})
        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    endforeach()
endif()
