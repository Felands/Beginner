#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "LoaderParams.h"
#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class Enemy : public SDLGameObject
{
public:
    Enemy();

    virtual void Update();

    virtual void Draw();
};

class EnemyCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new Enemy();
    }
};

#endif