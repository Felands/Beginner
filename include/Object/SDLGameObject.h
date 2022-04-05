#ifndef _SDL_GAME_OBJECT_H_
#define _SDL_GAME_OBJECT_H_

#include <string>

#include "GameObject.h"
#include "Vector2D.h"

class SDLGameObject : public GameObject
{
public:
    virtual void Draw();

    virtual void Clean();

    virtual void Update();

    virtual void Load(const LoaderParams* pParams);

    Vector2D& GetPosition()
    {
        return m_position;
    }

    Vector2D& GetVelocity()
    {
        return m_velocity;
    }

    uint32_t GetWidth()
    {
        return m_width;
    }

    uint32_t GetHeight()
    {
        return m_height;
    }

    uint32_t GetCurrentRow()
    {
        return m_currentRow;
    }

    uint32_t GetCurrentFrame()
    {
        return m_currentFrame;
    }

    int32_t GetCallbackID()
    {
        return m_callbackID;
    }

    int32_t GetAnimSpeed()
    {
        return m_animSpeed;
    }

    std::string GetTextureID()
    {
        return m_textureID;
    }

protected:
    Vector2D m_position;
    Vector2D m_velocity;
    uint32_t m_width;
    uint32_t m_height;
    uint32_t m_currentRow;
    uint32_t m_currentFrame;
    uint32_t m_numFrames;
    int32_t m_callbackID;
    int32_t m_animSpeed;
    std::string m_textureID;
};

#endif