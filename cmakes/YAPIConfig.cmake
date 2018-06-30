if (YAPI_FOUND)
    return()
endif(YAPI_FOUND)

add_library(YAPI STATIC IMPORTED)
set_target_properties(YAPI PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/lib/YAPI.${CMAKE_STATIC_LIBRARY_SUFFIX})
target_include_directories(YAPI PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)