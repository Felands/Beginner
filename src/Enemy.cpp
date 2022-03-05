#include "SDL.h"

#include "LoaderParams.h"
#include "SDLGameObject.h"
#include "Enemy.h"

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{}

void Enemy::Update()
{
    m_position.setX(m_position.getX() + 1);
    m_position.setY(m_position.getY() + 1);
}