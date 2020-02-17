cmake_minimum_required(VERSION 3.11)

project(OpenASN VERSION 0.1
                DESCRIPTION "C++ ASN.1 Compiler"
                HOMEPAGE_URL "https://github.com/abhijeet080808/OpenASN"
                LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_VERBOSE_MAKEFILE ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Build type is Debug (default)")
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)
else()
  message(STATUS "Build type is ${CMAKE_BUILD_TYPE}")
endif()

add_compile_options(-Wall -Wextra -pedantic -Werror)

message(STATUS "Building OpenASN version: ${CMAKE_PROJECT_VERSION}")

find_package(Threads REQUIRED)
include(ExternalProject)

## --------------------------------------------------------------------------- #
## CXXOPTS ------------------------------------------------------------------- #
## --------------------------------------------------------------------------- #

ExternalProject_Add(
  project_cxxopts
  GIT_REPOSITORY    https://github.com/jarro2783/cxxopts.git
  GIT_TAG           v2.2.0
  PREFIX            ${CMAKE_BINARY_DIR}/external
  CMAKE_ARGS        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_BINARY_DIR}/external/
)

## --------------------------------------------------------------------------- #
## SPDLog -------------------------------------------------------------------- #
## --------------------------------------------------------------------------- #

ExternalProject_Add(
  project_spdlog
  GIT_REPOSITORY    https://github.com/gabime/spdlog.git
  GIT_TAG           v1.5.0
  PREFIX            ${CMAKE_BINARY_DIR}/external
  CMAKE_ARGS        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_BINARY_DIR}/external/
)

add_library(spdlog STATIC IMPORTED)
add_dependencies(spdlog project_spdlog)
set_target_properties(spdlog
  PROPERTIES
  IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/external/lib/libspdlog.a
)

## --------------------------------------------------------------------------- #
## Google Test --------------------------------------------------------------- #
## --------------------------------------------------------------------------- #

ExternalProject_Add(
  project_googletest
  GIT_REPOSITORY    https://github.com/google/googletest.git
  GIT_TAG           release-1.10.0
  PREFIX            ${CMAKE_BINARY_DIR}/external
  CMAKE_ARGS        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_BINARY_DIR}/external/
)

add_library(gtest STATIC IMPORTED)
add_dependencies(gtest project_googletest)
set_target_properties(gtest
  PROPERTIES
  IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/external/lib/libgtest.a
  INTERFACE_LINK_LIBRARIES Threads::Threads
)

add_library(gmock STATIC IMPORTED)
add_dependencies(gmock project_googletest)
set_target_properties(gmock
  PROPERTIES
  IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/external/lib/libgmock.a
  INTERFACE_LINK_LIBRARIES Threads::Threads
)

## --------------------------------------------------------------------------- #

# SPDLOG_* macros on this log level or higher will be processed during
# compile time
#
# From spdlog/common.h -
#
# define SPDLOG_LEVEL_TRACE 0
# define SPDLOG_LEVEL_DEBUG 1
# define SPDLOG_LEVEL_INFO 2
# define SPDLOG_LEVEL_WARN 3
# define SPDLOG_LEVEL_ERROR 4
# define SPDLOG_LEVEL_CRITICAL 5
# define SPDLOG_LEVEL_OFF 6
add_compile_definitions(SPDLOG_ACTIVE_LEVEL=1)

configure_file(version_config.hh.in ${CMAKE_BINARY_DIR}/gen/version_config.hh )

include_directories(${CMAKE_BINARY_DIR}/gen)
include_directories(${CMAKE_BINARY_DIR}/external/include)

add_subdirectory(src/app)
add_subdirectory(src/common)
add_subdirectory(src/generator)
add_subdirectory(src/parser)

enable_testing()
add_subdirectory(tests)
