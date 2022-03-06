#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "SDLGameObject.h"
#include "LoaderParams.h"

class Player : public SDLGameObject
{
public:
    Player(const LoaderParams* pParams);

    virtual void Update();

    virtual void HandleInput();
};

#endif