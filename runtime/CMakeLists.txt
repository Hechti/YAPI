set(MODULE Runtime)

set(HDR_FILES
  YapiConfig.h
  Runtime.h
)

set(SRC_FILES
  YapiConfig.cpp
  Runtime.cpp
)

add_library(${MODULE} ${HDR_FILES} ${SRC_FILES})
target_link_libraries(${MODULE} PUBLIC YAPI PRIVATE json)

set_property(TARGET ${MODULE} PROPERTY FOLDER Runtime)