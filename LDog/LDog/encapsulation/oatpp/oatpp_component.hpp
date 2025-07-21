#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include"oatpp_include.h"

/**
* swagger
*/
#ifdef OATPP_SWAGGER_ENABLE
#include"swagger/oatpp_swagger_component.h"
#endif //OATPP_SWAGGER_ENABLE

//#define ASYNC_ENDPOINT

#define CONFIG_BY_YAML

#ifdef CONFIG_BY_YAML
#include"../yaml/yaml_p.h"
#endif // CONFIG_BY_YAML

#define COMPONENT(TYPE, NAME) \
oatpp::base::Environment::Component<TYPE> NAME
#define CREATE_COMPONENT(TYPE) \
 oatpp::base::Environment::Component<TYPE>


class RegisteredComponent {
public:
#ifdef OATPP_SWAGGER_ENABLE
	SwaggerComponent swaggerComponent;
#endif //OATPP_SWAGGER_ENABLE

	using c_ref_string = const std::string&;
	RegisteredComponent(c_ref_string ip, const v_uint16& port);
#ifdef CONFIG_BY_YAML
	RegisteredComponent(const YamlP& yaml);
#endif // CONFIG_BY_YAML
	COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, server_connection_provider);
	OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)([] {
		return oatpp::web::server::HttpRouter::createShared();
		}());
#ifndef ASYNC_ENDPOINT
	OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, server_connection_handler)([] {
		OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
		return oatpp::web::server::HttpConnectionHandler::createShared(router);
		}());
#else
	OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, server_connection_handler)([] {
		OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
		return oatpp::web::server::AsyncHttpConnectionHandler::createShared(router);
		}());
#endif // !ASYNC_ENDPOINT


	OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)([] {
		return oatpp::parser::json::mapping::ObjectMapper::createShared();
		}());
};
inline RegisteredComponent::RegisteredComponent(c_ref_string ip, const v_uint16& port)
	:server_connection_provider(CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>)([&] {
	return oatpp::network::tcp::server::ConnectionProvider::createShared({ ip, port, oatpp::network::Address::IP_4 });
		}()))
{
}

inline RegisteredComponent::RegisteredComponent(const YamlP& yaml)
	:RegisteredComponent(yaml["oatpp.ip"],
		static_cast<v_uint16>(std::atoi(yaml["oatpp.port"].c_str())))
{
}

#endif //COMPONENT_HPP