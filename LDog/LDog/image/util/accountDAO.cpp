#include"accountDAO.h"


bool AccountDAO::isExistAccount(c_ref_string nickname)const {
	const std::string& sql_statement = "select COUNT(*) from account_storge where nickname=?";
	MysqlP::guard_ResultSet result_set = this->mysql_->executePreQuery(sql_statement, nickname);

	result_set.get()->next();

	return result_set.get()->getBoolean(1);
}

bool AccountDAO::passwordConsistent(c_ref_string ps1, c_ref_string ps2)const {
	return ps1 == ps2;
}
/*
* ͨ
*/
bool AccountDAO::passwordConsistent(int id, c_ref_string ps)const {
	const std::string& sql_statement = "select EXISTS(select * from account_storge where id=? and password=?)";
	MysqlP::guard_ResultSet result_set = this->mysql_->executePreQuery(sql_statement, id, ps);
	result_set.get()->next();
	return result_set.get()->getBoolean(1);
}

bool AccountDAO::insertAccount(c_ref_string nickname, c_ref_string password) {
	if (this->isExistAccount(nickname)) {
		return false;
	}
	//constexpr std::string sql_statement = "";
	refreshTime();
	std::vector<std::string> sql_statements =
	{ "insert into account_storge (nickname, password, type, create_time, update_time) VALUE (?,?,?,?,?)"};
	//std::cout << std::endl << this->time_ << std::endl;
	this->mysql_->executePre(sql_statements[0], nickname, password, 0, this->time_, this->time_);
	return true;
}
bool AccountDAO::updateAccount() {
	return true;
}
bool AccountDAO::deleteAccount() {
	return true;
}

int AccountDAO::getAccountId(c_ref_string nickname)const {
	const std::string& sql_statement = "select id from account_storge where nickname=?";
	MysqlP::guard_ResultSet result_set = this->mysql_->executePreQuery(sql_statement, nickname);
	result_set.get()->next();
	return result_set.get()->getInt(1);
}

bool AccountDAO::checkAccountAccessToken(c_ref_string nickname, c_ref_string access_token)
{
	if (!this->isExistAccount(nickname)) {
		return false;
	}
	int id = this->getAccountId(nickname);
	return this->checkAccessToken(id, access_token) && this->checkAccessTokenValidityPeriod(id, access_token);
}

void AccountDAO::updateAccessToken(int id, c_ref_string access_token) {
	this->refreshTime();
	const std::string& sql_statement = "insert into access_token (user_id, token, validity_period, createtime) VALUE (?,?,?,?)";
	this->mysql_->executePre(sql_statement, id, access_token, 10, this->time_);
}

bool AccountDAO::checkAccessToken(int id, c_ref_string access_token) {
	c_ref_string sql_statement = "select EXISTS(select * from access_token where user_id=? and token=?)";
	MysqlP::guard_ResultSet result_set = this->mysql_->executePreQuery(sql_statement, id, access_token);
	result_set.get()->next();
	return result_set.get()->getBoolean(1);
}

bool AccountDAO::checkAccessTokenValidityPeriod(int id, c_ref_string access_token) {
	this->refreshTime();
	//const std::string& sql_statement = "select DATEDIFF(?,(select createtime from access_token where user_id=? ORDER BY access_token.createtime DESC LIMIT 0,1))<(select validity_period from access_token where user_id=? ORDER BY access_token.createtime DESC LIMIT 0,1 )";
	c_ref_string sql_statement = "select DATEDIFF(?,(select createtime from access_token where user_id=? and token=?))<(select validity_period from access_token where user_id=? and token=?)";
	MysqlP::guard_ResultSet result_set = this->mysql_->executePreQuery(sql_statement, this->time_, id, access_token, id, access_token);
	result_set.get()->next();
	return result_set.get()->getBoolean(1);
}
