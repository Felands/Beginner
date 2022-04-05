#include <iostream>

#include "SDL_image.h"

#include "Resource.h"
#include "Game.h"

const char *tilesetPath[] = {
    "./assets/drawable/0x72_DungeonTilesetII_v1_3",
    "./assets/drawable/fireball_explosion1",
    "./assets/drawable/halo_explosion1",
    "./assets/drawable/halo_explosion2",
    "./assets/drawable/fireball",
    "./assets/drawable/floor_spike",
    "./assets/drawable/floor_exit",
    "./assets/drawable/HpMed",
    "./assets/drawable/SwordFx",
    "./assets/drawable/ClawFx",
    "./assets/drawable/Shine",
    "./assets/drawable/Thunder",
    "./assets/drawable/BloodBound",
    "./assets/drawable/arrow",
    "./assets/drawable/explosion-2",
    "./assets/drawable/ClawFx2",
    "./assets/drawable/Axe",
    "./assets/drawable/cross_hit",
    "./assets/drawable/blood",
    "./assets/drawable/SolidFx",
    "./assets/drawable/IcePick",
    "./assets/drawable/IceShatter",
    "./assets/drawable/Ice",
    "./assets/drawable/SwordPack",
    "./assets/drawable/HolyShield",
    "./assets/drawable/golden_cross_hit",
    "./assets/drawable/ui",
    "./assets/drawable/title",
    "./assets/drawable/purple_ball",
    "./assets/drawable/purple_exp",
    "./assets/drawable/staff",
    "./assets/drawable/Thunder_Yellow",
    "./assets/drawable/attack_up",
    "./assets/drawable/powerful_bow",
    "./assets/drawable/button/login_button/login_button",
    "./assets/drawable/button/exit_button/exit_button",
    nullptr
};

TextureManager* TextureManager::s_pInstance = nullptr;

TextureManager* TextureManager::Instance()
{
    if(s_pInstance == nullptr) {
        s_pInstance = new TextureManager();
    }
    return s_pInstance;
}

void TextureManager::Clean()
{
	if (s_pInstance != nullptr) {
        for (auto it : m_textureMap) {
			SDL_DestroyTexture(it.second);
		}
		delete s_pInstance;
	} 
}

bool TextureManager::Load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
    SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
    if(pTempSurface == nullptr) {
        return false;
    }
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
    SDL_FreeSurface(pTempSurface);
    if(pTexture != nullptr) {
        m_textureMap[id] = pTexture;
        return true;
    }
    return false;
}

void TextureManager::DrawFrame(std::string id, int32_t x, int32_t y, uint32_t width, uint32_t height, uint32_t currentRow,
    uint32_t currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = width * currentFrame;
    srcRect.y = height * (currentRow - 1);
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::ClearFromTextureMap(std::string id)
{
    SDL_DestroyTexture(m_textureMap[id]);
    m_textureMap.erase(id);
}

void TextureManager::DrawTile(std::string id, int32_t margin, int32_t spacing, int32_t x, int32_t y, int32_t width, int32_t height,
    int32_t currentRow, int32_t currentFrame, SDL_Renderer *pRenderer)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = margin + (spacing + width) * currentFrame;
    srcRect.y = margin + (spacing + height) * currentRow;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect,&destRect, 0, 0, SDL_FLIP_NONE);
}

