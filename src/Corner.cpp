//
// Created by piotr on 05.01.17.
//

#include "Corner.h"

namespace hc{

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
	void Corner::updateState(const unsigned int &p_cursor_x,const unsigned int &p_cursor_y, const int &p_detection_margin){
		if(hc::getAbsValue(p_cursor_x -  this->pos_x) < p_detection_margin && 
		   hc::getAbsValue(p_cursor_y -  this->pos_y) < p_detection_margin){
				this->is_active = true;
		}
		else{
				this->is_active = false;
		}
	}
}
