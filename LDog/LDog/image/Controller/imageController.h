#ifndef IMAGE_CONTROLLER_H
#define IMAGE_CONTROLLER_H

#include<boost/url.hpp>

#include"../../encapsulation/oatpp/oatpp_include.h"
#include"../config/util_include.h"

#include"../oatpp/oatpp_DTO-example.h"

#include<chrono>
#include<thread>

#include"../dataobj/obj.h"

#include"../Service/imageService.h"

namespace TopcTool {
	void decode(oatpp::String& t);

	template<typename ...Args>
	void decodeS(Args& ...args) {
		(decode(args), ...);
		return;
	}
}

#include OATPP_CODEGEN_BEGIN(ApiController)

namespace multipart = oatpp::web::mime::multipart;

class ImageController :public oatpp::web::server::api::ApiController {
public:

	ImageController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
		:oatpp::web::server::api::ApiController(objectMapper) {
		auto mapper = dynamic_cast<oatpp::parser::json::mapping::ObjectMapper*>(objectMapper.get());
		{
			auto config = mapper->getSerializer()->getConfig();
			config->enabledInterpretations = { "custom-types" };
		}

		{
			auto config = mapper->getDeserializer()->getConfig();
			config->enabledInterpretations = { "custom-types" };
		}
	}



	ENDPOINT_ASYNC("GET", "/picture/async", async) {
		ENDPOINT_ASYNC_INIT(async)
			Action act()override {
			std::string image_key = request->getQueryParameter("image_key");
			ImageDAO dao;
			std::string url = dao.getImageURLByImageKey(image_key);
			if(url.empty()) {
				return _return(controller->createDtoResponse(Status::CODE_404,ImageGetReturn::createShared()));
			}
			std::string pre = std::string(IMAGE_FILE_PATH)+ "/"+ url;
			auto fileStream = std::make_shared<oatpp::data::stream::FileInputStream>(pre.c_str());
			auto body = std::make_shared<oatpp::web::protocol::http::outgoing::StreamingBody>(fileStream);
			auto response = OutgoingResponse::createShared(Status::CODE_200, body);
			response->putHeader(oatpp::web::protocol::http::Header::CONTENT_TYPE, "image/jpeg");
			return this->_return(response);
		}
	};

	ENDPOINT_ASYNC("POST", "/picture/upload_start", upload_start) {
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
		std::shared_ptr<multipart::Multipart> m_multipart;
		Action act()override {
			m_multipart = std::make_shared<multipart::PartList>(request->getHeaders());
			auto multipartReader = std::make_shared<multipart::AsyncReader>(m_multipart);
			multipartReader->setPartReader("image_file", multipart::createAsyncInMemoryPartReader(1024*1024*5 /* max-data-size */));
			multipartReader->setPartReader("name", multipart::createAsyncInMemoryPartReader(1024 * 1024 * 5 /* max-data-size */));
			multipartReader->setPartReader("access_token", multipart::createAsyncInMemoryPartReader(1024 * 1024 * 5 /* max-data-size */));
			multipartReader->setPartReader("image_access_token", multipart::createAsyncInMemoryPartReader(1024 * 1024 * 5 /* max-data-size */));
			multipartReader->setPartReader("hash", multipart::createAsyncInMemoryPartReader(1024 * 1024 * 5 /* max-data-size */));
			multipartReader->setPartReader("chunk_number", multipart::createAsyncInMemoryPartReader(1024 * 1024 * 5 /* max-data-size */));

			return request->transferBodyAsync(multipartReader).next(yieldTo(&image_upload::onBodyObtained));
		}

		Action onBodyObtained() {
			auto dto = ImageUpload::createShared();
			auto image_file = static_cast<multipart::PartList*>(m_multipart.get())->getNamedPart("image_file");
			auto name = static_cast<multipart::PartList*>(m_multipart.get())->getNamedPart("name");
			auto access_token = static_cast<multipart::PartList*>(m_multipart.get())->getNamedPart("access_token");
			auto image_access_token = static_cast<multipart::PartList*>(m_multipart.get())->getNamedPart("image_access_token");
			auto hash = static_cast<multipart::PartList*>(m_multipart.get())->getNamedPart("hash");
			auto chunk_number = static_cast<multipart::PartList*>(m_multipart.get())->getNamedPart("chunk_number");
			dto->image_file = image_file->getPayload()->getInMemoryData();
			dto->name = name->getPayload()->getInMemoryData();
			dto->access_token_ = access_token->getPayload()->getInMemoryData();
			dto->image_access_token = image_access_token->getPayload()->getInMemoryData();
			dto->hash = hash->getPayload()->getInMemoryData();
			dto->chunk_number = chunk_number->getPayload()->getInMemoryData();
			return _return(
				controller->createDtoResponse(Status::CODE_200, ImageService::uploadImage(dto))
			);
		}
	};

	ENDPOINT_ASYNC("POST", "/picture/upload_complete", upload_complete) {
		ENDPOINT_ASYNC_INIT(upload_complete)
			Action act()override {

			return request->readBodyToDtoAsync<ImageUploadComplete::Wrapper>
				(controller->getDefaultObjectMapper())
				.callbackTo(&upload_complete::onBodyObtained);
		}

		Action onBodyObtained(const oatpp::Object<ImageUploadComplete>& dto) {
			return _return(controller->createDtoResponse(Status::CODE_200, ImageService::uploadComplete(dto)));
		}
	};

	ENDPOINT_ASYNC("GET","/picture/group_info",group_info) {
		ENDPOINT_ASYNC_INIT(group_info)
		Action act()override {
			oatpp::String name = request->getQueryParameter("name");
			oatpp::String access_token = request->getQueryParameter("access_token");
			TopcTool::decodeS(const_cast<oatpp::String&>(name));
			image_group_info_get::Wrapper dto = image_group_info_get::createShared();
			dto->name = name->c_str();
			dto->access_token_ = access_token->c_str();
			return _return(controller->createDtoResponse(Status::CODE_200, ImageService::getImageGroupInfo(dto)));
		}
	};	

	ENDPOINT_ASYNC("GET","/picture/list",image_list) {
		ENDPOINT_ASYNC_INIT(image_list)
		Action act()override {
			image_info_get::Wrapper dto = image_info_get::createShared();
			try {
				oatpp::String name = request->getQueryParameter("name");
				TopcTool::decodeS(const_cast<oatpp::String&>(name));
				oatpp::String access_token = request->getQueryParameter("access_token");
				oatpp::String group_id = request->getQueryParameter("group_id");


				dto->name = name->c_str();
				dto->access_token_ = access_token->c_str();
				dto->group_id = group_id->c_str();
			}catch(const std::exception& e) {
				return _return(controller->createResponse(Status::CODE_400, "Invalid parameters."));
			}
			return _return(controller->createDtoResponse(Status::CODE_200,ImageService::getImageInfo(dto)));
		}
	};

private:
};

#include OATPP_CODEGEN_END(ApiController)

#endif //IMAGE_CONTROLLER_H