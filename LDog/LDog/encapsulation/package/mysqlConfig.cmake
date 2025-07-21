set(MYSQLC_NAME mysql)

add_library(${MYSQLC_NAME} STATIC IMPORTED)

add_compile_definitions(CPPCONN_PUBLIC_FUNC=)


if(CMAKE_SYSTEM_NAME STREQUAL "Windows")

	if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	set_target_properties(${MYSQLC_NAME} PROPERTIES
						 IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../encapsulation/lib/windows/debug/mysqlcppconn-static.lib)
	else()
	set_target_properties(${MYSQLC_NAME} PROPERTIES
						 IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../encapsulation/lib/windows/release/mysqlcppconn-static.lib)
	endif()
else()
	if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	set_target_properties(${MYSQLC_NAME} PROPERTIES
						 IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../encapsulation/lib/linux/debug/libmysqlcppconn.so)
	else()
	#set_target_properties(${MYSQLC_NAME} PROPERTIES
	#					 IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../encapsulation/lib/windows/release/mysqlcppconn-static.lib)
	endif()
endif()