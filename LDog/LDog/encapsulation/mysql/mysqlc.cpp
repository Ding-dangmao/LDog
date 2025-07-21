#include "mysqlc.h"

MysqlP::MysqlP(c_ref_string ip, c_ref_string port, c_ref_string user, c_ref_string password, c_ref_string Schema)noexcept
{
	//not thread-safe
	try {

		this->driver = sql::mysql::get_mysql_driver_instance();
		this->con = driver->connect("tcp://" + ip + ":" + port, user, password);
		this->con->setSchema(Schema);
		this->stmt = this->con->createStatement();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}
std::shared_ptr<MysqlP> MysqlP::CreateShared(c_ref_string ip, c_ref_string port, c_ref_string user, c_ref_string password, c_ref_string Schema) noexcept
{
	return std::make_shared<MysqlP>(ip, port, user, password, Schema);
}
#ifdef CONFIG_BY_YAML
MysqlP::MysqlP(const YamlP& yaml)noexcept : MysqlP(yaml["mysql.ip"], yaml["mysql.port"], yaml["mysql.user"], yaml["mysql.password"], yaml["mysql.schema"]) {}
std::shared_ptr<MysqlP> MysqlP::CreateShared(const YamlP& yaml) noexcept
{
	return std::make_shared<MysqlP>(yaml);
}
#endif // CONFIG_BY_YAML
void MysqlP::execute(c_ref_string statement)
{
	if (!verifyConnection(3))return;
	this->stmt->execute(statement);
}

MysqlP::guard_ResultSet MysqlP::executeQuery(c_ref_string statement)
{
	if (!verifyConnection(3))return nullptr;
	return guard_ResultSet(this->stmt->executeQuery(statement));
}

bool MysqlP::verifyConnection(int num)
{
	if (isValid())return true;
	reconnect(num);
	return isValid();
}

bool MysqlP::reconnect(int num)
{
	if (isValid())return true;
	while (num--) {
		if (reconnect())return true;
	}
	return isValid();
}

bool MysqlP::isValid()
{
	return this->con->isValid();
}

bool MysqlP::reconnect()
{
	return this->con->reconnect();
}



MysqlP::~MysqlP()
{
	delete con;
	delete stmt;
}



