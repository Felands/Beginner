#include "SDLGameObject.h"
#include "Game.h"
#include "Resource.h"
#include "log.h"

void SDLGameObject::Load(int32_t x, int32_t y, int32_t callBackId_, int32_t animeSpeed_,
    std::vector<std::string> textureNames_)
{
    position.SetX(x);
    position.SetY(y);
    velocity.SetX(0);
    velocity.SetY(0);
    callBackId = callBackId_;
    animeSpeed = animeSpeed_;
    textureNames = textureNames_;
}

void SDLGameObject::Update()
{
    LOG_DBG("[SDLGameObject][Update] Updating the SDL game object");

    position += velocity;

    LOG_DBG("[SDLGameObject][Update] Updating the SDL game object");
}

void SDLGameObject::Draw()
{
    LOG_DBG("[SDLGameObject][Draw] Drawing the SDL game object");

    LOG_DBG("[SDLGameObject][Draw] Drew the SDL game object");
}

void SDLGameObject::Clean()
{}

void SDLGameObject::Collision()
{}
    
std::string SDLGameObject::Type()
{
    return std::string("");
}
