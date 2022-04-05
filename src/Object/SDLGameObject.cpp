#include "SDLGameObject.h"
#include "Game.h"
#include "Resource.h"

void SDLGameObject::Draw()
{
    SDL_RendererFlip flip;
    if (m_velocity.GetX() >= 0) {
        flip = SDL_FLIP_NONE;
    } else {
        flip = SDL_FLIP_HORIZONTAL;
    }
    TextureManager::Instance()->DrawFrame(m_textureID, m_position.GetX(), m_position.GetY(), m_width, m_height,
        m_currentRow, m_currentFrame, Game::Instance()->GetRenderer(), flip);
}

void SDLGameObject::Clean()
{}

void SDLGameObject::Update()
{
    m_currentFrame = uint32_t(((SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames));
    m_position += m_velocity;
}

void SDLGameObject::Load(const LoaderParams* pParams)
{
    m_position.SetX(pParams->GetX());
    m_position.SetY(pParams->GetY());
    m_velocity.SetX(0);
    m_velocity.SetY(0);
    m_width = pParams->GetWidth();
    m_height = pParams->GetHeight();
    m_currentRow = 1;
    m_currentFrame = 0;
    m_numFrames = pParams->GetNumFrames();
    m_textureID = pParams->GetTextureID();
    m_callbackID = pParams->GetCallBackID();
    m_animSpeed = pParams->GetAnimSpeed();
}
