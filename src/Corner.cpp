//
// Created by piotr on 05.01.17.
//

#include "Corner.h"

namespace hc {

void  Corner::setCornerPos(const unsigned int &p_x,const  unsigned int &p_y) {
    m_posX = p_x;
    m_posY = p_y;
}

const std::string &Corner::getCommand() const {
    return m_command;
}

void Corner::setCommand(const std::string &p_command) {
    m_command = p_command;
}

void Corner::updateState(const unsigned int &p_cursorX,const unsigned int &p_cursorY, const int &p_detectionMargin) {
    m_isActive = (hc::getAbsValue(p_cursorX -  m_posX) < p_detectionMargin &&
                  hc::getAbsValue(p_cursorY -  m_posY) < p_detectionMargin);
}
}
