set(NACOS_NAME nacos)


add_library(${NACOS_NAME} STATIC IMPORTED)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
set_target_properties(${NACOS_NAME} PROPERTIES
					 IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../encapsulation/lib/linux/debug/libnacos-cli.so)
else()
set_target_properties(${NACOS_NAME} PROPERTIES
					 IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../encapsulation/lib/linux/release/libnacos-cli.so)
endif()