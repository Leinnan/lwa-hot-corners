//
// Created by piotr on 05.01.17.
//

#include "Manager.h"
#include "Utils.h"
#include <unistd.h>
#include <iostream>


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
                timeCounter = 0.0;
                stateString = "State::CORNER_DONE";
                break;
            case State::CORNER_START:
                timeCounter = TIME_DURATION;
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
                    timeCounter -= 0.05;
                    if( timeCounter < 0 )
                    {
                        const auto command = corners[current_corner].getCommand();
                        hc::debugLog( "Execute command: " + command );
                        changeState( State::CORNER_DONE );
                    }
                }
                else
                {
                    changeState( State::IDLE );
                }
            }
            else if( currentState == State::CORNER_DONE )
            {
                // ToDo
            }
            usleep( 51221 );
        }
        while( true );
	}
}
