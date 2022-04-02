#include <stdint.h>

#include "SDL.h"

#include "Player.h"
#include "LoaderParams.h"
#include "SDLGameObject.h"
#include "Vector2D.h"
#include "InputHandler.h"
#include "Resource.h"

void Player::Update()
{
    m_currentFrame = int32_t(((SDL_GetTicks() / 100) % TextureManager::Instance()->GetInfoMap(m_textureID)->numFrame));
    SDLGameObject::Update();
}

void Player::HandleInput()
{
    /*Vector2D* target = InputHandler::Instance()->GetMousePosition();
    m_velocity = *target - m_position;
    m_velocity /= 50;*/
}
