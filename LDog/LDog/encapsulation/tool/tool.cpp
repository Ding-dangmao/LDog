#include"tool.h"



system_clock::time_point Clock::systemClock()
{
	return system_clock::now();
}

steady_clock::time_point Clock::steadyClock()
{
	return steady_clock::now();
}

high_resolution_clock::time_point Clock::highResolutionClock()
{
	return high_resolution_clock::now();
}
/*
* 获取时间格式为: 星期 月 日 时分秒 年 
*/
char* Clock::time() {
	const time_t t_t= system_clock::to_time_t(Clock::systemClock());
	return std::ctime(&t_t);
}


void ToolP::splitStr(char*str,const char*delim, std::vector<std::string>& vec) {
	char* tp;
	tp=strtok(str, delim);
	short id{};
	while (tp) {
		vec[id++]=tp;
		tp= strtok(NULL, delim);
	}
}

//void ToolP::splitStr(char*str, const char* delim, std::string* vec) {
//	char* tp;
//	tp = strtok(str, delim);
//	short id{};
//	while (tp) {
//		//vec.push_back(tp);
//		vec[id++] = tp;
//		tp = strtok(str, delim);
//	}
//}