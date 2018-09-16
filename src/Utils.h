#ifndef X11HOTCORNER_UTILS_H
#define X11HOTCORNER_UTILS_H
#include <cstdio>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <stdexcept>

#define DEBUG 1

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
    if(!isDebugMode())
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
    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);

    if (!pipe) throw std::runtime_error("popen() failed!");
}

}

#endif // X11HOTCORNER_UTILS_H

