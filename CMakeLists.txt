cmake_minimum_required(VERSION 2.6)
project(SIMPLEMODEL)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")
find_package(Ymse REQUIRED)

include_directories(${YMSE_PATH})
add_subdirectory(src)

