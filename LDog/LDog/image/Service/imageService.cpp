#include "imageService.h"
#include "imageService.h"
#include"imageService.h"

ImageUploadStartReturn::Wrapper ImageService::uploadStart(const ImageUploadStart::Wrapper dto)
{
	ImageDAO image_dao;
	AccountDAO account_dao(image_dao);

	auto dto_r = ImageUploadStartReturn::createShared();
	c_ref_str nickname = static_cast<std::string>(dto->name);
	c_ref_str access_token = static_cast<std::string>(dto->access_token_);
	c_ref_str image_group = static_cast<std::string>(dto->image_group);
	c_ref_str file_sha256 = static_cast<std::string>(dto->FILE_SHA256);
	c_ref_str file_head_4k_sha256 = static_cast<std::string>(dto->FILE_HEAD_4k_SHA256);
	c_ref_str file_tail_4k_sha256 = static_cast<std::string>(dto->FILE_TAIL_4k_SHA256);
	// Check if the user exists and if the access token is valid
	if (!account_dao.isExistAccount(nickname)) {
		dto_r->is_success_ = false;
		dto_r->message_ = "User does not exist.";
		return dto_r;
	}
	int id = account_dao.getAccountId(nickname);
	//if (!(account_dao.checkAccessToken(id, access_token) && account_dao.checkAccessTokenValidityPeriod(id, access_token))) {
	//	dto_r->is_success_ = false;
	//	dto_r->message_ = "Invalid access token.";
	//	return dto_r;
	//}
	//检验是否命中
	if (image_dao.isExistImage(id, file_sha256, file_head_4k_sha256, file_tail_4k_sha256)) {
		int image_id = image_dao.getImageIdBySHA256(id, file_sha256, file_head_4k_sha256, file_tail_4k_sha256);
		// 处理命中情况
		if(!image_dao.isExistGroup(image_group,id))
			image_dao.insertImageGroup(id, image_group);
		//获取group_id
		int group_id = image_dao.getImageGroupId(image_group, id);
		//插入关联
		image_dao.insertImageAndGroupRelation(image_id, group_id);
		//命中直接返回url
		dto_r->url_ = image_dao.getImageKeyByImageId(image_id);
		dto_r->message_ = "Image already exists.";
		dto_r->is_hit = true;
		dto_r->is_success_ = true;
	}
	else {
		//未命中，生成临时文件夹
		//生成access_token
		std::string image_access_token = ImageUtil::imageAccessTokenGenerate();
		//临时名称
		std::string temp_folder_name = nickname + Clock::timeUnix();
		//映射
		ImageService::imageAccessTokenMap[image_access_token] = temp_folder_name;
		//映射2
		ImageService::imageAccessTokenMap2[image_access_token] = 0;
		//创建临时文件夹
		if (!ImageUtil::imageUploadfolderCreate(temp_folder_name)) {
			dto_r->is_success_ = false;
			dto_r->message_ = "Failed to create temporary folder.";
			return dto_r;
		}
		//保存上传信息
		if (!ImageUtil::imageUploadInfoSave(static_cast<std::string>(dto->upload_info_json), temp_folder_name)) {
			dto_r->is_success_ = false;
			dto_r->message_ = "Failed to save upload information.";
			return dto_r;
		}
		dto_r->image_upload_access_token = image_access_token;
		dto_r->message_ = " Image does not exist, proceed to upload.";
		dto_r->is_hit = false;
		dto_r->is_success_ = true;
	}

    return dto_r;
}

ImageUploadReturn::Wrapper ImageService::uploadImage(const ImageUpload::Wrapper dto)
{
	ImageDAO image_dao;
	AccountDAO account_dao(image_dao);

	auto dto_r = ImageUploadReturn::createShared();

	c_ref_str nickname = static_cast<std::string>(dto->name);
	c_ref_str access_token = static_cast<std::string>(dto->access_token_);
	c_ref_str image_access_token = static_cast<std::string>(dto->image_access_token);
	c_ref_str chunk_number = static_cast<std::string>(dto->chunk_number);
	if(ImageService::imageAccessTokenMap.find(image_access_token) == ImageService::imageAccessTokenMap.end()) {
		dto_r->is_success_ = false;
		dto_r->message_ = "Invalid image access token.";
		return dto_r;
	}
	std::string temp_folder_name = ImageService::imageAccessTokenMap[image_access_token];
	//// Check if the user exists
	if (!account_dao.isExistAccount(nickname)) {
		dto_r->is_success_ = false;
		dto_r->message_ = "User does not exist.";
		return dto_r;
	}
	//int id = account_dao.getAccountId(nickname);
	ImageUtil::imageChunkSave(temp_folder_name, chunk_number, static_cast<std::string>(dto->image_file));
	if(!ImageUtil::checkChunkSHA256(dto->hash,dto->image_file)) {
		dto_r->is_success_ = false;
		dto_r->message_ = "Chunk SHA256 mismatch.";
		return dto_r;
	}
	dto_r->is_success_ = true;
	dto_r->message_ = "Chunk uploaded successfully.";
	return dto_r;
}

ImageGroupListReturn::Wrapper ImageService::getImageGroupInfo(const image_group_info_get::Wrapper dto)
{
	ImageDAO image_dao;
	AccountDAO account_dao(image_dao);

	ImageGroupListReturn::Wrapper dto_r = ImageGroupListReturn::createShared();
	dto_r->group_list = oatpp::List<ImageGroupInfo>::createShared();
	std::string name = static_cast<std::string>(dto->name);
	std::string access_token = static_cast<std::string>(dto->access_token_);
	// Check if the user exists and if the access token is valid
	if (!account_dao.isExistAccount(name)) {
		dto_r->is_success_ = false;
		dto_r->message_ = "User does not exist.";
	}
	int id = account_dao.getAccountId(name);
	image_group_list_do::Wrapper group_list_do = image_dao.getImageGroupByUserID(id);

	for (auto i : group_list_do->group_list) {
		ImageGroupInfo dto = ImageGroupInfo({ "","","","","" });
		dto->id = i->id; dto->name = i->name; dto->image_num = i->image_num; dto->createtime = i->createtime; dto->updatetime = i->updatetime;;
		dto_r->group_list->push_back(dto);
	}
	dto_r->is_success_ = true;
	dto_r->message_ = "Image group information retrieved successfully.";
	return dto_r;
}

ImageListReturn::Wrapper ImageService::getImageInfo(const image_info_get::Wrapper dto)
{
	ImageDAO image_dao;
	AccountDAO account_dao(image_dao);
	ImageListReturn::Wrapper dto_r = ImageListReturn::createShared();
	dto_r->image_list = oatpp::List<ImageInfo>::createShared();
	std::string name = static_cast<std::string>(dto->name);
	std::string access_token = static_cast<std::string>(dto->access_token_);
	int group_id = std::atoi(static_cast<std::string>(dto->group_id).c_str());	
	// Check if the user exists and if the access token is valid
	if (!account_dao.isExistAccount(name)) {
		dto_r->is_success_ = false;
		dto_r->message_ = "User does not exist.";
	}
	int id = account_dao.getAccountId(name);
	image_list_do::Wrapper image_list_do = image_dao.getImageByGroupID(group_id);
	for (auto i : image_list_do->image_list) {
		ImageInfo dto = ImageInfo({ "","","","","","","","","" });
		dto->id = i->id; dto->name = i->name; dto->type = i->type; dto->size = i->size; dto->width = i->width; dto->height = i->height; dto->url = i->url; dto->createtime = i->createtime; dto->updatetime = i->updatetime;
		dto_r->image_list->push_back(dto);
	}
	dto_r->is_success_ = true;
	dto_r->message_ = "Image information retrieved successfully.";
	return dto_r;
}

ImageCompleteReturn::Wrapper ImageService::uploadComplete(const ImageUploadComplete::Wrapper dto)
{
	ImageDAO image_dao;
	AccountDAO account_dao(image_dao);
	auto dto_r = ImageCompleteReturn::createShared();
	c_ref_str nickname = static_cast<std::string>(dto->name);
	c_ref_str access_token = static_cast<std::string>(dto->access_token_);
	c_ref_str image_access_token = static_cast<std::string>(dto->image_access_token);
	if (ImageService::imageAccessTokenMap.find(image_access_token) == ImageService::imageAccessTokenMap.end()) {
		dto_r->is_success_ = false;
		dto_r->message_ = "Invalid image access token.";
		return dto_r;
	}
	std::string temp_folder_name = ImageService::imageAccessTokenMap[image_access_token];

	// Check if the user exists
	if (!account_dao.isExistAccount(nickname)) {
		dto_r->is_success_ = false;
		dto_r->message_ = "User does not exist.";
		return dto_r;
	}
	int id = account_dao.getAccountId(nickname);
	//拼接切片
	YamlP yaml(std::string(IMAGE_UPLOAD_INFO_PATH) + "/" + temp_folder_name);
	int chunk_num = std::atoi(yaml["chunk_num"].c_str());
	if (chunk_num != 1) {
		ImageUtil::imageChunkMerge(temp_folder_name, chunk_num);
	}
	c_ref_str image_name = yaml["image_name"];
	c_ref_str image_type = yaml["image_type"];
	c_ref_str image_group = yaml["image_group"];
	c_ref_str image_hash = yaml["image_hash"];
	c_ref_str image_head_4k_hash = yaml["image_head_4k_hash"];
	c_ref_str image_tail_4k_hash = yaml["image_tail_4k_hash"];
	signed image_size = std::atoi(yaml["image_size"].c_str());
	signed image_width = std::atoi(yaml["image_width"].c_str());
	signed image_height = std::atoi(yaml["image_height"].c_str());
	//c_ref_str new_image_name = nickname + Clock::timeUnix() + "." + image_type;
	std::string image_key = AccessToken::keyGeneratorRT(64);
	image_key = boost::urls::encode(image_key, boost::urls::unreserved_chars);
	c_ref_str new_image_name =image_key +"."+image_type;
	//复制数据到存储文件
	ImageUtil::imageCopyToStorage(temp_folder_name, new_image_name);
	ImageUtil::imageUploadTempClear(temp_folder_name);
	if (!image_dao.isExistGroup(image_group, id)) {
		image_dao.insertImageGroup(id, image_group);
	}
	image_dao.insertImage(id, image_key, image_hash, image_head_4k_hash, image_tail_4k_hash,
			image_name, image_type, new_image_name, image_size, image_width, image_height);
	image_dao.insertImageAndGroupRelation(
		image_dao.getImageIdBySHA256(id, image_hash, image_head_4k_hash, image_tail_4k_hash),
		image_dao.getImageGroupId(image_group, id)
	);
	dto_r->is_success_ = true;
	dto_r->message_ = "Image upload completed successfully.";
	dto_r->url_ = image_key;
	return dto_r;
}



std::unordered_map<std::string, std::string> ImageService::imageAccessTokenMap;
std::unordered_map<std::string, short> ImageService::imageAccessTokenMap2;

