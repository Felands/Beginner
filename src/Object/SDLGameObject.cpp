#include <stdint.h>

#include "Game.h"
#include "Resource.h"
#include "GameObject.h"
#include "LoaderParams.h"
#include "SDLGameObject.h"

void SDLGameObject::Load(const LoaderParams* pParams)
{
    m_position.SetX(pParams->GetX());
    m_position.SetY(pParams->GetY());
    m_velocity.SetX(0);
    m_velocity.SetY(0);
    m_currentFrame = 1;
    m_textureID = pParams->GetTextureID();
    callbackID = pParams->GetCallBackID();
    animSpeed = pParams->GetAnimSpeed();
}

void SDLGameObject::Draw()
{
    TextureManager::Instance()->DrawFrame(m_textureID, (Uint32)m_position.GetX(),
        (Uint32)m_position.GetY(), m_currentFrame, Game::Instance()->GetRenderer());
}

void SDLGameObject::Clean()
{
    delete this;
}

void SDLGameObject::Update()
{
    m_position += m_velocity;
}
