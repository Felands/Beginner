#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <unordered_map>

#include "SDL.h"
#include "SDL_mixer.h"

enum class SoundType
{
    SOUND_MUSIC,
    SOUND_SFX
};

struct SoundInfo {
    SoundType type;
    void* mixTrunk;
};

struct TextureInfo
{
    uint32_t width;
    uint32_t height;
    uint32_t numColumns;
    uint32_t numRows;
    SDL_Texture *texture;
};

struct ResourceMap {
    std::unordered_map<std::string, TextureInfo> textureMap;
    std::unordered_map<std::string, SoundInfo> soundMap;
};

class Resource
{
public:
    static Resource* Instance()
    {
        if (instance == nullptr) {
            instance = new Resource();
        }
        return instance;
    }

    TextureInfo GetTxetureInfo(std::string name)
    {
        return resourceMap.textureMap[name];
    }

    bool LoadOneSound(std::string source, std::string name, SoundType type);
    
    bool LoadOneTexture(std::string fileName, std::string name, uint32_t width, uint32_t height, uint32_t numColumns,
        uint32_t numRows, SDL_Renderer *renderer);

    void Draw(std::string name, int32_t xPos, int32_t yPos, uint32_t currentFrame, uint32_t currentRow,
        SDL_Renderer *renderer, SDL_RendererFlip flip, uint32_t alpha);

    void Play(std::string name, uint32_t loop);

    void ClearOneSound(std::string name);

    void ClearOneTexture(std::string name);

    void Clean();

private:
    Resource()
    {
        Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
    }

    ~Resource()
    {
        Mix_CloseAudio();
    }

    static Resource* instance;
    ResourceMap resourceMap;
};

#endif