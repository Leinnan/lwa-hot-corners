//
// Created by piotr on 05.01.17.
//

#include "Corner.h"

namespace hc{
    Corner::Corner() {}

    void  Corner::setCornerPos(const unsigned int &p_x,const  unsigned int &p_y){
        this->pos_x = p_x;
        this->pos_y = p_y;
    }

    const std::string &Corner::getCommand() const {
        return command;
    }

    void Corner::setCommand(const std::string &p_command) {
        Corner::command = p_command;
    }
}