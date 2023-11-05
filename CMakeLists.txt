cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(ptk LANGUAGES CXX)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(include/ast)
include_directories(include/codegen/)

add_subdirectory(lib/ast)
add_subdirectory(lib/codegen/c++)
add_subdirectory(test)
