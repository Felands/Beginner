#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class Enemy : public SDLGameObject
{
public:
    virtual std::string type()
    {
        return"Enemy";
    }

    Enemy() : SDLGameObject() {}

    virtual ~Enemy() {}

protected:
    int32_t health;
};

class EnemyCreator : public BaseCreator
{
    GameObject* CreateGameObject() const
    {
        return new Enemy();
    }
};

#endif