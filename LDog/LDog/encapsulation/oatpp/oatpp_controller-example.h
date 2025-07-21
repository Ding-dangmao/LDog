#ifndef CONTROLLER_EXAMPLE_H
#define CONTROLLER_EXAMPLE_H

#include"oatpp_include.h"


#include OATPP_CODEGEN_BEGIN(ApiController)

class ExampleController :public oatpp::web::server::api::ApiController {
public:

	ExampleController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
		:oatpp::web::server::api::ApiController(objectMapper) {}
#ifndef ASYNC_ENDPOINT
#ifdef OATPP_SWAGGER_ENABLE
	ENDPOINT_INFO(get) {
		info->summary = "create new User";
	}
#endif
	ENDPOINT("GET", "/example/get", get) {
		return createResponse(Status::CODE_200, "hello example!");
	}
#else
	ENDPOINT_ASYNC("GET", "/example/async", async) {
		ENDPOINT_ASYNC_INIT(async)

			Action act()override {
			return _return(controller->createResponse(Status::CODE_200, "hello"));
		}
	};
#endif
};

#include OATPP_CODEGEN_END(ApiController)

#endif