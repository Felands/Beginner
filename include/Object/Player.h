#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

enum class PlayerState
{
    IDLE,
    RUN,
    HIT
};

class Player : public SDLGameObject
{
public:
    virtual void Update();

    virtual void HandleInput();

    PlayerState GetState()
    {
        return m_state;
    }

private:
    PlayerState m_state;
};

class PlayerCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new Player();
    }
};

#endif
