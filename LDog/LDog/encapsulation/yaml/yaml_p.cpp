#include "yaml_p.h"

/**
*
*
*
*/
YamlP::YamlP(const std::string& file_name)
{
	this->config = YAML::LoadFile(file_name);
}

/**
*
*
*
*/
void YamlP::loadFile(const std::string& file_name)
{
	this->config = YAML::LoadFile(file_name);
}
/**
*
*
*
*/
std::vector<std::string> YamlP::split(const std::string& str)const
{
	std::vector<std::string> str_vec;
	std::string::size_type size = str.size();
	std::string::size_type idx_last{ 0 };
	for(int i=0;i<size;i++) {
		//if (!isdigit(str[i]) && str[i] != '.')
		//	return std::vector<std::string>();
		if (str[i] == '.') {
			if (idx_last)
				str_vec.emplace_back(str.substr(idx_last+1, i - idx_last - 1));
			else
				str_vec.emplace_back(str.substr(idx_last, i - idx_last));
			idx_last = i;
		}
	}
	if (idx_last)
		str_vec.emplace_back(str.substr(idx_last+1, size - idx_last-1));
	else
		str_vec.emplace_back(str.substr(idx_last, size - idx_last));
	return str_vec;
}
/**
*
*
*
*/
std::string YamlP::operator[](const std::string& str) const
{

	std::vector<std::string> vec_str = split(str);
	YAML_MACRO(this->config, vec_str.size(), vec_str)
}

