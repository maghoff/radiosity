cmake_minimum_required(VERSION 2.6)
project(SIMPLEMODEL)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")
find_package(Ymse REQUIRED)
find_package(SDL REQUIRED)
find_package(CWiiD REQUIRED)

include_directories(${YMSE_PATH} ${SDL_INCLUDE_DIR} ${CWIID_INCLUDE_DIR})
add_subdirectory(src)
