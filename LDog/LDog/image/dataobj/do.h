#ifndef DO_H
#define DO_H


#include<iostream>
#include<list>
#include<memory>
template<typename T>
struct basedo {
	public:
	using Wrapper = std::shared_ptr<T>;
	static Wrapper createShared() {
		return std::make_shared<T>();
	}
};

struct image_group_info_do:public basedo< image_group_info_do>{
public:
	std::string id;
	std::string name;
	std::string image_num;
	std::string createtime;
	std::string updatetime;
};

struct image_info_do:public basedo<image_info_do>{
public:
	std::string id;
	std::string name;
	std::string type;
	std::string size;
	std::string width;
	std::string height;
	std::string url;
	std::string createtime;
	std::string updatetime;
};

struct image_group_list_do:public basedo<image_group_list_do> {
	std::list<image_group_info_do::Wrapper> group_list;
};
struct image_list_do:public basedo<image_list_do> {
	std::list<image_info_do::Wrapper> image_list;
};

#endif // !DO_H
