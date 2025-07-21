#ifndef TOOL_H
#define TOOL_H

#include<iostream>
#include<random>
#include<chrono>
#include<functional>

using namespace std::chrono;

class IntRandomGen {
public:
    IntRandomGen(int max_val, int min_val) :
        p(max_val, min_val),
        f(std::bind(std::uniform_int_distribution<>(p), std::default_random_engine{ static_cast<unsigned int>(time(0)) }))
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

    static char* time();
};

namespace ToolP {
    void splitStr(char*,const char*, std::vector<std::string>&);
    //void splitStr(char*, const char*, std::string*);
}



#endif // !TOOL_H
