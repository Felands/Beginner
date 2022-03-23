#include <stdint.h>
#include <iostream>
#include "SDL.h"

#include "Enemy.h"
#include "Resource.h"
#include "Game.h"
#include "InputHandler.h"

const char *enemies[] = {
    "wogol",
    nullptr
};

void Enemy::Load()
{
    if (m_name == "wogol") {
        m_enemyTexture[EnemyState::IDLE] = "wogol_idle_anim";
        m_enemyTexture[EnemyState::RUN] = "wogol_run_anim";
    }
}

void Enemy::Draw()
{
    SDL_RendererFlip flip;
    if (m_velocity.GetX() >= 0) {
        flip = SDL_FLIP_NONE;
    } else {
        flip = SDL_FLIP_HORIZONTAL;
    }
    TextureManager::Instance()->DrawFrame(m_enemyTexture[m_state], m_position.GetX(), m_position.GetY(),
        m_currentFrame, Game::Instance()->GetRenderer(), flip);
}

void Enemy::Update()
{
    m_currentFrame =
        int32_t(((SDL_GetTicks() / 100) % TextureManager::Instance()->GetNumFrame(m_enemyTexture[m_state]))) + 1;
    m_position += m_velocity;
    if (m_position.GetX() >300) {
        m_velocity += Vector2D(-2, 0);
    } else if (m_position.GetX() < 100) {
        m_velocity += Vector2D(2, 0);
    }
}

void Enemy::Clean()
{}

void Enemy::HandleInput()
{}
