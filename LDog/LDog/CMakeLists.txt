# CMakeList.txt: LDog 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#

#set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/encapsulation)
#include(config)

include_directories(./encapsulation
					./encapsulation/include_all
					./encapsulation/include_all/mysql
					./encapsulation/include_all/oatpp-1.3.0
)

# 将源代码添加到此项目的可执行文件。
add_executable (LDog "LDog.cpp" "image/image_main.cpp" "image/config/util_include.h" "image/controller/imageController.h"  "encapsulation/tool/tool.cpp" "encapsulation/tool/tool.h")
add_subdirectory(encapsulation)
add_subdirectory(image)



if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET LDog PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
