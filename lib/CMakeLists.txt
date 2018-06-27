set(MODULE1 DataSenderPlugin)
add_library(${MODULE1} SHARED DataSenderPlugin.h DataSenderPlugin.cpp)
install(TARGETS ${MODULE1} DESTINATION ${CMAKE_INSTALL_PREFIX})

set(MODULE2 DataReceiverPlugin)
add_library(${MODULE2} SHARED DataReceiverPlugin.h DataReceiverPlugin.cpp)
install(TARGETS ${MODULE2} DESTINATION ${CMAKE_INSTALL_PREFIX})