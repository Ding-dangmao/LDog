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

};

class ImageUploadComplete :public LDog::BaseDTOPOST {
	DTO_INIT(ImageUploadComplete, BaseDTOPOST)

};

class ImageUpload:public LDog::BaseDTOPOST {
	DTO_INIT(ImageUpload, BaseDTOPOST)

};



#include OATPP_CODEGEN_END(DTO)


#endif // !POST_H