#ifndef OATPP_SWAGGER_COMPONENT_H
#define OATPP_SWAGGER_COMPONENT_H

#include"../oatpp_include.h"

#ifdef OATPP_SWAGGER_ENABLE
#include"oatpp-swagger/Model.hpp"
#include"oatpp-swagger/Resources.hpp"


#ifndef OATPP_SWAGGER_RES_PATH
//#define OATPP_SWAGGER_RES_PATH "F:/encapsulation/encapsulation/encapsulation"
#endif

class SwaggerComponent {
public:
	/**
	* General API docs info
	*/
	OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, swaggerDocumentInfo)([] {
		oatpp::swagger::DocumentInfo::Builder builder;

		builder.setTitle("User entity service")
			.setDescription("CRUD API Example project with swagger docs")
			.setVersion("1.0")
			.setContactName("Ivan Ovsyanochka")
			.setContactUrl("https://oatpp.io")

			.setLicenseName("Apache License,Version 2.0")
			.setLicenseUrl("http://www.apache.org/licenses/LICENSE-2.0")

			.addServer("http://localhost:8000", "server on localhost");

		return builder.build();
		}());

	OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>, swaggerResources)([] {
		return oatpp::swagger::Resources::loadResources(std::string(OATPP_SWAGGER_RES_PATH)+"/config/res");
		}());
};


#endif //OATPP_SWAGGER_ENABLE

#endif //OATPP_SWAGGER_COMPONENT_H