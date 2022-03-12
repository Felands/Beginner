#include <stdint.h>

#include "SDL.h"

#include "AnimatedGraphic.h"
#include "LoaderParams.h"
#include "SDLGameObject.h"

AnimatedGraphic::AnimatedGraphic(const LoaderParams* pParams, int32_t animSpeed) :
    SDLGameObject(pParams), m_animSpeed(animSpeed)
{}

void AnimatedGraphic::Update()
{
    m_currentFrame = int32_t(((SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames));
}

void AnimatedGraphic::load(const LoaderParams *pParams)
{
 SDLGameObject::load(pParams);
 m_animSpeed = pParams->getAnimSpeed();
}