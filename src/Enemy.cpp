#include "SDL.h"

#include "Enemy.h"
#include "LoaderParams.h"
#include "SDLGameObject.h"

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{}

void Enemy::Update()
{
    m_position.SetX(m_position.GetX() + 1);
    m_position.SetY(m_position.GetY() + 1);
}