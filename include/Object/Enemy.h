#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class Enemy : public SDLGameObject
{};

class EnemyCreator : public BaseCreator
{
    GameObject* CreateGameObject() const
    {
        return new Enemy();
    }
};

#endif