#include <iostream>
#include <string>

#include "SDL.h"
#include "SDL_image.h"

#include "TextureManager.h"

TextureManager* TextureManager::s_pInstance = nullptr;

TextureManager* TextureManager::Instance()
{
    if(s_pInstance == nullptr) {
        s_pInstance = new TextureManager();
    }
    return s_pInstance;
}

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
            SDL_DestroyTexture(m_textureMap[id]);
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

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height,int currentRow, int currentFrame,
    SDL_Renderer *pRenderer, double angle, int alpha, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = width * (currentFrame - 1);
    srcRect.y = height * (currentRow - 1);
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;

    // set the alpha of the texture and pass in the angle
    SDL_SetTextureAlphaMod(m_textureMap[id], alpha);
    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, angle, 0, flip);
}

void TextureManager::Clean()
{
    if (s_pInstance != nullptr) {
        for (std::unordered_map<std::string, SDL_Texture*>::iterator it = m_textureMap.begin();
            it != m_textureMap.end(); ++it) {
            SDL_DestroyTexture(it->second);
        }
        delete s_pInstance;
    } 
}

void TextureManager::ClearFromTextureMap(std::string id)
{
    SDL_DestroyTexture(m_textureMap[id]);
    m_textureMap.erase(id);
}

/*void TextureManager::drawTile(std::string id, int margin, int 
 spacing, int x, int y, int width, int height, int currentRow, 
 int currentFrame, SDL_Renderer *pRenderer)
{
 SDL_Rect srcRect;
 SDL_Rect destRect;
 srcRect.x = margin + (spacing + width) * currentFrame;
 srcRect.y = margin + (spacing + height) * currentRow;
 srcRect.w = destRect.w = width;
 srcRect.h = destRect.h = height;
 destRect.x = x;
 destRect.y = y;
 SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect,
 &destRect, 0, 0, SDL_FLIP_NONE);
}*/
