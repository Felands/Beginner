#include "Ui.h"
#include "Resource.h"
#include "Game.h"

void Ui::Draw()
{
    TextureManager::Instance()->DrawFrame(m_name, m_position.GetX(), m_position.GetY(),
        m_currentFrame, Game::Instance()->GetRenderer());
}

void Ui::Update()
{
    m_currentFrame =
        int32_t(((SDL_GetTicks() / 100) % TextureManager::Instance()->GetNumFrame(m_name))) + 1;
}
