#ifndef OATPP_DTO_EXAMPLE_H
#define OATPP_DTO_EXAMPLE_H
#include"oatpp_include.h"


#include OATPP_CODEGEN_BEGIN(DTO)


class ExampleDTO :oatpp::DTO {
	DTO_INIT(ExampleDTO, DTO)

	DTO_FIELD(String, message);
	DTO_FIELD(Int32, status_code_);
};

#include OATPP_CODEGEN_END(DTO)

#endif //OATPP_DTO_EXAMPLE_H