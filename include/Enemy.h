#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <memory>

#include "LoaderParams.h"
#include "SDLGameObject.h"

class Enemy : public SDLGameObject
{
public:
    Enemy();

    virtual void Load(std::unique_ptr<LoaderParams> pParams);

    virtual void Draw();

    virtual void Update();

    virtual std::string Type();
};

/*class Enemy : public ShooterObject
{
public:
 virtual std::string type() { return"Enemy"; }
protected:
 int m_health;
 Enemy() : ShooterObject() {}
 virtual ~Enemy() {} // for polymorphism
};*/

#endif