set(MODULE1 DataSenderPlugin)
add_library(${MODULE1} SHARED DataSenderPlugin.h DataSenderPlugin.cpp)
install(TARGETS ${MODULE1} DESTINATION ${CMAKE_INSTALL_PREFIX})

set(MODULE2 DataReceiverPlugin)
add_library(${MODULE2} SHARED DataReceiverPlugin.h DataReceiverPlugin.cpp)
install(TARGETS ${MODULE2} DESTINATION ${CMAKE_INSTALL_PREFIX})

set(MODULE3 CyclicSenderPlugin)
add_library(${MODULE3} SHARED CyclicSenderPlugin.h CyclicSenderPlugin.cpp)
install(TARGETS ${MODULE3} DESTINATION ${CMAKE_INSTALL_PREFIX})