#include <iostream>
#include <string>

#include "SDL_image.h"
#include "SDL.h"

#include "Resource.h"

TextureManager* TextureManager::s_pInstance = nullptr;

bool TextureManager::Load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
    SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
    if(pTempSurface == nullptr) {
        std::cout << "IMG load fail\n";
    } else {
        std::cout << "IMG load success\n";
        SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
        SDL_FreeSurface(pTempSurface);
        if (pTexture == nullptr) {
            std::cout << "Texture create fail\n";
        } else {
            std::cout << "Texture create success\n";
            m_textureMap[id] = pTexture;
            return true;
        }
    }
    return false;
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height,
    SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height,
    int currentRow, int currentFrame, SDL_Renderer *pRenderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = width * (currentFrame - 1);
    srcRect.y = height * (currentRow - 1);
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

TextureManager* TextureManager::Instance()
{
    if(s_pInstance == nullptr)
    {
        s_pInstance = new TextureManager();
    }
    return s_pInstance;
}