#ifndef IMAGE_CONTROLLER_H
#define IMAGE_CONTROLLER_H

#include"../../encapsulation/oatpp/oatpp_include.h"
#include"../config/util_include.h"

#include"../oatpp/oatpp_DTO-example.h"

#include<chrono>
#include<thread>

#include"../dataobj/obj.h"

#include"../Service/imageService.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

namespace multipart = oatpp::web::mime::multipart;

class ImageController :public oatpp::web::server::api::ApiController {
public:

	ImageController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
		:oatpp::web::server::api::ApiController(objectMapper) {}



	ENDPOINT_ASYNC("GET", "/picture/async", async) {
		ENDPOINT_ASYNC_INIT(async)
			Action act()override {
			auto fileStream = std::make_shared<oatpp::data::stream::FileInputStream>("./8.jpg");
			auto body = std::make_shared<oatpp::web::protocol::http::outgoing::StreamingBody>(fileStream);
			auto response = OutgoingResponse::createShared(Status::CODE_200, body);
			response->putHeader(oatpp::web::protocol::http::Header::CONTENT_TYPE, "image/jpeg");
			return this->_return(response);
		}
	};

	ENDPOINT_ASYNC("POST", "/picture/upload_start", upload_start,
		BODY_DTO(ImageUploadStart::Wrapper,dd)) {
		ENDPOINT_ASYNC_INIT(upload_start)
		Action act()override {
			return request->readBodyToDtoAsync<ImageUploadStart::Wrapper>
				(controller->getDefaultObjectMapper())
				.callbackTo(&upload_start::onBodyObtained);
		}

		Action onBodyObtained(const oatpp::Object<ImageUploadStart>& dto) {

			return _return(controller->createDtoResponse(Status::CODE_200,ImageService::uploadStart(dto)));
		}
	};

	ENDPOINT_ASYNC("PUT", "/picture/upload", image_upload) {
		ENDPOINT_ASYNC_INIT(image_upload)
			Action act()override {
			auto multipart = std::make_shared<multipart::PartList>(request->getHeaders());

			/* Create multipart reader. */
			multipart::Reader multipartReader(multipart.get());

			multipartReader.setPartReader("part1", multipart::createFilePartReader("F:/t.png"));

			request->transferBody(&multipartReader);

			auto part1 = multipart->getNamedPart("part1");

			//auto inputStream = part1->getInputStream();

			return this->_return(
				ResponseFactory::createResponse(Status::CODE_200, "File uploaded successfully")
			);
		}
	};

	ENDPOINT_ASYNC("POST", "/picture/upload_complete", upload_complete) {
		ENDPOINT_ASYNC_INIT(upload_complete)
			Action act()override {

			return this->_return(
				ResponseFactory::createResponse(Status::CODE_200, "File uploaded successfully")
			);
		}
	};
	 



private:
};

#include OATPP_CODEGEN_END(ApiController)

#endif //IMAGE_CONTROLLER_H