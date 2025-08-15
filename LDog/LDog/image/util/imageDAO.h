#ifndef IMAGE_DAO_H
#define IMAGE_DAO_H

#include"../config/util_include.h"
#include"../../Base/baseDAO.h"
#include<unordered_map>

#define  VALID_RESULT(ptr,return_type)\
if(ptr.get()==nullptr) return return_type::createShared();

class ImageDAO :public BaseDAO {
public:
	ImageDAO() {
		YamlP yaml(YAML_CONFIG_FILE_CONNECTION);
		this->mysql_ = MysqlP::CreateShared(yaml);
	}
	template<DAO T>
	inline ImageDAO(T& dao) :BaseDAO(dao.getMysql()) {}
	//template<DAO T>
	//inline ImageDAO(T* dao) : BaseDAO(dao->getMysql()) {}

	inline std::shared_ptr<MysqlP> getMysql() {
		return this->mysql_;
	}

public:

};
#endif //IMAGE_DAO_H
