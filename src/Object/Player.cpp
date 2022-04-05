#include "SDL.h"

#include "Player.h"
#include "InputHandler.h"

void Player::Update()
{
    SDLGameObject::Update();
    m_velocity /= 2;
}

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
}
