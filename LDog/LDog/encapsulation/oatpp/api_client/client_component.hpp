#ifndef CLIENT_COMPONENT_H
#define CLIENT_COMPONENT_H

#include"../oatpp_include.h"
#include"../../include_all/oatpp-1.3.0/oatpp/web/client/ApiClient.hpp"
#include"../../include_all/oatpp-1.3.0/oatpp/core/macro/codegen.hpp"
#include "../../include_all/oatpp-1.3.0/oatpp/web/client/HttpRequestExecutor.hpp"
#include "../../include_all/oatpp-1.3.0/oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "../../include_all/oatpp-1.3.0/oatpp/network/tcp/client/ConnectionProvider.hpp"

#define CONFIG_BY_YAML

#ifdef CONFIG_BY_YAML
#include"../yaml/yaml_p.h"
#endif // CONFIG_BY_YAML

#define COMPONENT(TYPE, NAME) \
oatpp::base::Environment::Component<TYPE> NAME
#define CREATE_COMPONENT(TYPE) \
 oatpp::base::Environment::Component<TYPE>

using namespace oatpp::network;
using namespace oatpp::web;
using namespace oatpp::parser;

class ClientRegisteredComponent {
public:
	using c_ref_string = const std::string&;
	ClientRegisteredComponent(c_ref_string ip, const v_uint16& port);	

#ifdef CONFIG_BY_YAML
	ClientRegisteredComponent(const YamlP& yaml);
#endif // CONFIG_BY_YAML

	COMPONENT(std::shared_ptr<tcp::client::ConnectionProvider>, client_connection_provider);
	COMPONENT(std::shared_ptr<client::HttpRequestExecutor>, client_request_executor);
	OATPP_CREATE_COMPONENT(std::shared_ptr<json::mapping::ObjectMapper>, objectMapper)([] {
		return json::mapping::ObjectMapper::createShared();
		}());

};

inline ClientRegisteredComponent::ClientRegisteredComponent(c_ref_string ip, const v_uint16& port) 
	:
	client_connection_provider(CREATE_COMPONENT(std::shared_ptr<tcp::client::ConnectionProvider>)([&]{
		return tcp::client::ConnectionProvider::createShared({ ip,port,oatpp::network::Address::IP_4 });
		}())),
	client_request_executor(CREATE_COMPONENT(std::shared_ptr<client::HttpRequestExecutor>)([]{
	OATPP_COMPONENT(std::shared_ptr<oatpp::network::tcp::client::ConnectionProvider>, connection_provider);
		return client::HttpRequestExecutor::createShared(connection_provider);
		}()))
{}

inline ClientRegisteredComponent::ClientRegisteredComponent(const YamlP & yaml) 
	:ClientRegisteredComponent(yaml["oatpp-client.ip"],
	static_cast<v_uint16>(std::atoi(yaml["oatpp-client.port"].c_str())))
{}




#endif //CLIENT_COMPONENT_H