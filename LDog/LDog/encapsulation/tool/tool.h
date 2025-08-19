#ifndef TOOL_H
#define TOOL_H

#include<iostream>
#include<fstream>
#include<initializer_list>
#include<random>
#include<chrono>
#include<functional>
#include<sstream>
#include"../oatpp/oatpp_include.h"
//#include<boost/url.hpp>

using namespace std::chrono;


constexpr std::size_t IMAGE_CHUNK_SIZE = 1 * 1024 * 1024;  // 1 MiB
class IntRandomGen {
public:
    IntRandomGen(int max_val, int min_val) :
        p(max_val, min_val),
        f(std::bind(std::uniform_int_distribution<>(p), std::default_random_engine{ std::random_device{}() }))
    {
    }
    int operator()() {
        return f();
    }
private:
    std::uniform_int_distribution<>::param_type p;
    decltype(std::bind(std::uniform_int_distribution<>(p), std::default_random_engine{})) f;
};

using namespace std::chrono;
class Clock {

public:
    static system_clock::time_point systemClock();
    static steady_clock::time_point steadyClock();
    static high_resolution_clock::time_point highResolutionClock();

	static std::string timeUnix();
    static char* time();
};

namespace ToolP {
    inline char buffer[IMAGE_CHUNK_SIZE];
    void splitStr(char*, const char*, std::vector<std::string>&);

    void decode(oatpp::String &);

    template<typename ...Args>
    void decodeS(Args& ...args) {
        (ToolP::decode(args), ...);
        return;
    }
	bool createFile(const std::string& file_name);
	bool SaveStringToFile(const std::string& file_name, const std::string& data,std::ios_base::openmode mode);
//	void SaveSringToFile(const std::string& file_name,const std::string& data);
	bool appendDataFile(const std::vector<std::string> file_list);
	int splitDataFile(const std::string& file_name,const std::string& save_path);
}




#endif // !TOOL_H
