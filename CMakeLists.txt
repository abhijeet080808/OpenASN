cmake_minimum_required(VERSION 3.10)

project(OpenASN VERSION 0.1
				        DESCRIPTION "C++ ASN.1 Library"
								LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

message(STATUS "Building OpenASN version: ${VERSION}")

add_subdirectory(src/parser)
