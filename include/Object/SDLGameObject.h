#ifndef SDL_GAME_OBJECT_H
#define SDL_GAME_OBJECT_H

#include <string>

#include "GameObject.h"
#include "Vector2D.h"

class SDLGameObject : public GameObject
{
public:
    virtual void Load(int32_t x, int32_t y, std::vector<ObjectAnimeInfo> objectAnimeInfos);

    virtual void Update();

    virtual void Draw();

    virtual void Clean();

    virtual void Collision();

    virtual bool CheckCollideTile(Vector2D newPos);
    
    virtual std::string Type();

    virtual ~SDLGameObject()
    {}

    virtual int32_t GetCallbackId()
    {
        return objectAnimeInfos[0].callBackId;
    }

    virtual int32_t GetAnimeSpeed()
    {
        return objectAnimeInfos[0].animeSpeed;
    }

    virtual std::string GetTextureName()
    {
        return objectAnimeInfos[0].textureName;
    }

    Vector2D& GetPosition()
    {
        return position;
    }

    Vector2D& GetVelocity()
    {
        return velocity;
    }

protected:
    // how fast will this object fire bullets? with a counter
    int bulletFiringSpeed;
    int bulletCounter;

    // how long will the death animation takes? with a counter
    int dyingTime;
    int dyingCounter;
    // has the explosion sound played?
    bool playedDeathSound;

    SDLGameObject()
    {}

    // draw the animation for the object being destroyed
    void DoDyingAnimation();
};

#endif