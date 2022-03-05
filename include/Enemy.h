#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "LoaderParams.h"
#include "SDLGameObject.h"

class Enemy : public SDLGameObject
{
public:
    Enemy(const LoaderParams* pParams);

    virtual void Update();
};

#endif