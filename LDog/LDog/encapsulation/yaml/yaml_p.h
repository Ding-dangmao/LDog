#ifndef YAML_P_H
#define YAML_P_H


#include"yaml-cpp/yaml.h"
#include<iostream>
#include<tuple>

#define MAX 20
#define YAML_MACRO(yaml,param_nums,vec) YAML_JUDGE_PARAM(yaml,param_nums,vec)
#define YAML_JUDGE_PARAM(yaml,param_nums,vec)\
if(param_nums==N1)YAML_INVOKE_##1(yaml,vec)\
if(param_nums==N2)YAML_INVOKE_##2(yaml,vec)\
if(param_nums==N3)YAML_INVOKE_##3(yaml,vec)\
if(param_nums==N4)YAML_INVOKE_##4(yaml,vec)\
if(param_nums==N5)YAML_INVOKE_##5(yaml,vec)\
if(param_nums==N6)YAML_INVOKE_##6(yaml,vec)\
if(param_nums==N7)YAML_INVOKE_##7(yaml,vec)\
if(param_nums==N8)YAML_INVOKE_##8(yaml,vec)\
if(param_nums==N9)YAML_INVOKE_##9(yaml,vec)\
if(param_nums==N10)YAML_INVOKE_##10(yaml,vec)\
if(param_nums==N11)YAML_INVOKE_##11(yaml,vec)\
if(param_nums==N12)YAML_INVOKE_##12(yaml,vec)
#define YAML_INVOKE_1(yaml,vec) return yaml[vec.at(0)].as<std::string>();
#define YAML_INVOKE_2(yaml,vec) return yaml[vec.at(0)][vec.at(1)].as<std::string>();
#define YAML_INVOKE_3(yaml,vec) return yaml[vec.at(0)][vec.at(1)][vec.at(2)].as<std::string>();
#define YAML_INVOKE_4(yaml,vec) return yaml[vec.at(0)][vec.at(1)][vec.at(2)][vec.at(3)].as<std::string>();
#define YAML_INVOKE_5(yaml,vec) return yaml[vec.at(0)][vec.at(1)][vec.at(2)][vec.at(3)][vec.at(4)].as<std::string>();
#define YAML_INVOKE_6(yaml,vec) return yaml[vec.at(0)][vec.at(1)][vec.at(2)][vec.at(3)][vec.at(4)][vec.at(5)].as<std::string>();
#define YAML_INVOKE_7(yaml,vec) return yaml[vec.at(0)][vec.at(1)][vec.at(2)][vec.at(3)][vec.at(4)][vec.at(5)][vec.at(6)].as<std::string>();
#define YAML_INVOKE_8(yaml,vec) return yaml[vec.at(0)][vec.at(1)][vec.at(2)][vec.at(3)][vec.at(4)][vec.at(5)][vec.at(6)][vec.at(7)].as<std::string>();
#define YAML_INVOKE_9(yaml,vec) return yaml[vec.at(0)][vec.at(1)][vec.at(2)][vec.at(3)][vec.at(4)][vec.at(5)][vec.at(6)][vec.at(7)][vec.at(8)].as<std::string>();
#define YAML_INVOKE_10(yaml,vec) return yaml[vec.at(0)][vec.at(1)][vec.at(2)][vec.at(3)][vec.at(4)][vec.at(5)][vec.at(6)][vec.at(7)][vec.at(8)][vec.at(9)].as<std::string>();
#define YAML_INVOKE_11(yaml,vec) return yaml[vec.at(0)][vec.at(1)][vec.at(2)][vec.at(3)][vec.at(4)][vec.at(5)][vec.at(6)][vec.at(7)][vec.at(8)][vec.at(9)][vec.at(10)].as<std::string>();
#define YAML_INVOKE_12(yaml,vec) return yaml[vec.at(0)][vec.at(1)][vec.at(2)][vec.at(3)][vec.at(4)][vec.at(5)][vec.at(6)][vec.at(7)][vec.at(8)][vec.at(9)][vec.at(10)][vec.at(11)].as<std::string>();
#define N1 1
#define N2 2
#define N3 3
#define N4 4
#define N5 5
#define N6 6
#define N7 7
#define N8 8
#define N9 9
#define N10 10
#define N11 11
#define N12 12
      
class YamlP {
public:
	//初始化
	YamlP() = default;
	explicit YamlP(const std::string& file_name);

	void loadFile(const std::string& file_name);
private:
	//隐藏接口
	std::vector<std::string> split(const std::string& str)const;
public:
	//开放接口
	std::string operator[](const std::string& str)const;
private:
	//隐藏成员
	YAML::Node config;
};

#endif //YAML_P_H