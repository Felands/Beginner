#include <stdint.h>

#include "Game.h"
#include "Resource.h"
#include "GameObject.h"
#include "LoaderParams.h"
#include "SDLGameObject.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams) :
    GameObject(pParams), m_position(pParams->GetX(), pParams->GetY()), m_velocity(0,0),
    m_width(pParams->GetWidth()), m_height(pParams->GetHeight()), m_currentRow(1), m_currentFrame(1),
    m_textureID(pParams->GetTextureID())
{}

void SDLGameObject::Draw()
{
    TextureManager::Instance()->DrawFrame(m_textureID, (int32_t)m_position.GetX(), (int32_t)m_position.GetY(), m_width, m_height,
        m_currentRow, m_currentFrame, Game::Instance()->GetRenderer());
}

void SDLGameObject::Clean()
{
    delete this;
}

void SDLGameObject::Update()
{
    m_position += m_velocity;
}