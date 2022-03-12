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
    SDLGameObject();

    virtual void Draw();

    virtual void Clean();

    virtual void Update();

    Vector2D& GetPosition() { return m_position; }

    int32_t GetWidth()
    {
        return m_width;
    }

    int32_t GetHeight()
    {
        return m_height;
    }

    virtual void SDLGameObject::load(const LoaderParams *pParams);

protected:
    Vector2D m_position;
    Vector2D m_velocity;
    int m_width;
    int m_height;
    int m_currentRow;
    int m_currentFrame;
    int32_t m_numFrames;
    std::string m_textureID;
};

#endif