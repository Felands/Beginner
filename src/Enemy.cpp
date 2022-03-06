#include "SDL.h"

#include "Enemy.h"
#include "LoaderParams.h"
#include "SDLGameObject.h"

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{
    m_velocity.SetY(2);
    m_velocity.SetX(0.001);
}

void Enemy::Draw()
{
    SDLGameObject::Draw();
}

void Enemy::Update()
{
    m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));
    if(m_position.GetY() < 0) {
        m_velocity.SetY(2);
    } else if(m_position.GetY() > 400) {
        m_velocity.SetY(-2);
    }
    SDLGameObject::Update();
}
