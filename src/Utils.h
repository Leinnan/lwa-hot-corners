#ifndef X11HOTCORNER_UTILS_H
#define X11HOTCORNER_UTILS_H
#include <iostream>
#include <time.h>
#include <chrono>
#include <thread>

#define DEBUG 1

namespace hc
{
    using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;
    const char APP_TAG[]  = "X11_HotCorner";
    
    void debugLog( const std::string &s )
    {
#if DEBUG
        std::clog << '[' << APP_TAG << ']' << s << '\n';
#endif
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
}

#endif // X11HOTCORNER_UTILS_H

