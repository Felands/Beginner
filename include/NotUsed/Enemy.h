#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "LoaderParams.h"
#include "SDLGameObject.h"

class Enemy : public SDLGameObject
{
public:
    Enemy(const LoaderParams* pParams);

    virtual void Update();

    virtual void Draw();
};

class Enemy : public ShooterObject
{
public:
 virtual std::string type() { return"Enemy"; }
protected:
 int m_health;
 Enemy() : ShooterObject() {}
 virtual ~Enemy() {} // for polymorphism
};

#endif