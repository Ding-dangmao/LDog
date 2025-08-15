#ifndef RETURN_H
#define RETURN_H

#include"../config/util_include.h"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace LDog {
	/**
	* Base
	*/
	class BaseDTOR :public oatpp::DTO {
	public:
		DTO_INIT(BaseDTOR, DTO)

		DTO_FIELD(Boolean, is_success_);
		DTO_FIELD(String, message_);
	};
}

class ImageUploadStartReturn :public LDog::BaseDTOR {
	DTO_INIT(ImageUploadStartReturn, BaseDTOR)

	DTO_FIELD(String, image_upload_access_token);

	DTO_FIELD(Boolean, is_hit);
	DTO_FIELD(String, url_);
};

class ImageUploadReturn:public LDog::BaseDTOR {
	DTO_INIT(ImageUploadReturn, BaseDTOR)


};

class ImageCompleteReturn :public LDog::BaseDTOR {
	DTO_INIT(ImageCompleteReturn, BaseDTOR)
	DTO_FIELD(String, url_);
};


#include OATPP_CODEGEN_END(DTO)
#endif // !RETURN_H