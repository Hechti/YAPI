cmake_minimum_required(VERSION 3.10)
project(YAPI)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install CACHE INTERNAL "" FORCE)

add_subdirectory(api)
add_subdirectory(cmakes)
add_subdirectory(examples)  