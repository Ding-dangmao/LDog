#ifndef CLIENT_RUN_H
#define CLIENT_RUN_H

#include"client_component.hpp"
#include"client.h"


class ClientRun {
public:

	void operator()() {
		OATPP_COMPONENT(std::shared_ptr<tcp::client::ConnectionProvider>, connection_provider);
		OATPP_COMPONENT(std::shared_ptr<client::HttpRequestExecutor>, request_executor);
		OATPP_COMPONENT(std::shared_ptr<json::mapping::ObjectMapper>, obj);

		auto client = ExampleApiClient::createShared(request_executor, obj);
		auto data = client->gettest()->readBodyToString();
		std::cout << std::string(data);
	}
};


#endif //CLIENT_RUN_H