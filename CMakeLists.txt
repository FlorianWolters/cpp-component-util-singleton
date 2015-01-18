# CMakeLists.txt
#
# The top-level configuration file for the build system "CMake" of the project
# "florianwolters/singleton".
#
# -DCMAKE_BUILD_TYPE=Debug
# -DBUILD_TESTS=BOOL:ON
#
# Author: Florian Wolters <wolters.fl@gmail.com>
#
# Copyright Florian Wolters (http://blog.florianwolters.de) 2014 - 2015.
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

if(BIICODE)
  # "biicode" build.

  init_biicode_block()

  include("biicode/cmake/tools")
  activate_cpp11(${BII_BLOCK_TARGET})

  add_biicode_targets()
else()
  # Independent build.

  # --------------------------------------------------------------------------
  # Set variables related to the project.
  # --------------------------------------------------------------------------

  set(PROJECT_VERSION_MAJOR 1)
  set(PROJECT_VERSION_MINOR 0)
  set(PROJECT_VERSION_PATCH 0)

  set(PROJECT_NAME "florianwolters-singleton")
  set(PROJECT_DETAIL_NAME "Singleton")
  set(PROJECT_BRIEF_DESCRIPTION "The Singleton creational design pattern as a reusable C++11 component.")
  set(PROJECT_AUTHOR_NAME "Florian Wolters")
  set(PROJECT_AUTHOR_EMAIL "wolters.fl@gmail.com")
  set(PROJECT_AUTHOR_WEBSITE "http://blog.florianwolters.de")
  set(PROJECT_VENDOR_NAME ${PROJECT_AUTHOR_NAME})
  set(PROJECT_VENDOR_WEBSITE ${PROJECT_AUTHOR_WEBSITE})
  set(PROJECT_VENDOR_EMAIL ${PROJECT_AUTHOR_WEBSITE})

  set(PROJECT_PACKAGE_NAME_PREFIX "FlorianWolters-")
  set(PROJECT_PACKAGE_INSTALL_BASE_DIR "opt/florianwolters")

  # TODO(wolters): Find a way to determine the architecture of the build
  # automatically.
  set(PROJECT_ARCHITECTURE "x86_64")

  # --------------------------------------------------------------------------
  # Set variables related to dependencies of the project.
  # --------------------------------------------------------------------------

  set(PROJECT_DEPENDENCY_CMAKE_VERSION "3.1")
  set(PROJECT_DEPENDENCY_CPPCHECK_VERSION "1.6")
  set(PROJECT_DEPENDENCY_DOXYGEN_VERSION "1.8")

  # This has to be the exact version string (e. g. 1.2.0 instead of 1.2).
  set(PROJECT_DEPENDENCY_FLAWFINDER_VERSION "1.31")
  set(PROJECT_DEPENDENCY_GTEST_VERSION "1.7.0")

  # --------------------------------------------------------------------------
  # Custom actions specific to this project.
  # --------------------------------------------------------------------------

  if(WIN32)
    set(CPPCHECK_ROOT_DIR "C:/Program Files (x86)/Cppcheck")

    set(GTEST_ROOT "C:/usr/lib")
    set(GTEST_INCLUDE_DIR "C:/usr/include")

    set(PYTHON_EXECUTABLE "C:/Program Files/Python 2.7/python.exe")
    set(PYTHON_INCLUDE_DIR "${PYTHON_EXECUTABLE}/include")
    set(PYTHON_LIBRARY "${PYTHON_EXECUTABLE}/Lib")
  endif()

  # ----------------------------------------------------------------------------
  # Set the minimum required version of "CMake for the project.
  # ----------------------------------------------------------------------------

  cmake_minimum_required(VERSION ${PROJECT_DEPENDENCY_CMAKE_VERSION} FATAL_ERROR)

  # ----------------------------------------------------------------------------
  # Set the minimum required version of "CMake for the project.
  # Load and run "CMake" code from "florianwolters/cmake-utils".
  #
  # This must be done AFTER declaring variables, since the custom "CMake"
  # modules depend on some variables.
  # ----------------------------------------------------------------------------

  include("${PROJECT_SOURCE_DIR}/cmake/Bootstrap.cmake")
endif()
