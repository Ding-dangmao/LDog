#include<iostream>



//#include"config/util_include.h"
#include"Controller/imageController.h"


using namespace oatpp::network;
using namespace oatpp::web;
using namespace oatpp::parser;

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
	OATPP_INIT_P(run)
		return 0;
}