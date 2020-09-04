#ifndef X11HOTCORNER_UTILS_H
#define X11HOTCORNER_UTILS_H
#include <cstdio>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <stdexcept>
#include <algorithm>

#define DEBUG 0

namespace hc
{
using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;
const char APP_TAG[]  = "X11_HotCorner";

bool isDebugMode()
{
    return DEBUG;
}

void debugLog( const std::string &s )
{
    if(!isDebugMode() || s.empty())
        return;
    std::clog << '[' << APP_TAG << ']' << s << '\n';
}

void errorLog( const std::string &s )
{
    std::cerr << "[" << APP_TAG << "]" << s << '\n';
}

int getTimeSinceMoment( TimePoint tp )
{
    const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>
                          (std::chrono::steady_clock::now() - tp);
    return duration.count();
}

void sleep(const int& ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

std::string getConfigParameterName( const std::string& s )
{
    return s.substr(0, s.find("="));
}

std::string getConfigParameterValue( const std::string& s )
{
    return s.substr(s.find("=")+1);
}

int getConfigParameterIntValue( const std::string& s )
{
    return std::stoi( getConfigParameterValue(s) );
}

void executeCommand( const std::string &command )
{
    debugLog( "Execute command: " + command );

    const std::string commandToExecute = command + std::string("&");
    std::system(commandToExecute.c_str());

}

bool stringToBool( const std::string &s )
{
    static std::array<std::string,3> stringTrue = {"true", "True", "TRUE"};

    return std::any_of(stringTrue.begin(),stringTrue.end(),
        [s](std::string& el){
            return (s.find(el) != std::string::npos);
        });
}
}

#endif // X11HOTCORNER_UTILS_H

