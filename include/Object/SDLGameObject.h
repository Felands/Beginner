#ifndef SDL_GAME_OBJECT_H
#define SDL_GAME_OBJECT_H

#include <string>

#include "GameObject.h"
#include "Vector2D.h"

class SDLGameObject : public GameObject
{
public:
    virtual void Load(int32_t x, int32_t y, int32_t callBackId, int32_t animeSpeed,
        std::vector<std::string> textureNames);

    virtual void Update();

    virtual void Draw();

    virtual void Clean();

    Vector2D& GetPosition()
    {
        return position;
    }

    Vector2D& GetVelocity()
    {
        return velocity;
    }

    std::vector<std::string> *GetTextureNames()
    {
        return &textureNames;
    }

    int32_t GetCallbackId()
    {
        return callBackId;
    }

protected:
    Vector2D position;
    Vector2D velocity;
    int32_t callBackId;
    int32_t animeSpeed;
    std::vector<std::string> textureNames;
};

#endif