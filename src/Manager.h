 //
// Created by piotr on 05.01.17.
//

#ifndef X11HOTCORNER_MANAGER_H
#define X11HOTCORNER_MANAGER_H

#include <X11/Xlib.h>
#include <array>
#include <stdlib.h>
#include <stdio.h>
#include "Corner.h"

 namespace hc {
     
     const double TIME_DURATION = 2.0; 
     
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

    private:
        void                        updateScreenSize();
        void                        configureCornersPos();
        void                        changeState( const State &newState );

        Display                    *x_display;
        Window                      x_root_window;
        Window                      x_ret_root;
        Window                      x_ret_child;
        std::array<hc::Corner, 4>   corners;
        std::array<unsigned int, 2> x_screen_size;
        std::array<int, 2>          x_cursor_pos;
        int                         last_active_corner;
        int                         current_corner;
		unsigned int                detection_margin;
        State                       currentState;
        double                      timeCounter;
    };
}


#endif //X11HOTCORNER_MANAGER_H
