set(OATPP_SWAGGER_NAME oatpp_swagger)

add_library(${OATPP_SWAGGER_NAME} STATIC IMPORTED)


if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	
	if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	set_target_properties(${OATPP_SWAGGER_NAME} PROPERTIES
						 IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../encapsulation/lib/windows/debug/oatpp-swagger.lib)
	else()
	set_target_properties(${OATPP_SWAGGER_NAME} PROPERTIES
						 IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../encapsulation/lib/windows/release/oatpp-swagger.lib)
	endif()

else()
	if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	set_target_properties(${OATPP_SWAGGER_NAME} PROPERTIES
						 IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../encapsulation/lib/linux/debug/liboatpp-swagger.a)
	else()
	#set_target_properties(${OATPP_SWAGGER_NAME} PROPERTIES
	#					 IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../encapsulation/lib/windows/release/liboatpp-swagger.a)
	endif()

endif()