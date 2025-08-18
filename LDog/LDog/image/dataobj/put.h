#ifndef PUT_H
#define PUT_H


#include"../config/util_include.h"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace LDog {
	/**
	* Base
	*/
	class BaseDTOPUT :public oatpp::DTO {
	public:
		DTO_INIT(BaseDTOPUT, DTO)

		DTO_FIELD(String, name);
		DTO_FIELD(String, access_token_);
	};
}


class ImageUpload :public LDog::BaseDTOPOST {
	DTO_INIT(ImageUpload, BaseDTOPOST)

	DTO_FIELD(String, image_access_token);
	DTO_FIELD(String, chunk_number);
	DTO_FIELD(String, hash);
	DTO_FIELD(String, image_file);
};


#include OATPP_CODEGEN_END(DTO)




#endif // !PUT_H