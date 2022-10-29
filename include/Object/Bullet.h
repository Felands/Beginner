#ifndef BULLET_H
#define BULLET_H

#include <stdint.h>
#include <string>

#include "SDLGameObject.h"
#include "Vector2D.h"

class PlayerBullet : public SDLGameObject
{
public:
    PlayerBullet() : SDLGameObject() {}

    virtual ~PlayerBullet() {}

    virtual std::string Type() { return "PlayerBullet"; }

    virtual void Load(int32_t x, int32_t y, int32_t callBackId, int32_t animeSpeed,
        std::vector<std::string> textureNames, Vector2D heading)
    {
        SDLGameObject::Load(x, y, callBackId, animeSpeed, textureNames);
        this->heading = heading;
    }

    virtual void Draw()
    {
        SDLGameObject::Draw();
    }

    virtual void Collision()
    {
        dead = true;
    }

    virtual void update()
    {
        velocity.SetX(heading.GetX());
        velocity.SetY(heading.GetY());
        SDLGameObject::Update();
    }

    virtual void Clean()
    {
        SDLGameObject::Clean();
    }

private:
    Vector2D heading;
};

// Enemy Bullet is just a Player Bullet with a different typename
class EnemyBullet : public PlayerBullet
{
public:
    EnemyBullet() : PlayerBullet() {}
    virtual ~EnemyBullet() {}
    virtual std::string Type() { return "EnemyBullet"; }
};

#endif
