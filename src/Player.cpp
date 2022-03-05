#include "SDL.h"

#include "LoaderParams.h"
#include "SDLGameObject.h"
#include "Player.h"

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams)
{}

void Player::update()
{
    m_currentFrame = int(((SDL_GetTicks() / 100) % 8));
    m_velocity.setX(1);
    SDLGameObject::Update();
}
