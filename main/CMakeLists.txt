set(MODULE YapiMain)

add_executable(${MODULE} main.cpp)
install(TARGETS ${MODULE} DESTINATION ${CMAKE_INSTALL_PREFIX})