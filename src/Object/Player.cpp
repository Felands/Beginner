#include <stdint.h>

#include "SDL.h"

#include "Player.h"
#include "LoaderParams.h"
#include "SDLGameObject.h"
#include "Vector2D.h"
#include "InputHandler.h"

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams)
{}

void Player::Update()
{
    m_currentFrame = int32_t(((SDL_GetTicks() / 100) % m_numFrames));
    SDLGameObject::Update();
}

void Player::HandleInput()
{
    /*Vector2D* target = InputHandler::Instance()->GetMousePosition();
    m_velocity = *target - m_position;
    m_velocity /= 50;*/
}
