#ifndef _SDL_GAME_OBJECT_H_
#define _SDL_GAME_OBJECT_H_

#include <string>
#include <stdint.h>

#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "GameObject.h"
#include "Vector2D.h"

class SDLGameObject : public GameObject
{
public:
    SDLGameObject()
    {}

    virtual void Draw();

    virtual void Clean();

    virtual void Update();

    virtual void Load(const LoaderParams* pParams);

    Vector2D& GetPosition() { return m_position; }

    std::string GetName() { return m_textureID; }

protected:
    Vector2D m_position;
    Vector2D m_velocity;
    int m_currentFrame;
    int32_t callbackID;
    int32_t animSpeed;
    std::string m_textureID;
};

#endif