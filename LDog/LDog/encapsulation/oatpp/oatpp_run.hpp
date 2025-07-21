#ifndef OATPP_RUN_H
#define OATPP_RUN_H


#include"oatpp_include.h"

/**
* swagger
*/
#ifdef OATPP_SWAGGER_ENABLE
#include"oatpp-swagger/Controller.hpp"
#include"oatpp-swagger/AsyncController.hpp"
#endif

#define OATPP_INIT_P(function) \
oatpp::base::Environment::init();\
function();\
oatpp::base::Environment::destroy();


class OatppRun {
public:
	template<typename T>
	inline void operator()(T controller) {
		OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

		oatpp::web::server::api::Endpoints docEndpoints;
		docEndpoints = router->addController(controller)->getEndpoints();
#ifdef OATPP_SWAGGER_ENABLE
#ifndef ASYNC_ENDPOINT
		router->addController(oatpp::swagger::Controller::createShared(docEndpoints));
#else
		router->addController(oatpp::swagger::AsyncController::createShared(docEndpoints));
#endif // !ASYNC_ENDPOINT
#endif
		OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connection_handler);
		OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, server_connection_provider);

		oatpp::network::Server server(server_connection_provider, connection_handler);

		OATPP_LOGI("MyApp", "Server running on port %s", server_connection_provider->getProperty("port").getData());

		server.run();
	}
};


#endif //OATPP_RUN_H