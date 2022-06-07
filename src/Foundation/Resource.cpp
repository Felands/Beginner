#include "SDL_image.h"

#include "Resource.h"

#include "log.h"

TextureManager *TextureManager::instance = nullptr;

bool TextureManager::Load(std::string fileName, std::string name, uint32_t width, uint32_t height,
    uint32_t numColumns, uint32_t numRows, SDL_Renderer *renderer)
{
    LOG_DBG("[TextureManager][Load] Loading ", name, " from ", fileName);

    SDL_Surface *surface = IMG_Load(fileName.c_str());
    if(surface == nullptr) {
        LOG_ERR("[TextureManager][Load] Failed to load the surface, because: ", IMG_GetError());
        return false;
    } else {
        LOG_DBG("[TextureManager][Load] Succeed to load the surface");
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if(texture == nullptr) {
        LOG_ERR("[TextureManager][Load] Failed to load the texture, because: ", SDL_GetError());
        return false;
    } else {
        LOG_DBG("[TextureManager][Load] Succeed to load the texture");
    }

    TextureInfo textureInfo = {
        .width = width,
        .height = height,
        .numColumns = numColumns,
        .numRows = numRows,
        .texture = texture,
    };
    textureMap[name] = textureInfo;

    LOG_DBG("[TextureManager][Load] Loaded ", name, " from ", fileName);
    return true;
}

void TextureManager::Draw(std::string name, int32_t xPos, int32_t yPos,uint32_t currentColumn,
    uint32_t currentRow, SDL_Renderer *renderer, SDL_RendererFlip flip, uint32_t alpha)
{
    LOG_DBG("[TextureManager][DrawFrame] Drawing the frame of ", name);

    currentColumn %= textureMap[name].numColumns;
    currentRow %= textureMap[name].numRows;

    SDL_Rect srcRect;
    srcRect.x = textureMap[name].width * currentColumn;
    srcRect.y = textureMap[name].width * currentRow;
    srcRect.w = textureMap[name].width;
    srcRect.h = textureMap[name].height;

    SDL_Rect destRect;
    destRect.x = xPos;
    destRect.y = yPos;
    destRect.w = textureMap[name].width;
    destRect.h = textureMap[name].height;
    SDL_SetTextureAlphaMod(textureMap[name].texture, alpha);
    SDL_RenderCopyEx(renderer, textureMap[name].texture, &srcRect, &destRect, 0, 0, flip);

    LOG_DBG("[TextureManager][DrawFrame] Drew the frame of ", name);
}

void TextureManager::ClearFromTextureMap(std::string name)
{
    SDL_DestroyTexture(textureMap[name].texture);
    textureMap.erase(name);
}

void TextureManager::Clean()
{
    if (instance != nullptr) {
        for (auto &it : textureMap) {
            SDL_DestroyTexture(it.second.texture);
        }
        delete instance;
    } 
}
