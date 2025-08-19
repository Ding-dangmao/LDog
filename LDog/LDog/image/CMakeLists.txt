set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../encapsulation)
include(config)
message(${SOURCES})

set(INFORMATION "image")

#可开关宏
#是否启用oatpp-swagger
add_compile_definitions(OATPP_SWAGGER_ENABLE)
#是否启用异步endpoints
add_compile_definitions(ASYNC_ENDPOINT)


#配置文件
#此为oatpp-swagger所需文件路径
add_compile_definitions(OATPP_SWAGGER_RES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/../encapsulation")
#此为yaml所需yaml文件宏,若注释将导致yaml工具类报错,若不开启yaml配置则无用
add_compile_definitions(YAML_CONFIG_FILE_CONNECTION="${CMAKE_CURRENT_SOURCE_DIR}/config/config.yaml")

#定义图片存储目录
add_compile_definitions(IMAGE_FILE_PATH="F:/ldog_images/images")
#定义图片临时存储目录
add_compile_definitions(IMAGE_TEMP_FILE_PATH="F:/ldog_images/temp")
#定义文件上传信息存储目录
add_compile_definitions(IMAGE_UPLOAD_INFO_PATH="F:/ldog_images/image_info")


include_directories(../encapsulation
					../encapsulation/include_all
					../encapsulation/include_all/mysql
					../encapsulation/include_all/oatpp-1.3.0
					../encapsulation/include_all/nacos
					./transmitOBJ/
)



# 将源代码添加到此项目的可执行文件。
add_executable (${INFORMATION}
			   "image_main.cpp"
			   ${SOURCES}
			   #Controller
			   "Controller/imageController.cpp"
			   #Service
			   "Service/imageService.cpp"
			   #DAO
			   "util/imageDAO.cpp"
			   "util/imageutil.cpp"
			   "util/accountDAO.cpp"

)

#平台限制
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	add_compile_definitions(Windows)
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	add_compile_definitions(Linux)
endif()


set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../encapsulation/package)

#Windows
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
#xlnt
find_package(xlnt REQUIRED HINT ${CMAKE_CURRENT_SOURCE_DIR}/package)
if(NOT xlnt_FOUND)
	message("not found xlnt")
else()
	message("found it xlnt")
endif()
target_link_libraries(${INFORMATION} PUBLIC xlnt)
endif()

#Linux
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
#配置nacos
find_package(nacos REQUIRED HINT ${CMAKE_CURRENT_SOURCE_DIR}/package)
if(NOT nacos_FOUND)
	message("not found nacos")
else()
	message("found it nacos")
endif()
target_link_libraries(${INFORMATION} PUBLIC nacos)
endif()


#配置mysql
find_package(mysql REQUIRED HINT ${CMAKE_CURRENT_SOURCE_DIR}/../encapsulation/package)
if(NOT mysql_FOUND)
	message("not found mysql")
else()
	message("found mysql ")
endif()
target_link_libraries(${INFORMATION}  PUBLIC mysql)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_link_libraries(${INFORMATION} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../encapsulation/lib/linux/debug/libmysqlcppconn8.so)
endif()


#配置oatpp
find_package(oatpp REQUIRED HINT ${CMAKE_CURRENT_SOURCE_DIR}/../encapsulation/package)
if(NOT oatpp_FOUND)
	message("not found oatpp")
else()
	message("found oatpp ")
endif()
target_link_libraries(${INFORMATION} PUBLIC oatpp)

#配置oatpp-swagger

find_package(oatpp_swagger REQUIRED HINT ${CMAKE_CURRENT_SOURCE_DIR}/../encapsulation/package)
if(NOT oatpp_swagger_FOUND)
	message("not found oatpp-swagger")
else()
	message("found it oatpp-swagger")
endif()
target_link_libraries(${INFORMATION} PUBLIC oatpp_swagger)


#配置yaml 
include(FetchContent)

FetchContent_Declare(
	yaml-cpp
	GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git  
	GIT_TAG yaml-cpp-0.7.0   
)
FetchContent_MakeAvailable(yaml-cpp)   

target_link_libraries(${INFORMATION}  PUBLIC yaml-cpp)

#配置boost
set(Boost_DIR "F:/boost_1_88_0/lib64-msvc-14.3/cmake/Boost-1.88.0")
find_package(Boost REQUIRED COMPONENTS url json)
target_link_libraries(${INFORMATION} PUBLIC Boost::url)
target_link_libraries(${INFORMATION} PUBLIC Boost::json)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${INFORMATION} PROPERTY CXX_STANDARD 20)
endif()
