#ifndef GET_H
#define GET_H
#include<iostream>
#include<memory>

namespace LDog {
	/**
	* Base
	*/
	template<typename T>
	class BaseGET {
	public:
		using Wrapper = std::shared_ptr<T>;
		template<typename... Args>
		static Wrapper createShared(Args... args) {
			return std::make_shared<T>(std::forward<Args>(args)...);
		}
		std::string name;
		std::string access_token_;
	};
}

struct image_info_get:public LDog::BaseGET<image_info_get>{
	std::string group_id;
};

struct image_group_info_get:public LDog::BaseGET<image_group_info_get> {

};

#endif //!GET_H