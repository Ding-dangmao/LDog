#ifndef INFORMATION_CONTROLLER_H
#define INFORMATION_CONTROLLER_H

#include"../../encapsulation/oatpp/oatpp_include.h"
#include"../config/util_include.h"

#include"../oatpp/oatpp_DTO-example.h"




#include OATPP_CODEGEN_BEGIN(ApiController)

class ImageController :public oatpp::web::server::api::ApiController {
public:

	ImageController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
		:oatpp::web::server::api::ApiController(objectMapper) {}




	ENDPOINT("GET", "/pic", pic){
		auto fileStream = std::make_shared<oatpp::data::stream::FileInputStream>("./8.jpg");
		auto body = std::make_shared<oatpp::web::protocol::http::outgoing::StreamingBody>(fileStream);
		auto response = OutgoingResponse::createShared(Status::CODE_200, body);
		//response->putHeader(oatpp::web::protocol::http::Header::CONTENT_TYPE, "image/jpeg");
		return response;
	}

	ENDPOINT("GET", "/picture/ ", picture) {

		return createResponse(Status::CODE_200, "Ok");
	}



private:
};

#include OATPP_CODEGEN_END(ApiController)

#endif //INFORMATION_CONTROLLER_H