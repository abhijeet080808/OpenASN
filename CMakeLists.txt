cmake_minimum_required(VERSION 3.11)

project(OpenASN VERSION 0.1
                DESCRIPTION "C++ ASN.1 Compiler"
                HOMEPAGE_URL "https://github.com/abhijeet080808/OpenASN"
                LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
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

FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG        v1.5.0
)

FetchContent_GetProperties(spdlog)
if(NOT spdlog_POPULATED)
  FetchContent_Populate(spdlog)
  add_subdirectory(${spdlog_SOURCE_DIR} ${spdlog_BINARY_DIR})
  message(STATUS "GIT library spdlog downloaded to: ${spdlog_SOURCE_DIR}")
endif()

message(STATUS "Building OpenASN version: ${CMAKE_PROJECT_VERSION}")

configure_file(version_config.hh.in ${CMAKE_BINARY_DIR}/gen/version_config.hh )
include_directories(${CMAKE_BINARY_DIR}/gen)

add_subdirectory(src/app)
add_subdirectory(src/parser)
