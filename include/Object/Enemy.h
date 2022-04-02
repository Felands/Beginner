#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "LoaderParams.h"
#include "SDLGameObject.h"

class Enemy : public SDLGameObject
{
public:
    Enemy();

    virtual void Update();

    virtual void Draw();
};

#endif