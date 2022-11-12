#include "SDL_image.h"
#include "tinyxml.h"

#include "Resource.h"

#include "log.h"

Resource* Resource::instance = nullptr;

bool Resource::LoadOneSound(std::string source, std::string name, SoundType type)
{
    LOG_DBG("[Resource][LoadOneSound] Loading the sound ", name, " from ", source);

    void* mixTrunk = nullptr;
    if (type == SoundType::SOUND_MUSIC) {
        mixTrunk = Mix_LoadMUS(source.c_str());
    } else if (type == SoundType::SOUND_SFX) {
        mixTrunk = Mix_LoadWAV(source.c_str());
    }

    if(mixTrunk == nullptr) { 
        LOG_ERR("[Resource][LoadOneSound] Could not load sound from ", source, " : ERROR - ", Mix_GetError());
        return false;
    }

    resourceMap.soundMap[name] = {
        .type = type,
        .mixTrunk = mixTrunk
    };

    LOG_DBG("[Resource][LoadOneSound] Loaded the sound ", name, " from ", source);
    return true;
}
    
bool Resource::LoadOneTexture(std::string fileName, std::string name, uint32_t width, uint32_t height, uint32_t numColumns,
    uint32_t numRows, SDL_Renderer *renderer)
{
    LOG_DBG("[Resource][LoadOneTexture] Loading ", name, " from ", fileName);

    SDL_Surface *surface = IMG_Load(fileName.c_str());
    if(surface == nullptr) {
        LOG_ERR("[Resource][LoadOneTexture] Failed to load the surface, because: ", IMG_GetError());
        return false;
    } else {
        LOG_DBG("[Resource][LoadOneTexture] Succeed to load the surface");
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if(texture == nullptr) {
        LOG_ERR("[Resource][LoadOneTexture] Failed to load the texture, because: ", SDL_GetError());
        return false;
    } else {
        LOG_DBG("[Resource][LoadOneTexture] Succeed to load the texture");
    }

    TextureInfo textureInfo = {
        .width = width,
        .height = height,
        .numColumns = numColumns,
        .numRows = numRows,
        .texture = texture,
    };
    resourceMap.textureMap[name] = textureInfo;

    LOG_DBG("[Resource][LoadOneTexture] Loaded ", name, " from ", fileName);
    return true;
}

void Resource::Play(std::string name, uint32_t loop)
{
    LOG_DBG("[Resource][Play] playing the sound ", name, " for ", loop, " times");

    if (resourceMap.soundMap[name].type == SoundType::SOUND_MUSIC) {
        Mix_PlayMusic((Mix_Music*)resourceMap.soundMap[name].mixTrunk, loop);
    } else if (resourceMap.soundMap[name].type == SoundType::SOUND_SFX) {
        Mix_PlayChannel(-1, (Mix_Chunk*)resourceMap.soundMap[name].mixTrunk, loop);
    }

    LOG_DBG("[Resource][Play] played the sound ", name, " for ", loop, " times");
}

void Resource::Draw(std::string name, int32_t xPos, int32_t yPos, uint32_t currentColumn, uint32_t currentRow,
    SDL_Renderer *renderer, SDL_RendererFlip flip, uint32_t alpha)
{
    LOG_DBG("[Resource][Draw] Drawing the frame of ", name);

    currentColumn %= resourceMap.textureMap[name].numColumns;
    currentRow %= resourceMap.textureMap[name].numRows;

    SDL_Rect srcRect;
    srcRect.x = resourceMap.textureMap[name].width * currentColumn;
    srcRect.y = resourceMap.textureMap[name].width * currentRow;
    srcRect.w = resourceMap.textureMap[name].width;
    srcRect.h = resourceMap.textureMap[name].height;

    SDL_Rect destRect;
    destRect.x = xPos;
    destRect.y = yPos;
    destRect.w = resourceMap.textureMap[name].width;
    destRect.h = resourceMap.textureMap[name].height;
    SDL_SetTextureAlphaMod(resourceMap.textureMap[name].texture, alpha);
    SDL_RenderCopyEx(renderer, resourceMap.textureMap[name].texture, &srcRect, &destRect, 0, 0, flip);

    LOG_DBG("[Resource][Draw] Drew the frame of ", name);
}

void Resource::ClearOneSound(std::string name)
{
    LOG_DBG("[Resource][ClearOneSound] clearing the sound ", name);

    if (resourceMap.soundMap[name].type == SoundType::SOUND_MUSIC) {
        Mix_FreeMusic((Mix_Music*)resourceMap.soundMap[name].mixTrunk);
    } else if (resourceMap.soundMap[name].type == SoundType::SOUND_SFX) {
        Mix_FreeChunk((Mix_Chunk*)resourceMap.soundMap[name].mixTrunk);
    }
    resourceMap.soundMap.erase(name);

    LOG_DBG("[Resource][ClearOneSound] cleared the sound ", name);
}

void Resource::ClearOneTexture(std::string name)
{
    LOG_DBG("[Resource][ClearOneTexture] clearing the texture ", name);

    SDL_DestroyTexture(resourceMap.textureMap[name].texture);
    resourceMap.textureMap.erase(name);

    LOG_DBG("[Resource][ClearOneTexture] cleared the texture ", name);
}

void Resource::Clean()
{
    LOG_DBG("[Resource][Clean] cleaning");

    if (instance != nullptr) {
        for (auto& texture : resourceMap.textureMap) {
            ClearOneTexture(texture.first);
        }
        for (auto& sound : resourceMap.soundMap) {
            ClearOneSound(sound.first);
        }
        delete instance;
    }

    LOG_DBG("[Resource][Clean] cleaned");
}
