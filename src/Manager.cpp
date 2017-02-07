//
// Created by piotr on 05.01.17.
//

#include "Manager.h"


namespace hc{
    Manager::Manager() {

    }
    void Manager::configure() {

        this->x_display = XOpenDisplay(NULL);
        this->x_root_window = XDefaultRootWindow(this->x_display);
        this->updateScreenSize();
		
		corners[0].setCornerPos(0,0);
		corners[1].setCornerPos(this->x_screen_size[0],0);
		corners[2].setCornerPos(0,this->x_screen_size[1]);
		corners[3].setCornerPos(this->x_screen_size[0],this->x_screen_size[1]);
		detection_margin = 3;
		
    }
    void Manager::updateScreenSize() {
        Screen* m_screen_pointer = NULL;


        m_screen_pointer = DefaultScreenOfDisplay( this->x_display );
        if ( !m_screen_pointer ) {
            fprintf(stderr, "Failed to obtain the default screen of given display.\n");
            return;
        }

        x_screen_size[0] = (unsigned int)m_screen_pointer->width;
        x_screen_size[1] = (unsigned int)m_screen_pointer->height;

    }

    void Manager::update() {
        int m_empty;
        unsigned int m_mask;
        XQueryPointer(this->x_display, this->x_root_window, &this->x_ret_root,
                      &this->x_ret_child, &this->x_cursor_pos[0],
                      &this->x_cursor_pos[1],&m_empty, &m_empty, &m_mask);
        printf("+%d+%d\n", this->x_cursor_pos[0], this->x_cursor_pos[1]);
        printf("+%d+%d\n", this->x_screen_size[0], this->x_screen_size[1]);
		
		// if current counter is not  equal to -1 then is active 
		if(current_corner != -1){
			this->last_active_corner = this->current_corner; 
		}
		
		// now lets get is this any of the corners
		int m_counter = 0;
		current_corner = -1;
		for(auto corner : corners){
			corner.updateState( this->x_cursor_pos[0], this->x_cursor_pos[1], detection_margin);
			if(corner.isActive())
				current_corner = m_counter;
			
			m_counter++;
		}
		if(current_corner != -1){
        	printf("Current corner is this: +%d\n", this->current_corner);
		}
	}
}