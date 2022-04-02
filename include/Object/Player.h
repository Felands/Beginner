#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "GameObjectFactory.h"

class Player : public SDLGameObject
{
public:
    virtual void Update();

    virtual void HandleInput();
};

class PlayerCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new Player();
    }
};

#endif