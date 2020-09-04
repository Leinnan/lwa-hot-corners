//
// Created by piotr on 05.01.17.
//

#ifndef X11HOTCORNER_CORNER_H
#define X11HOTCORNER_CORNER_H

#include <string>
namespace hc {

inline int getAbsValue(int p_value) {
    return p_value < 0 ? -p_value : p_value;
}

class Corner {
public:
    void setCornerPos(const unsigned int &p_x,const unsigned int &p_y);
    const std::string &getCommand() const;
    bool isActive() {
        return m_isActive;
    };
    bool hasCommand() const {
        return m_hasCommand;
    };
    void updateState(const unsigned int &cursor_x,const unsigned int &cursor_y, const int &p_detection_margin);
    void setCommand(const std::string &p_command);

private:
    std::string m_command = "";
    unsigned int m_posX;
    unsigned int m_posY;
    bool m_isActive;
    bool m_hasCommand = false;
};

}

#endif //X11HOTCORNER_CORNER_H
