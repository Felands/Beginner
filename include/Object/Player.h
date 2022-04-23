#ifndef PLAYER_H
#define PLAYER_H

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

    virtual void Draw();

    PlayerState GetState()
    {
        return state;
    }

    void HandleInput();

private:
    PlayerState state;
};

class PlayerCreator : public BaseCreator
{
    GameObject* CreateGameObject() const
    {
        return new Player();
    }
};

#endif
