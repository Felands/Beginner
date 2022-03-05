#include "Game.h"
#include "Resource.h"
#include "GameObject.h"
#include "LoaderParams.h"
#include "SDLGameObject.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams) :
GameObject(pParams), m_position(pParams->getX(), pParams->getY()), m_velocity(0,0)
{  
    m_width = pParams->GetWidth();
    m_height = pParams->GetHeight();
    m_textureID = pParams->GetTextureID();
    m_currentRow = 1;
    m_currentFrame = 1;

    delete pParams;
}

void SDLGameObject::Draw()
{
    TextureManager::Instance()->DrawFrame(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height,
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