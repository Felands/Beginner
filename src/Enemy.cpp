#include <stdint.h>

#include "SDL.h"

#include "Enemy.h"

Enemy::Enemy() : SDLGameObject()
{
    m_velocity.SetY(2);
    m_velocity.SetX(0.001);
}

void Enemy::Load(std::unique_ptr<LoaderParams> pParams)
{
    SDLGameObject::Load(std::move(pParams));
}

void Enemy::Draw()
{
    SDLGameObject::Draw();
}

void Enemy::Update()
{
    m_currentFrame = uint32_t(((SDL_GetTicks() / 100) % m_numFrames) + 1);
    if(m_position.GetY() < 0) {
        m_velocity.SetY(2);
    } else if(m_position.GetY() > 400) {
        m_velocity.SetY(-2);
    }
    SDLGameObject::Update();
}

std::string Type()
{
    return "Enemy";
}
