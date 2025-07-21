#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include"../oatpp_include.h"

class CustomAuthorizationObject : public oatpp::web::server::handler::AuthorizationObject {
public:
	
	CustomAuthorizationObject(const oatpp::String& userId)
		:userId_(userId){}

	oatpp::String userId_;
};

class CustomAuthorizationHandler :public oatpp::web::server::handler::BasicAuthorizationHandler {
public:

	CustomAuthorizationHandler(const oatpp::String& userId, const oatpp::String& password)
		:BasicAuthorizationHandler("custom-realm"),userId_(userId),password_(password){}

	std::shared_ptr<AuthorizationObject> authorize(const oatpp::String& userId, const oatpp::String& password)override;
	oatpp::String userId_;
	oatpp::String password_;
};

class CustomBearerAuthorizationHandler :public oatpp::web::server::handler::BearerAuthorizationHandler {
public:
	CustomBearerAuthorizationHandler(const oatpp::String& token) :BearerAuthorizationHandler("custom-bearer-realm"),token_(token) {}

	std::shared_ptr<AuthorizationObject> authorize(const oatpp::String& token);

	oatpp::String token_;
};

#endif //AUTHORIZATION_H