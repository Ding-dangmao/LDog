set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../encapsulation)
include(config)
message(${SOURCES})

set(INFORMATION "image")

#�ɿ��غ�
#�Ƿ�����oatpp-swagger
add_compile_definitions(OATPP_SWAGGER_ENABLE)
#�Ƿ������첽endpoints
add_compile_definitions(ASYNC_ENDPOINT)
#�Ƿ����ò��Թ���
#add_compile_definitions(TEST_ON)

#�����ļ�
#��Ϊoatpp-swagger�����ļ�·��
add_compile_definitions(OATPP_SWAGGER_RES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/../encapsulation")
#��Ϊyaml����yaml�ļ���,��ע�ͽ�����yaml�����౨��,��������yaml����������
add_compile_definitions(YAML_CONFIG_FILE_CONNECTION="${CMAKE_CURRENT_SOURCE_DIR}/config/config.yaml")



#����ͼƬ�洢Ŀ¼
add_compile_definitions(IMAGE_FILE_PATH="/home/ddcat_service/service_data/ldog_images/images")
#����ͼƬ��ʱ�洢Ŀ¼
add_compile_definitions(IMAGE_TEMP_FILE_PATH="/home/ddcat_service/service_data/ldog_images/temp")
#�����ļ��ϴ���Ϣ�洢Ŀ¼
add_compile_definitions(IMAGE_UPLOAD_INFO_PATH="/home/ddcat_service/service_data/ldog_images/image_info")


include_directories(../encapsulation
					../encapsulation/include_all
					../encapsulation/include_all/mysql
					../encapsulation/include_all/oatpp-1.3.0
					../encapsulation/include_all/nacos
					./transmitOBJ/
)



# ��Դ�������ӵ�����Ŀ�Ŀ�ִ���ļ���
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

#ƽ̨����
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
#����nacos
find_package(nacos REQUIRED HINT ${CMAKE_CURRENT_SOURCE_DIR}/package)
if(NOT nacos_FOUND)
	message("not found nacos")
else()
	message("found it nacos")
endif()
target_link_libraries(${INFORMATION} PUBLIC nacos)
endif()


#����mysql
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


#����oatpp
find_package(oatpp REQUIRED HINT ${CMAKE_CURRENT_SOURCE_DIR}/../encapsulation/package)
if(NOT oatpp_FOUND)
	message("not found oatpp")
else()
	message("found oatpp ")
endif()
target_link_libraries(${INFORMATION} PUBLIC oatpp)

#����oatpp-swagger

find_package(oatpp_swagger REQUIRED HINT ${CMAKE_CURRENT_SOURCE_DIR}/../encapsulation/package)
if(NOT oatpp_swagger_FOUND)
	message("not found oatpp-swagger")
else()
	message("found it oatpp-swagger")
endif()
target_link_libraries(${INFORMATION} PUBLIC oatpp_swagger)


#����yaml 
include(FetchContent)

FetchContent_Declare(
	yaml-cpp
	GIT_REPOSITORY https://bgithub.xyz/jbeder/yaml-cpp.git  
	GIT_TAG yaml-cpp-0.7.0   
)
FetchContent_MakeAvailable(yaml-cpp)   

target_link_libraries(${INFORMATION}  PUBLIC yaml-cpp)

#����boost
set(Boost_DIR "/home/tool/boost_1_89_0/stage/lib/cmake/Boost-1.89.0")
find_package(Boost REQUIRED COMPONENTS url json)
message("found it boost")
target_link_libraries(${INFORMATION} PUBLIC Boost::url)
target_link_libraries(${INFORMATION} PUBLIC Boost::json)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${INFORMATION} PROPERTY CXX_STANDARD 20)
endif()
