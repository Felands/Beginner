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

    virtual int32_t GetCallbackId()
    {
        return objectAnimeInfos[(size_t)state].callBackId;
    }

    virtual int32_t GetAnimeSpeed()
    {
        return objectAnimeInfos[(size_t)state].animeSpeed;
    }

    virtual std::string GetTextureName()
    {
        return objectAnimeInfos[(size_t)state].textureName;
    }

    virtual std::string Type()
    {
        return std::string("Player");
    }

    PlayerState GetState()
    {
        return state;
    }

private:
    PlayerState state;
    // player can be invulnerable for a time
    bool invulnerable;
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
