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





#include OATPP_CODEGEN_END(DTO)




#endif // !PUT_H