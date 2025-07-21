#ifndef BASE_DAO_H
#define BASE_DAO_H

template<typename T>
concept DAO = requires(T a) {
	a.getMysql();
};

class BaseDAO {
public:
	using c_ref_string = const std::string&;
public:
	inline BaseDAO() { this->time_str_.resize(10); }
	inline BaseDAO(c_ref_string yaml_path) {
		this->time_str_.resize(10);
		YamlP yaml(yaml_path);
		this->mysql_ = MysqlP::CreateShared(yaml);
	}
	inline BaseDAO(std::shared_ptr<MysqlP> mysql) :mysql_(mysql) { this->time_str_.resize(10); }
	virtual std::shared_ptr<MysqlP> getMysql() = 0;

	std::shared_ptr<MysqlP> mysql_;

	//刷新时间
	inline void refreshTime() {
		ToolP::splitStr(Clock::time(), " ", this->time_str_);
		//this->time_=this->time_str_[]
		if (this->time_str_[1] == "Jan")
			this->time_ = this->time_str_[4].substr(0, this->time_str_[4].find("\n")) + "-" + "1" + "-" + this->time_str_[2] + " " + this->time_str_[3];
		else if (this->time_str_[1] == "Feb")
			this->time_ = this->time_str_[4].substr(0, this->time_str_[4].find("\n")) + "-" + "2" + "-" + this->time_str_[2] + " " + this->time_str_[3];
		else if (this->time_str_[1] == "Mar")
			this->time_ = this->time_str_[4].substr(0, this->time_str_[4].find("\n")) + "-" + "3" + "-" + this->time_str_[2] + " " + this->time_str_[3];
		else if (this->time_str_[1] == "Apr")
			this->time_ = this->time_str_[4].substr(0, this->time_str_[4].find("\n")) + "-" + "4" + "-" + this->time_str_[2] + " " + this->time_str_[3];
		else if (this->time_str_[1] == "May")
			this->time_ = this->time_str_[4].substr(0, this->time_str_[4].find("\n")) + "-" + "5" + "-" + this->time_str_[2] + " " + this->time_str_[3];
		else if (this->time_str_[1] == "Jun")
			this->time_ = this->time_str_[4].substr(0, this->time_str_[4].find("\n")) + "-" + "6" + "-" + this->time_str_[2] + " " + this->time_str_[3];
		else if (this->time_str_[1] == "Jul")
			this->time_ = this->time_str_[4].substr(0, this->time_str_[4].find("\n")) + "-" + "7" + "-" + this->time_str_[2] + " " + this->time_str_[3];
		else if (this->time_str_[1] == "Aug")
			this->time_ = this->time_str_[4].substr(0, this->time_str_[4].find("\n")) + "-" + "8" + "-" + this->time_str_[2] + " " + this->time_str_[3];
		else if (this->time_str_[1] == "Sep")
			this->time_ = this->time_str_[4].substr(0, this->time_str_[4].find("\n")) + "-" + "9" + "-" + this->time_str_[2] + " " + this->time_str_[3];
		else if (this->time_str_[1] == "Oct")
			this->time_ = this->time_str_[4].substr(0, this->time_str_[4].find("\n")) + "-" + "10" + "-" + this->time_str_[2] + " " + this->time_str_[3];
		else if (this->time_str_[1] == "Nov")
			this->time_ = this->time_str_[4].substr(0, this->time_str_[4].find("\n")) + "-" + "11" + "-" + this->time_str_[2] + " " + this->time_str_[3];
		else if (this->time_str_[1] == "Dec")
			this->time_ = this->time_str_[4].substr(0, this->time_str_[4].find("\n")) + "-" + "12" + "-" + this->time_str_[2] + " " + this->time_str_[3];
		else
			this->time_ = this->time_str_[4].substr(0, this->time_str_[4].find("\n")) + "-" + "1" + "-" + this->time_str_[2] + " " + this->time_str_[3];
}
public:
	//存储时间,每次取用前使用refreshTime函数进行刷新
	std::vector<std::string> time_str_;
	std::string time_;
};

#endif // !BASE_DAO_H
