set(MODULE YapiMain)

add_executable(${MODULE} main.cpp)
target_link_libraries(${MODULE} YAPI)
install(TARGETS ${MODULE} DESTINATION ${CMAKE_INSTALL_PREFIX}/examples)
set_property(TARGET ${MODULE} PROPERTY FOLDER ${FOLDER_NAME})