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
	//·������
	static std::string tempRouteAssign(const std::string& file_name);
	//����ͼƬ�ϴ���access_token
	static std::string imageAccessTokenGenerate();
	//����ͼƬ�ϴ�����ʱ�ļ���
	static bool imageUploadfolderCreate(const std::string& folder_name);
	//����ͼƬ�ϴ���Ϣ
	static bool imageUploadInfoSave(const std::string& data, const std::string& folder_name);
	//ɾ��������ʱ�ļ�
	static bool imageUploadTempClear(const std::string& folder_name);
	//ɾ����Ч����
	static bool clearInvaildCache();
	//���ƺϳ�ͼƬ���洢�ļ���
	static bool imageCopyToStorage(const std::string& tempfolder_name,c_ref_string file_name_t);
	//����ͼƬ��Ƭ
	static bool imageChunkSave(const std::string& tempfolder_name, const std::string& chunk_name,const std::string& data);
	//ͼƬ��Ƭ�ϳ�
	static bool imageChunkMerge(const std::string& tempfolder_name,int chunk_num);
	//����Start��SHA256
	static bool checkStartSHA256(std::initializer_list<std::string>l1,std::initializer_list<std::string> l2);
	//����Chunk��SHA256
	static bool checkChunkSHA256(std::string hash, std::string data);
};

#endif //IMAGE_UTIL_H