//
// Created by piotr on 05.01.17.
//

#ifndef X11HOTCORNER_CORNER_H
#define X11HOTCORNER_CORNER_H

#include <string>
#include <array>
namespace hc {
    class Corner {
    public:
        Corner();
        ~Corner(){};
        void setCornerPos(const unsigned int &p_x,const unsigned int &p_y);

        const std::string &getCommand() const;

        void setCommand(const std::string &p_command);

    private:
        std::string command;
        unsigned int pos_x;
        unsigned int pos_y;
        bool is_active;
    };

}

#endif //X11HOTCORNER_CORNER_H
