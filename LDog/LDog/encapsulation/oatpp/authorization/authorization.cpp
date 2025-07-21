#include"authorization.h"

std::shared_ptr<oatpp::web::server::handler::AuthorizationHandler::AuthorizationObject> CustomAuthorizationHandler::authorize(const oatpp::String& userId, const oatpp::String& password) {
	if (userId == this->userId_ && password == this->password_) {
		return std::make_shared<CustomAuthorizationObject>("uid-admin");
	}
	return nullptr;
}

std::shared_ptr<oatpp::web::server::handler::AuthorizationHandler::AuthorizationObject> CustomBearerAuthorizationHandler::authorize(const oatpp::String& token)
{
	if (token==this->token_) {
		return std::make_shared<CustomAuthorizationObject>("uid-admin");
	}
	return nullptr;
}
