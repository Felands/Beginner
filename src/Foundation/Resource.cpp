#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>

#include "SDL_image.h"
#include "SDL.h"

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
    if(s_pInstance == nullptr)
    {
        s_pInstance = new TextureManager();
    }
    return s_pInstance;
}

bool TextureManager::Load(std::string fileName, SDL_Renderer* pRenderer)
{
    std::string imageName = fileName + ".png";
    SDL_Texture* pTexture = nullptr;
    SDL_Surface* pTempSurface = IMG_Load(imageName.c_str());
    if(pTempSurface == nullptr) {
        std::cout << "IMG " << imageName << " load fail.\n";
        return false;
    } else {
        //std::cout << "IMG " << imageName << " load success.\n";
         pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
        SDL_FreeSurface(pTempSurface);
        if (pTexture == nullptr) {
            std::cout << "Texture " << imageName << " create fail\n";
            return false;
        } else {
            //std::cout << "Texture " << imageName << " create success\n";
        }
    }

    std::ifstream infoFile(fileName, std::ios_base::in);
    if (!infoFile.is_open()) {
        std::cout << "Open file " << fileName << " failed.\n";
        SDL_DestroyTexture(pTexture);
        return false;
    }

    std::string infoId;
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
    uint32_t numFrame;
    ResourceInfo *resourceInfo;
    while (infoFile >> infoId >> x >> y >> width >> height >> numFrame ) {
        resourceInfo = new ResourceInfo();
        resourceInfo->coordinate.SetX(x);
        resourceInfo->coordinate.SetY(y);
        resourceInfo->size.SetX(width);
        resourceInfo->size.SetY(height);
        resourceInfo->numFrame = numFrame;
        m_infoMap[infoId] = resourceInfo;
        SDL_DestroyTexture(m_textureMap[infoId]);
        m_textureMap[infoId] = pTexture;
        //std::cout << infoId << std::endl;
    }

    return true;
}

void TextureManager::LoadAllResource()
{
    for (int i = 0; tilesetPath[i] != nullptr; ++i) {
        Load(tilesetPath[i], Game::Instance()->GetRenderer());
    }
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height,
    SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
    if (m_infoMap.count(id) < 1 || m_textureMap.count(id) < 1) {
        std::cout << id << "is incorrect.\n";
    }
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int currentFrame, SDL_Renderer *pRenderer,
    SDL_RendererFlip flip)
{
    if (m_infoMap.count(id) < 1 || m_textureMap.count(id) < 1) {
        std::cout << id << "is incorrect.\n";
    }
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = m_infoMap[id]->coordinate.GetX() + m_infoMap[id]->size.GetX() * (currentFrame - 1);
    srcRect.y = m_infoMap[id]->coordinate.GetY();
    srcRect.w = destRect.w = m_infoMap[id]->size.GetX();
    srcRect.h = destRect.h = m_infoMap[id]->size.GetY();
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::ClearFromTextureMap(std::string id)
{
    m_textureMap.erase(id);
}
