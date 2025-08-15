#include"imageutil.h"

bool ImageUtil::checkSHA256(const std::string& nickname, std::initializer_list<std::string> SHA256_list)
{

	return false;
}

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
