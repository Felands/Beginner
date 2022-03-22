#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <string>
#include <stdint.h>

#include "Vector2D.h"

class GameObject
{
public:
    GameObject(Vector2D position, Vector2D velocity, std::string name) :
        m_position(position), m_velocity(velocity), m_currentFrame(1), m_name(name)
    {}

    virtual void Load() = 0;

    virtual void Draw() = 0;

    virtual void Update() = 0;

    virtual void Clean() = 0;

    virtual void HandleInput() = 0;

    Vector2D& GetPosition()
    {
        return m_position;
    }

protected:
    Vector2D m_position;
    Vector2D m_velocity;
    uint32_t m_currentFrame;
    std::string m_name;
};

#endif