#ifndef X11HOTCORNER_UTILS_H
#define X11HOTCORNER_UTILS_H
#include <iostream>
#include <time.h>

#define DEBUG 1

namespace hc
{
    const char APP_TAG[]  = "X11_HotCorner";
    
    void debugLog( const std::string &s )
    {
#if DEBUG
        std::clog << '[' << APP_TAG << ']' << s << '\n';
#endif
    }
    
}

#endif // X11HOTCORNER_UTILS_H

