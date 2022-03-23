#include <stdint.h>
#include <iostream>

#include "SDL.h"

#include "Player.h"
#include "Resource.h"
#include "Game.h"
#include "InputHandler.h"

const char *players[] = {
    "elf_f",
    nullptr
};

void Player::Load()
{
    if (m_name == "elf_f") {
        m_playerTexture[PlayerState::IDLE] = "elf_f_idle_anim";
        m_playerTexture[PlayerState::RUN] = "elf_f_run_anim";
        m_playerTexture[PlayerState::HIT] = "elf_f_hit_anim";
    }
}

void Player::Draw()
{
    SDL_RendererFlip flip;
    if (m_velocity.GetX() >= 0) {
        flip = SDL_FLIP_NONE;
    } else {
        flip = SDL_FLIP_HORIZONTAL;
    }
    TextureManager::Instance()->DrawFrame(m_playerTexture[m_state], m_position.GetX(), m_position.GetY(),
        m_currentFrame, Game::Instance()->GetRenderer(), flip);
    for (auto it = m_specialEffects.begin(); it != m_specialEffects.end(); ++it) {
        (*it)->Draw();
    }
}

void Player::Update()
{
    m_currentFrame =
        int32_t(((SDL_GetTicks() / 100) % TextureManager::Instance()->GetNumFrame(m_playerTexture[m_state]))) + 1;
    m_position += m_velocity;
    m_velocity /= 2;
    /*for (auto it = m_specialEffects.begin(); it != m_specialEffects.end(); ++it) {
        if ((*it)->IsInvalidate()) {
            delete *it;
            m_specialEffects.erase(it);
        }
    }*/ 
    for (auto it = m_specialEffects.begin(); it != m_specialEffects.end(); ++it) {
        (*it)->SetPosition(m_position);
        (*it)->Update();
    }
}

void Player::Clean()
{}

void Player::HandleInput()
{
    bool wDown = InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_W);
    bool sDown = InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_S);
    bool aDown = InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_A);
    bool dDown = InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_D);
    if (wDown) {
        m_position += Vector2D(0, -1);
        m_velocity += Vector2D(0, -0.1);
        m_state = PlayerState::RUN;
    }
    if (sDown) {
        m_position += Vector2D(0, 1);
        m_velocity += Vector2D(0, 0.1);
        m_state = PlayerState::RUN;
    }
    if (aDown) {
        m_position += Vector2D(-1, 0);
        m_velocity += Vector2D(-0.1, 0);
        m_state = PlayerState::RUN;
    }
    if (dDown) {
        m_position += Vector2D(1, 0);
        m_velocity += Vector2D(0.1, 0);
        m_state = PlayerState::RUN;
    }
    if (!(wDown || sDown || aDown || dDown) && m_velocity.Length() < 1.0e-4) {
        m_state = PlayerState::IDLE;
    }

    if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_J)) {
        m_state = PlayerState::HIT;
    } else {
        m_state = PlayerState::IDLE;
    }

    if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_U)) {
        if (m_specialEffects.empty()) {
            m_specialEffects.push_back(new SpecialEffect("BloodBound"));
        }
    }
}
