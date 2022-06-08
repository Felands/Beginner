#include "ScrollingBackground.h"
#include "SDL.h"
#include "SDLGameObject.h"

void ScrollingBackground::Load(std::unique_ptr<LoaderParams> const &pParams)
{
    SDLGameObject::Load(std::move(pParams));
    scrollSpeed = pParams->getAnimSpeed();
    scrollSpeed = 1;
    srcRect1.x = 0;
    destRect1.x = position.getX();
    srcRect1.y = 0;
    destRect1.y = position.getY();
    srcRect1.w = destRect1.w = srcRect2Width = 
    destRect1Width = width;
    srcRect1.h = destRect1.h = height;
    srcRect2.x = 0;
    destRect2.x = position.getX() + width;
    srcRect2.y = 0;
    destRect2.y = position.getY();
    srcRect2.w = destRect2.w = srcRect2Width = 
    destRect2Width = 0;
    srcRect2.h = destRect2.h = height;
}

void ScrollingBackground::Draw()
{
    // draw first rect
    SDL_RenderCopyEx(TheGame::Instance()->getRenderer(), 
    TheTextureManager::Instance()->getTextureMap()[textureID], 
    &srcRect1, &destRect1, 0, 0, SDL_FLIP_NONE);
    // draw second rect
    SDL_RenderCopyEx(TheGame::Instance()->getRenderer(), 
    TheTextureManager::Instance()->getTextureMap()[textureID], 
    &srcRect2, &destRect2, 0, 0, SDL_FLIP_NONE);
}

void ScrollingBackground::Update()
{
    if (count == maxcount) {
        // make first rectangle smaller
        srcRect1.x += scrollSpeed;
        srcRect1.w -= scrollSpeed;
        destRect1.w -= scrollSpeed;

        // make second rectangle bigger
        srcRect2.w += scrollSpeed;
        destRect2.w += scrollSpeed;
        destRect2.x -= scrollSpeed;

        // reset and start again
        if (destRect2.w >= width) {
            srcRect1.x = 0;
            destRect1.x = position.getX();
            srcRect1.y = 0;
            destRect1.y = position.getY();
            srcRect1.w = destRect1.w = srcRect2Width = 
            destRect1Width = width;
            srcRect1.h = destRect1.h = height;
            srcRect2.x = 0;
            destRect2.x = position.getX() + width;
            srcRect2.y = 0;
            destRect2.y = position.getY();
            srcRect2.w = destRect2.w = srcRect2Width = 
            destRect2Width = 0;
            srcRect2.h = destRect2.h = height;
        }
        count = 0;
    }
    count++;
}