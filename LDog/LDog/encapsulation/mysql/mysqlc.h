#ifndef MYSQL_P_H
#define MYSQL_P_H

#include<iostream>
#include<memory>
#include<regex>

#include<mysql/jdbc.h>
#include<mutex>

#define MULTIPLET_THREADS

#define CONFIG_BY_YAML
#define MYSQL_TEST

#ifdef CONFIG_BY_YAML
#include"../yaml/yaml_p.h"
#endif // CONFIG_BY_YAML




class MysqlP {
	using c_ref_string = const std::string&;
	struct guard_PrepareStatement;
	typedef guard_PrepareStatement guard_pre;
public:
	MysqlP(c_ref_string ip, c_ref_string port, c_ref_string user, c_ref_string password, c_ref_string Schema)noexcept;
	static std::shared_ptr<MysqlP> CreateShared(c_ref_string ip, c_ref_string port, c_ref_string user, c_ref_string password, c_ref_string Schema)noexcept;
#ifdef CONFIG_BY_YAML
	MysqlP(const YamlP& yaml)noexcept;
	static std::shared_ptr<MysqlP> CreateShared(const YamlP& yaml)noexcept;
#endif // CONFIG_BY_YAML

	~MysqlP();

	class guard_ResultSet {
	public:
		inline explicit guard_ResultSet(sql::ResultSet* result_set) {
			this->result_set = result_set;
		}
		inline guard_ResultSet(void*) {
			this->result_set = nullptr;
		}
		inline ~guard_ResultSet() {
			delete this->result_set;
		}
		inline sql::ResultSet*& get() { return this->result_set; }
		sql::ResultSet* result_set;
	};
public:
	void execute(c_ref_string statement);
	template<typename... Args>
	void executePre(c_ref_string statement, Args... args);
	guard_ResultSet executeQuery(c_ref_string statement);
	template<typename... Args>
	guard_ResultSet executePreQuery(c_ref_string statement, Args... args);

private:
	template<typename T>
	void padParameters(guard_pre& prestatement, int idx, T parameter)noexcept;
	//Registration
	//void registered(c_ref_string ip,c_ref_string port,c_ref_string user);
	//Destruction
	bool verifyConnection(int num);
	bool reconnect(int num);

	bool isValid();
	bool reconnect();

private:
	struct guard_PrepareStatement {
		inline guard_PrepareStatement(sql::Connection*& con, c_ref_string statement) {
			this->prestmt = con->prepareStatement(statement);
		}
		inline guard_PrepareStatement() {
			delete this->prestmt;
		}
		inline sql::PreparedStatement*& getPreStmt() {
			return this->prestmt;
		}
		sql::PreparedStatement* prestmt;
	};
	//Connector/C++ takes care of freeing but it is not thread-safe
	sql::mysql::MySQL_Driver* driver;
	//need explicitly delete
	sql::Connection* con;
	sql::Statement* stmt;

	sql::ResultSet* res;
#ifdef MULTIPLET_THREADS
	//static std::mutex driver_mutex;
#endif
	//Registration and Destruction
	std::string registered;
	std::string prefix_s = ".\n host: ";
	std::string suffix_s = "\n port: [0-9]+\n user: [a-zA-Z]+\n.";
public:

};


#endif
/**
*
* should add
*
*/
template<typename ...Args>
inline void MysqlP::executePre(c_ref_string statement, Args ...args)
{
	if (!verifyConnection(3))return;
	size_t idx{ 1 };
	auto tuple_arg = std::make_tuple(args...);
	guard_pre prestatement(this->con, statement);
	((padParameters(prestatement, idx++, args)), ...);
#ifdef MYSQL_TEST
	try
	{
#endif // MYSQL_TEST
		prestatement.getPreStmt()->execute();
#ifdef MYSQL_TEST
	}
	catch (const sql::SQLException& e)
	{
		//std::cout << e.what();
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
	}
#endif // MYSQL_TEST

}

template<typename ...Args>
inline MysqlP::guard_ResultSet MysqlP::executePreQuery(c_ref_string statement, Args ...args)
{
	if (!verifyConnection(3))return nullptr;
#ifdef MYSQL_TEST
	try
	{
#endif // MYSQL_TEST
		size_t idx{ 1 };
		auto tuple_arg = std::make_tuple(args...);
		guard_pre prestatement(this->con, statement);
		((padParameters(prestatement, idx++, args)), ...);
		return guard_ResultSet(prestatement.getPreStmt()->executeQuery());
#ifdef MYSQL_TEST
	}
	catch (const sql::SQLException& e)
	{
		//std::cout << e.what();
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
	}
#endif // MYSQL_TEST
}

template<typename T>
inline void MysqlP::padParameters(guard_pre& prestatement, int idx, T parameter)noexcept
{
#ifdef MYSQL_TEST
	try
	{
#endif // MYSQL_TEST
		if constexpr (std::is_same_v<int, T>) {
			prestatement.getPreStmt()->setInt(idx, parameter);
		}
		if constexpr (std::is_same_v<bool, T>)
		{
			prestatement.getPreStmt()->setBoolean(idx, parameter);
		}
		if constexpr (std::is_same_v<std::string, T>)
		{
			prestatement.getPreStmt()->setString(idx, parameter);
		}
		if constexpr (std::is_same_v<char*, T>)
		{
			prestatement.getPreStmt()->setString(idx, parameter);
		}
		if constexpr (std::is_same_v<const char*, T>)
		{
			prestatement.getPreStmt()->setString(idx, parameter);
		}
		if constexpr (std::is_same_v<double, T>)
		{
			prestatement.getPreStmt()->setDouble(idx, parameter);
		}
#ifdef MYSQL_TEST
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		std::cout << "# ERR: Exception in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
	}
#endif // MYSQL_TEST
}
