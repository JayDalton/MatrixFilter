cmake_minimum_required(VERSION 3.20)

message(STATUS "Using CMake ${CMAKE_VERSION}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set up project
project(MatrixFilter)
message(STATUS ${PROJECT_NAME})

enable_testing()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/Release)

set(ROOT_DIR ${CMAKE_SOURCE_DIR})
set(SRC_DIR ${CMAKE_SOURCE_DIR}/source)

# Prepare the build
add_subdirectory(source/common)
#add_subdirectory(source/console)
#add_subdirectory(source/cuteapp)
