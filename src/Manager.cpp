//
// Created by piotr on 05.01.17.
//

#include "Manager.h"
#include "Utils.h"
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <fstream>

namespace hc{
    Manager::Manager()
    {
        hc::debugLog( "Init" );
        configure();
        start();
    }
    
    void Manager::changeState( const State &newState )
    {
        if( newState == currentState )
            return;
            
        std::string stateString;
        switch( newState )
        {
            case State::CORNER_DONE:
                last_active_corner = current_corner;
                stateString = "State::CORNER_DONE";
                break;
            case State::CORNER_START:
                startTimeCounter = std::chrono::steady_clock::now();
                stateString = "State::CORNER_START";
                break;
            case State::IDLE:
                last_active_corner = current_corner;
                stateString = "State::IDLE";
                current_corner = -1;
                break;
        }
        currentState = newState;
        hc::debugLog("Switched state to " + stateString );
    }
    
    void Manager::configure() 
    {

        this->x_display = XOpenDisplay(NULL);
        this->x_root_window = XDefaultRootWindow(this->x_display);
        this->updateScreenSize();
		
		corners[0].setCornerPos(0,0);
		corners[1].setCornerPos(this->x_screen_size[0],0);
		corners[2].setCornerPos(0,this->x_screen_size[1]);
		corners[3].setCornerPos(this->x_screen_size[0],this->x_screen_size[1]);
		detection_margin = 15;
        
		readConfigFile();
    }
    void Manager::updateScreenSize() {
        Screen* m_screen_pointer = NULL;


        m_screen_pointer = DefaultScreenOfDisplay( this->x_display );
        if ( !m_screen_pointer ) {
            fprintf(stderr, "Failed to obtain the default screen of given display.\n");
            return;
        }

        x_screen_size[0] = static_cast< unsigned int >( m_screen_pointer->width );
        x_screen_size[1] = static_cast< unsigned int >( m_screen_pointer->height );
        std::string log = "Screen resolution is ";
        log += std::to_string( this->x_screen_size[0] );
        log += 'x';
        log += std::to_string( this->x_screen_size[1] );
        hc::debugLog(log);
    }

    void Manager::start() {
        currentState = State::IDLE;
        int m_empty;
        unsigned int m_mask;
        do
        {
            XQueryPointer(this->x_display, this->x_root_window, &this->x_ret_root,
                          &this->x_ret_child, &this->x_cursor_pos[0],
                          &this->x_cursor_pos[1],&m_empty, &m_empty, &m_mask);
            
            // if current counter is not  equal to -1 then is active 
            if(current_corner != -1){
                this->last_active_corner = this->current_corner; 
            }
            
            // now lets get is this any of the corners
            if( currentState == State::IDLE )
            {
                printf("+%d+%d\n", this->x_cursor_pos[0], this->x_cursor_pos[1]);
                int m_counter = 0;
                current_corner = -1;
                for(auto corner : corners){
                    corner.updateState( this->x_cursor_pos[0], this->x_cursor_pos[1], detection_margin);
                    if(corner.isActive())
                    {
                        current_corner = m_counter;
                        changeState( State::CORNER_START );
                    }
                    m_counter++;
                }
                if(current_corner != -1){
                    printf("Current corner is this: +%d\n", this->current_corner);
                }
            }
            else if( currentState == State::CORNER_START )
            {
                corners[current_corner].updateState( this->x_cursor_pos[0], this->x_cursor_pos[1], detection_margin);
                if( corners[current_corner].isActive() )
                {
                    if( DURATION_IN_MS < hc::getTimeSinceMoment( startTimeCounter ) )
                    {
                        const auto command = corners[current_corner].getCommand();
                        hc::debugLog( "Execute command: " + command );
                        changeState( State::CORNER_DONE );
                    }
                    else
                    {
                        std::stringstream debugInfo;
                        debugInfo << "Time since start: ";
                        debugInfo << hc::getTimeSinceMoment(startTimeCounter);
                        hc::debugLog( debugInfo.str() );
                    }
                }
                else
                {
                    changeState( State::IDLE );
                }
            }
            else if( currentState == State::CORNER_DONE )
            {
                corners[current_corner].updateState( this->x_cursor_pos[0], this->x_cursor_pos[1], detection_margin);
                if(!corners[current_corner].isActive())
                {
                    current_corner = -1;
                    changeState( State::IDLE );
                }
                
            }
            usleep( 51221 );
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
                    corners[0].setCommand(value);
            else if( name == "top_right_command")
                    corners[1].setCommand(value);
            else if( name == "bottom_left_command")
                    corners[2].setCommand(value);
            else if( name == "bottom_right_command")
                    corners[3].setCommand(value);
        }
        return true;
    }
}
