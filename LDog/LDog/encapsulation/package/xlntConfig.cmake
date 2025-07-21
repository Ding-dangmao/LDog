set(XLNT_NAME xlnt)
#set(XLNT_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include_all)

add_library(${XLNT_NAME} STATIC IMPORTED)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
set_target_properties(${XLNT_NAME} PROPERTIES
					 IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../encapsulation/lib/windows/debug/xlntd.lib)
else()
set_target_properties(${XLNT_NAME} PROPERTIES
					 IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../encapsulation/lib/windows/release/xlnt.lib)
endif()