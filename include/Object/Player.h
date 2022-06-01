#ifndef PLAYER_H
#define PLAYER_H

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

enum class PlayerState
{
    IDLE,
    RUN,
    HIT,
    DYING,
    MAX
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

private:
    PlayerState state;
    // player can be invulnerable for a time
    int32_t invulnerable;
    int32_t invulnerableTime;
    int32_t invulnerableCounter;

    // bring the player back if there are lives left
    void Ressurect();
    // handle any input from the keyboard, mouse, or joystick
    void HandleInput();
    // handle any animation for the player
    void HandleAnimation();
};

class PlayerCreator : public BaseCreator
{
    GameObject* CreateGameObject() const
    {
        return new Player();
    }
};

#endif
