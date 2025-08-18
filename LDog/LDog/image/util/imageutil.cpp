#include "imageutil.h"
#include"imageutil.h"



std::string ImageUtil::tempRouteAssign(const std::string& file_name)
{
	return file_name + Clock::time();
}

std::string ImageUtil::imageAccessTokenGenerate()
{
	return AccessToken::keyGeneratorRT(32);
}

bool ImageUtil::imageUploadfolderCreate(const std::string& folder_name)
{
	using namespace std::filesystem;
	try {
		create_directory(std::string(IMAGE_TEMP_FILE_PATH) + "/" + folder_name);
	}catch (const std::filesystem::filesystem_error& e) {
		std::cerr << "Error creating directory: " << e.what() << std::endl;
		return false;
	}
	return true;
}

bool ImageUtil::imageUploadInfoSave(const std::string& data, const std::string& folder_name)
{
	ToolP::SaveStringToFile(std::string(IMAGE_UPLOAD_INFO_PATH) + "/" + folder_name, data, std::ios_base::out);

	return true;
}

bool ImageUtil::imageUploadTempClear(const std::string& folder_name)
{
	using namespace std::filesystem;
	remove(std::string(IMAGE_UPLOAD_INFO_PATH) + "/" + folder_name);
	remove_all(std::string(IMAGE_TEMP_FILE_PATH) + "/" + folder_name);
	return true;
}

bool ImageUtil::imageCopyToStorage(const std::string& tempfolder_name, c_ref_string file_name_t)
{
	using namespace std::filesystem;
	rename(
		std::string(IMAGE_TEMP_FILE_PATH) + "/" + tempfolder_name + "/" + "1",
		std::string(IMAGE_TEMP_FILE_PATH) + "/" + tempfolder_name + "/" + file_name_t);
	copy_file(
		std::string(IMAGE_TEMP_FILE_PATH) + "/" + tempfolder_name + "/" + file_name_t,
		std::string(IMAGE_FILE_PATH) + "/" + file_name_t,
		std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive);
	return true;
}

bool ImageUtil::imageChunkSave(const std::string& tempfolder_name, const std::string& chunk_name,const std::string& data)
{
	std::string file_name = std::string(IMAGE_TEMP_FILE_PATH) + "/" + tempfolder_name + "/" + chunk_name;
	return ToolP::SaveStringToFile(file_name, data, std::ios_base::out | std::ios_base::binary);
}

bool ImageUtil::imageChunkMerge(const std::string& tempfolder_name, int chunk_num)
{
	std::string file_route = std::string(IMAGE_TEMP_FILE_PATH) + "/" + tempfolder_name;
	std::vector<std::string> file_list;
	for (int i = 1; i <= chunk_num; i++) {
		file_list.push_back(file_route + "/" + std::to_string(i));
	}
	ToolP::appendDataFile(file_list);
	return true;
}

bool ImageUtil::checkStartSHA256(std::initializer_list<std::string> l1, std::initializer_list<std::string> l2)
{
	if (l1.size() != l2.size()) {
		return false;
	}
	for (const auto& item : l1) {
		if (std::find(l2.begin(), l2.end(), item) == l2.end()) {
			return false;
		}
	}
	return true;
}

bool ImageUtil::checkChunkSHA256(std::string hash, std::string data)
{
	
	return true;
}
