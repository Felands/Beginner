#include <stdint.h>
#include <iostream>

#include "SDL.h"

#include "SpecialEffect.h"
#include "Resource.h"
#include "Game.h"

void SpecialEffect::SetPosition(Vector2D position)
{
    m_position = position;
}

bool SpecialEffect::IsInvalidate()
{
    if (SDL_GetTicks() - m_startTime > m_duration) {
        return true;
    }

    return false;
}

void SpecialEffect::Load()
{}

void SpecialEffect::Draw()
{
    TextureManager::Instance()->DrawFrame(m_name, m_position.GetX(), m_position.GetY(),
        m_currentFrame, Game::Instance()->GetRenderer());
}

void SpecialEffect::Update()
{
    m_currentFrame =
        int32_t(((SDL_GetTicks() / 100) % TextureManager::Instance()->GetNumFrame(m_name))) + 1;
}

void SpecialEffect::Clean()
{}

void SpecialEffect::HandleInput()
{}
