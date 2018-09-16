//
// Created by piotr on 05.01.17.
//
#include "Manager.h"

#include "Utils.h"

#include <sstream>
#include <fstream>

namespace hc {
Manager::Manager()
{
    hc::debugLog( "Init" );
}

void Manager::changeState( const State &p_newState )
{
    if( p_newState == m_currentState )
        return;

    std::string stateString;
    switch( p_newState )
    {
    case State::CORNER_DONE:
        m_lastActiveCorner = m_currentCorner;
        stateString = "State::CORNER_DONE";
        break;
    case State::CORNER_START:
        m_startTimeCounter = std::chrono::steady_clock::now();
        stateString = "State::CORNER_START";
        break;
    case State::IDLE:
        m_lastActiveCorner = m_currentCorner;
        stateString = "State::IDLE";
        m_currentCorner = -1;
        break;
    }
    m_currentState = p_newState;

    hc::debugLog("Switched state to " + stateString );
}

void Manager::configure()
{
    m_xDisplay = XOpenDisplay(NULL);
    m_xRootWindow = XDefaultRootWindow(m_xDisplay);
    updateScreenSize();

    m_corners[0].setCornerPos(0,0);
    m_corners[1].setCornerPos(m_xScreenSize[0],0);
    m_corners[2].setCornerPos(0,m_xScreenSize[1]);
    m_corners[3].setCornerPos(m_xScreenSize[0],m_xScreenSize[1]);
    m_detectionMargin = 15;

    const bool configReaded = readConfigFile();

    if(hc::isDebugMode())
    {
        std::stringstream ss;
        ss << "Reading config ended with "
           << ( configReaded ? "succes" : "failure" ) << std::endl;
        hc::debugLog( ss.str() );
    }
    m_currentState = State::IDLE;
}
void Manager::updateScreenSize() {
    Screen* screenPtr = DefaultScreenOfDisplay( m_xDisplay );

    if ( !screenPtr ) {
        hc::errorLog( "Failed to obtain the default screen of given display.\n" );
        return;
    }

    m_xScreenSize[0] = static_cast< unsigned int >( screenPtr->width );
    m_xScreenSize[1] = static_cast< unsigned int >( screenPtr->height );

    if(hc::isDebugMode())
    {
        std::string log = "Screen resolution is ";
        log += std::to_string( this->m_xScreenSize[0] );
        log += 'x';
        log += std::to_string( this->m_xScreenSize[1] );
        hc::debugLog(log);
    }
}

void Manager::start() {
    int tmp;
    unsigned int utmp;

    do
    {
        XQueryPointer(m_xDisplay, m_xRootWindow, &m_xRetRoot,
                      &m_xRetChild, &m_xCursorPos[0],
                      &m_xCursorPos[1], &tmp, &tmp, &utmp);

        // if current counter is not equal to -1 then is active
        if(m_currentCorner != -1) {
            m_lastActiveCorner = m_currentCorner;
        }

        // now lets get is this any of the m_corners
        if( m_currentState == State::IDLE )
        {
            if(hc::isDebugMode())
            {
                std::stringstream ss;
                ss << m_xCursorPos[0] << "x" << m_xCursorPos[1];
                hc::debugLog(ss.str());
            }
            int m_counter = 0;
            m_currentCorner = -1;

            for(auto& corner : m_corners) {
                corner.updateState( m_xCursorPos[0], m_xCursorPos[1], m_detectionMargin);

                if(corner.isActive())
                {
                    m_currentCorner = m_counter;
                    changeState( State::CORNER_START );
                }

                m_counter++;
            }
            if(m_currentCorner != -1 && hc::isDebugMode()) {
                std::stringstream ss;
                ss << "Current corner is this: " << m_currentCorner;
                hc::debugLog(ss.str());
            }
        }
        else if( m_currentState == State::CORNER_START )
        {
            m_corners[m_currentCorner].updateState( m_xCursorPos[0], m_xCursorPos[1], m_detectionMargin);

            if( m_corners[m_currentCorner].isActive() )
            {
                if( DURATION_IN_MS < hc::getTimeSinceMoment( m_startTimeCounter ) )
                {
                    hc::executeCommand( m_corners[m_currentCorner].getCommand() );
                    changeState( State::CORNER_DONE );
                }
                else
                {
                    std::stringstream debugInfo;
                    debugInfo << "Time since start: ";
                    debugInfo << hc::getTimeSinceMoment(m_startTimeCounter);
                    hc::debugLog( debugInfo.str() );
                }
            }
            else
            {
                changeState( State::IDLE );
            }
        }
        else if( m_currentState == State::CORNER_DONE )
        {
            m_corners[m_currentCorner].updateState( m_xCursorPos[0], m_xCursorPos[1], m_detectionMargin );

            if(!m_corners[m_currentCorner].isActive())
            {
                m_currentCorner = -1;
                changeState( State::IDLE );
            }
        }
        hc::sleep( UPDATE_INTERVAL_IN_MS );
    }
    while( true );
}

bool Manager::readConfigFile()
{
    std::ifstream configFile(m_configPath.c_str());
    std::string oneLine;

    if(!configFile.good())
        return false;

    while(std::getline(configFile, oneLine))
    {
        const auto value = getConfigParameterValue(oneLine);
        const auto name = getConfigParameterName(oneLine);

        if( name == "top_left_command")
            m_corners[0].setCommand(value);
        else if( name == "top_right_command")
            m_corners[1].setCommand(value);
        else if( name == "bottom_left_command")
            m_corners[2].setCommand(value);
        else if( name == "bottom_right_command")
            m_corners[3].setCommand(value);
    }
    return true;
}
}
