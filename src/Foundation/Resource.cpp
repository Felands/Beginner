#include "SDL_image.h"

#include "Resource.h"

TextureManager *TextureManager::s_pInstance = nullptr;

TextureManager *TextureManager::Instance()
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

