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
    }
}