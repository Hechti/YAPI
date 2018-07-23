set(MODULE YAPI)

set(HDR_FILES
  SampleEventHandler.h
  InputPin.h
  OutputPin.h
  Yapi.h
  CyclicPlugin.h
)

set(SRC_FILES
  InputPin.cpp
  OutputPin.cpp
  Yapi.cpp
  CyclicPlugin.cpp
)

add_library(${MODULE} ${HDR_FILES} ${SRC_FILES})
target_include_directories(${MODULE} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${MODULE} PUBLIC )

install(TARGETS ${MODULE} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(FILES ${HDR_FILES} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)

set_property(TARGET ${MODULE} PROPERTY FOLDER API)