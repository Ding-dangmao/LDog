set(OATPP_NAME oatpp)

add_library(${OATPP_NAME} STATIC IMPORTED)


if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	
	if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	set_target_properties(${OATPP_NAME} PROPERTIES
						 IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../encapsulation/lib/windows/debug/oatpp.lib)
	else()
	set_target_properties(${OATPP_NAME} PROPERTIES
						 IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../encapsulation/lib/windows/release/oatpp.lib)
	endif()

else()
	if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	set_target_properties(${OATPP_NAME} PROPERTIES
						 IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../encapsulation/lib/linux/debug/liboatpp.a)
	else()
	#set_target_properties(${OATPP_NAME} PROPERTIES
	#					 IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../encapsulation/lib/windows/release/oatpp.lib)
	endif()

endif()