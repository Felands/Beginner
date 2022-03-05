#include <stdint.h>

#include "SDL.h"

#include "Player.h"
#include "LoaderParams.h"
#include "SDLGameObject.h"

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams)
{}

void Player::Update()
{
    m_currentFrame = int32_t(((SDL_GetTicks() / 100) % 8));
    m_velocity.SetX(1);
    SDLGameObject::Update();
}
