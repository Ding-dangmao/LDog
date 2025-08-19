#ifndef IMAGE_UTIL_H
#define IMAGE_UTIL_H

#include<iostream>
#include<initializer_list>
#include<unordered_map>
#include<filesystem>
#include"../config/util_include.h"
#include"access_token/access_token.h"

class ImageUtil {
public:
	using c_ref_string = const std::string&;
	//路径分配
	static std::string tempRouteAssign(const std::string& file_name);
	//生成图片上传的access_token
	static std::string imageAccessTokenGenerate();
	//创建图片上传的临时文件夹
	static bool imageUploadfolderCreate(const std::string& folder_name);
	//保存图片上传信息
	static bool imageUploadInfoSave(const std::string& data, const std::string& folder_name);
	//删除所有临时文件
	static bool imageUploadTempClear(const std::string& folder_name);
	//删除无效缓存
	static bool clearInvaildCache();
	//复制合成图片至存储文件夹
	static bool imageCopyToStorage(const std::string& tempfolder_name,c_ref_string file_name_t);
	//保存图片切片
	static bool imageChunkSave(const std::string& tempfolder_name, const std::string& chunk_name,const std::string& data);
	//图片切片合成
	static bool imageChunkMerge(const std::string& tempfolder_name,int chunk_num);
	//检验Start的SHA256
	static bool checkStartSHA256(std::initializer_list<std::string>l1,std::initializer_list<std::string> l2);
	//检验Chunk的SHA256
	static bool checkChunkSHA256(std::string hash, std::string data);
};

#endif //IMAGE_UTIL_H