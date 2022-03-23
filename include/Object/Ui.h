#ifndef _UI_H_
#define _UI_H_

#include <string>

#include "Vector2D.h"

class Ui
{
public:
    Ui(std::string name) :
        m_position(100, 100), m_name(name)
    {}

    void Draw();

    void Update();

private:
    Vector2D m_position;
    std::string m_name;
    uint32_t m_currentFrame;
};

#endif