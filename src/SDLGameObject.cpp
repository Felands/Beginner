#include <stdint.h>

#include "SDLGameObject.h"
#include "Game.h"
#include "TextureManager.h"

SDLGameObject::SDLGameObject() : GameObject()
{}

void SDLGameObject::Load(std::unique_ptr<LoaderParams> pParams)
{
    m_position = Vector2D(pParams->GetX(), pParams->GetY());
    m_width = pParams->GetWidth();
    m_height = pParams->GetHeight();
    m_textureID = pParams->GetTextureID();
    m_numFrames = pParams->GetNumFrames();
}

void SDLGameObject::Draw()
{
    if(m_velocity.GetX() > 0) {
        TextureManager::Instance()->DrawFrame(m_textureID, m_position.GetX(), m_position.GetY(), m_width, m_height,
            m_currentRow, m_currentFrame, Game::Instance()->GetRenderer(), m_angle, m_alpha, SDL_FLIP_HORIZONTAL);
    } else {
        TextureManager::Instance()->DrawFrame(m_textureID, m_position.GetX(), m_position.GetY(), m_width, m_height,
            m_currentRow, m_currentFrame, Game::Instance()->GetRenderer(), m_angle, m_alpha);
    }
}

void SDLGameObject::Update()
{
    m_position += m_velocity;
    m_velocity += m_acceleration;
}

void SDLGameObject::Clean()
{
    delete this;
}

void Collision()
{}
