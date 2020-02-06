cmake_minimum_required(VERSION 3.11)

project(OpenASN VERSION 0.1
                DESCRIPTION "C++ ASN.1 Compiler"
                LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_VERBOSE_MAKEFILE ON)

include(FetchContent)

FetchContent_Declare(
  cxxopts
  GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
  GIT_TAG        v2.2.0
)

FetchContent_GetProperties(cxxopts)
if(NOT cxxopts_POPULATED)
  FetchContent_Populate(cxxopts)
  add_subdirectory(${cxxopts_SOURCE_DIR} ${cxxopts_BINARY_DIR})
  message(STATUS "GIT library cxxopts downloaded to: ${cxxopts_SOURCE_DIR}")
endif()

message(STATUS "Building OpenASN version: ${CMAKE_PROJECT_VERSION}")

add_subdirectory(src/app)
add_subdirectory(src/parser)
