#ifndef IMAGE_UTIL_H
#define IMAGE_UTIL_H

#include<iostream>
#include<initializer_list>
#include<unordered_map>
#include<filesystem>
#include"access_token/access_token.h"

class ImageUtil {
public:
	//Check if the SHA256 hash of the file matches any in the provided list
	//顺序分别为文件全体SHA256,文件头4k SHA256,文件尾4k SHA256
	bool checkSHA256(const std::string& nickname, std::initializer_list<std::string> SHA256_list);

	static std::string tempRouteAssign(const std::string& file_name);
	static std::string imageAccessTokenGenerate();
	static bool imageUploadfolderCreate(const std::string& folder_name);
	static bool imageUploadInfoSave(const std::string& data, const std::string& folder_name);

	//access_token -> folder_name+unix_time
	static std::unordered_map<std::string, std::string> imageAccessTokenMap;
};

#endif //IMAGE_UTIL_H