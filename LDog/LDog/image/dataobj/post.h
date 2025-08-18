#ifndef POST_H
#define POST_H
#include"../config/util_include.h"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace LDog {
	/**
	* Base
	*/
	class BaseDTOPOST :public oatpp::DTO {
	public:
		DTO_INIT(BaseDTOPOST, DTO)

		DTO_FIELD(String, name);
		DTO_FIELD(String, access_token_);
	};
}

class ImageUploadStart :public LDog::BaseDTOPOST {
	DTO_INIT(ImageUploadStart, BaseDTOPOST)

	DTO_FIELD(String, upload_info_json);
	DTO_FIELD(String, image_group);
	DTO_FIELD(String, FILE_SHA256);
	DTO_FIELD(String, FILE_HEAD_4k_SHA256);
	DTO_FIELD(String, FILE_TAIL_4k_SHA256);

};

class ImageUploadComplete :public LDog::BaseDTOPOST {
	DTO_INIT(ImageUploadComplete, BaseDTOPOST)

	DTO_FIELD(String, image_access_token);
};




#include OATPP_CODEGEN_END(DTO)


#endif // !POST_H