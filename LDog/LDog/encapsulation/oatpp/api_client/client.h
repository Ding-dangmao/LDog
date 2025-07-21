#include"../oatpp_include.h"

#include"oatpp/web/client/ApiClient.hpp"

#include OATPP_CODEGEN_BEGIN(ApiClient)

class ExampleApiClient :public oatpp::web::client::ApiClient {
	API_CLIENT_INIT(ExampleApiClient)

	API_CALL("GET","/example/get",gettest)
};



#include OATPP_CODEGEN_END(ApiClient)