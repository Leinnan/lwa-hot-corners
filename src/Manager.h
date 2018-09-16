//
// Created by piotr on 05.01.17.
//

#ifndef X11HOTCORNER_MANAGER_H
#define X11HOTCORNER_MANAGER_H

#include <X11/Xlib.h>
#include <array>
#include <chrono>
#include <stdlib.h>
#include <stdio.h>
#include "Corner.h"


namespace hc {

using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;
const int DEFAULT_DURATION_IN_MS = 300;
const int UPDATE_INTERVAL_IN_MS = 60;

class Manager {
public:
    enum class State
    {
        IDLE,
        CORNER_START,
        CORNER_DONE
    };
    Manager();
    void                        configure();
    void                        start();
    void                        setConfigPath( const std::string &p_path );

private:
    void                        updateScreenSize();
    void                        configureCornersPos();
    void                        changeState( const State &p_newState );
    bool                        readConfigFile();

    Display                    *m_xDisplay;
    Window                      m_xRootWindow;
    Window                      m_xRetRoot;
    Window                      m_xRetChild;
    std::array<hc::Corner, 4>   m_corners;
    std::array<unsigned int, 2> m_xScreenSize;
    std::array<int, 2>          m_xCursorPos;
    int                         m_lastActiveCorner;
    int                         m_currentCorner;
    unsigned int                m_detectionMargin;
    int                         m_holdDuration;
    State                       m_currentState;
    TimePoint                   m_startTimeCounter;
    std::string                 m_configPath;
};
}


#endif //X11HOTCORNER_MANAGER_H
