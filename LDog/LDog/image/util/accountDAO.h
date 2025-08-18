#ifndef ACCOUNT_DAO_H
#define ACCOUNT_DAO_H

#include"../config/util_include.h"
#include"../../Base/baseDAO.h"

class AccountDAO :public BaseDAO {
	using c_ref_string = const std::string&;
public:
	//
	inline AccountDAO() {
		YamlP yaml(YAML_CONFIG_FILE_CONNECTION);
		this->mysql_ = MysqlP::CreateShared(yaml);
	}
	inline AccountDAO(c_ref_string yaml_path) :BaseDAO(yaml_path) {}
	template<DAO T>
	inline AccountDAO(T dao) : BaseDAO(dao.getMysql()) {}
	//
	inline std::shared_ptr<MysqlP> getMysql() {
		return this->mysql_;
	}

	bool isExistAccount(c_ref_string)const;
	bool passwordConsistent(c_ref_string, c_ref_string)const;
	bool passwordConsistent(int id, c_ref_string)const;

	bool insertAccount(c_ref_string, c_ref_string);
	bool updateAccount();
	bool deleteAccount();
	//access_token
	void updateAccessToken(int id, c_ref_string);
	bool checkAccessToken(int id, c_ref_string);
	bool checkAccessTokenValidityPeriod(int id, c_ref_string);
	int getAccountId(c_ref_string)const;
	bool checkAccountAccessToken(c_ref_string nickname, c_ref_string access_token);
};

#endif // !ACCOUNT_DAO_H
