#ifndef IMAGE_DAO_H
#define IMAGE_DAO_H

#include"../config/util_include.h"
#include"../../Base/baseDAO.h"


#include<initializer_list>
#include"../dataobj/obj.h"



#define  VALID_RESULT(ptr,return_type)\
if(ptr.get()==nullptr) return return_type::createShared();

class ImageDAO :public BaseDAO {
public:
	ImageDAO() {
		YamlP yaml(YAML_CONFIG_FILE_CONNECTION);
		this->mysql_ = MysqlP::CreateShared(yaml);
	}
	inline ImageDAO(c_ref_string yaml_path) :BaseDAO(yaml_path) {}
	template<DAO T>
	inline ImageDAO(T& dao) :BaseDAO(dao.getMysql()) {}
	//template<DAO T>
	//inline ImageDAO(T* dao) : BaseDAO(dao->getMysql()) {}

	inline std::shared_ptr<MysqlP> getMysql() {
		return this->mysql_;
	}

public:

	std::string serializeImageSHA256(
		c_ref_string a_sha256,
		c_ref_string h_sha256,
		c_ref_string t_sha256);
	bool insertImage(int user_id,
		c_ref_string image_key,
		c_ref_string a_sha256, 
		c_ref_string h_sha256, 
		c_ref_string t_sha256,
		c_ref_string image_name,
		c_ref_string image_type,
		c_ref_string url,
		signed image_size,
		signed image_width,
		signed image_height);
	bool insertImageGroup(int user_id,c_ref_string group_name);
	bool insertImageAndGroupRelation(int image_id, int group_id);

	bool isExistGroup(c_ref_string group_name,int user_id);
	bool isExistImage(int user_id,c_ref_string a_sha256, c_ref_string h_sha256, c_ref_string t_sha256);

	std::string getImageKeyByImageId(int image_id);
	std::string getImageURLByImageKey(c_ref_string image_key);
	int getImageIdBySHA256(int user_id,c_ref_string a_sha256, c_ref_string h_sha256, c_ref_string t_sha256);
	int getImageGroupId(c_ref_string group_name, int user_id);
	image_group_list_do::Wrapper getImageGroupByUserID(int user_id);
	image_list_do::Wrapper getImageByGroupID(int group_id);


};
#endif //IMAGE_DAO_H
