cmake_minimum_required(VERSION 3.10)
project(YAPI)

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install CACHE INTERNAL "" FORCE)

include_directories(api)
add_subdirectory(lib)
add_subdirectory(main)