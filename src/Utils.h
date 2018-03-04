#ifndef X11HOTCORNER_UTILS_H
#define X11HOTCORNER_UTILS_H
#include <iostream>
#include <time.h>
#include <chrono>

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
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds> 
                    (std::chrono::steady_clock::now() - tp);
        return duration.count();
    }
    
}

#endif // X11HOTCORNER_UTILS_H

