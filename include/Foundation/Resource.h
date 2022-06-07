#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <unordered_map>

#include "SDL.h"

struct TextureInfo
{
    uint32_t width;
    uint32_t height;
    uint32_t numColumns;
    uint32_t numRows;
    SDL_Texture *texture;
};

class TextureManager
{
public:
    static TextureManager *Instance()
    {
        if (instance == nullptr) {
            instance = new TextureManager();
        }
        return instance;
    }

    TextureInfo GetTxetureInfo(std::string name)
    {
        return textureMap[name];
    }

    bool Load(std::string fileName, std::string name, uint32_t width, uint32_t height, uint32_t numColumns,
        uint32_t numRows, SDL_Renderer *renderer);

    void Draw(std::string name, int32_t xPos, int32_t yPos, uint32_t currentFrame, uint32_t currentRow,
        SDL_Renderer *renderer, SDL_RendererFlip flip, uint32_t alpha);

    void ClearFromTextureMap(std::string name);

    void Clean();

private:
    TextureManager()
    {}

    ~TextureManager()
    {}

    static TextureManager *instance;
    std::unordered_map<std::string, TextureInfo> textureMap;
};

#endif