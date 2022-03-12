#include <stdint.h>

#include "Game.h"
#include "Resource.h"
#include "GameObject.h"
#include "LoaderParams.h"
#include "SDLGameObject.h"

SDLGameObject::SDLGameObject() : GameObject()
{
}
void SDLGameObject::load(const LoaderParams *pParams)
{
 m_position = Vector2D(pParams->getX(),pParams->getY());
 m_velocity = Vector2D(0,0);
 m_acceleration = Vector2D(0,0);
 m_width = pParams->getWidth();
 m_height = pParams->getHeight();
 m_textureID = pParams->getTextureID();
 m_currentRow = 1;
 m_currentFrame = 1;
 m_numFrames = pParams->getNumFrames();
}

void SDLGameObject::Draw()
{
    if(m_velocity.GetX() > 0) {
        TextureManager::Instance()->DrawFrame(m_textureID, (Uint32)m_position.GetX(),
            (Uint32)m_position.GetY(),m_width, m_height, m_currentRow, m_currentFrame,
            Game::Instance()->GetRenderer(),SDL_FLIP_HORIZONTAL);
    } else {
        TextureManager::Instance()->DrawFrame(m_textureID, (Uint32)m_position.GetX(),
            (Uint32)m_position.GetY(), m_width, m_height, m_currentRow, m_currentFrame, 
            Game::Instance()->GetRenderer());
    }
}

void SDLGameObject::Clean()
{
    delete this;
}

void SDLGameObject::Update()
{
    m_position += m_velocity;
}
