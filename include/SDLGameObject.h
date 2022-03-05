#ifndef _SDL_GAME_OBJECT_H_
#define _SDL_GAME_OBJECT_H_

#include <string>

#include "GameObject.h"
#include "Vector2D.h"

class SDLGameObject : public GameObject
{
public:
    SDLGameObject(const LoaderParams* pParams);

    virtual void Draw();

    virtual void Clean();

    virtual void Update();

protected:
    Vector2D m_position;
    Vector2D m_velocity;
    int m_width;
    int m_height;
    int m_currentRow;
    int m_currentFrame;
    std::string m_textureID;
};

#endif