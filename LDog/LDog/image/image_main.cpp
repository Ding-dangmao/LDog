#include<iostream>



//#include"config/util_include.h"
#include"Controller/imageController.h"


#define LDOG_VERSION "1.0v"
#define COUNT_ENDL(str,message) std::cout<<str<<": "<<message<<std::endl;

using namespace oatpp::network;
using namespace oatpp::web;
using namespace oatpp::parser;

namespace __class {
	const oatpp::ClassId ImageGroupInfoClass::CLASS_ID("custom-types::image_group_info");
	const oatpp::ClassId ImageInfoClass::CLASS_ID("custom-types::image_upload_info");
}

void run() {
	for (int i = 8000; i <= 8100; i++) {
		try {
			RegisteredComponent component("localhost", i);
			auto controller = std::make_shared<ImageController>();
			OatppRun run_exe;
			run_exe(controller);
			break;
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}
	return;
}


int main() {
	std::cout << "==========================================================" << std::endl;
	std::cout << "欢迎使用LDOG图床" << std::endl;
	std::cout << "当前版本为: " << LDOG_VERSION << std::endl;
	COUNT_ENDL("制作者","ddcat")
	std::cout << "==========================================================" << std::endl;
	OATPP_INIT_P(run)
	return 0;
}