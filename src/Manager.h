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
    class Manager {
    public:
        Manager();
        ~Manager() {};
        void configure();
        void update();

    private:
        void updateScreenSize();
        void configureCornersPos();

        Display *x_display;
        Window x_root_window;
        Window x_ret_root;
        Window x_ret_child;
        std::array<hc::Corner, 4> corners;
        std::array<unsigned int, 2> x_screen_size;
        std::array<int, 2> x_cursor_pos;
        unsigned int last_active_corner;
        unsigned int current_corner;

    };
}


#endif //X11HOTCORNER_MANAGER_H
