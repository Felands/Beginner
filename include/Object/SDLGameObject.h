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
    SDLGameObject(const LoaderParams* pParams);

    virtual void Draw();

    virtual void Clean();

    virtual void Update();

    Vector2D& GetPosition() { return m_position; }

    std::string GetName() { return m_textureID; }

protected:
    Vector2D m_position;
    Vector2D m_velocity;
    int m_currentFrame;
    std::string m_textureID;
};

#endif