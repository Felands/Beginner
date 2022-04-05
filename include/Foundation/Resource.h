#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <unordered_map>
#include <string>

#include "SDL.h"

class TextureManager
{
public:
    static TextureManager* Instance();

	bool Load(std::string fileName, std::string id, SDL_Renderer *pRenderer);

    void DrawFrame(std::string id, int32_t x, int32_t y, uint32_t width, uint32_t height, uint32_t currentRow,
	    uint32_t currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void ClearFromTextureMap(std::string id);

	void DrawTile(std::string id, int32_t margin, int32_t spacing, int32_t x, int32_t y, int32_t width, int32_t height,
        int32_t currentRow, int32_t currentFrame, SDL_Renderer *pRenderer);

	void Clean();

private:
    TextureManager()
	{}

	std::map<std::string, SDL_Texture*> m_textureMap;
	static TextureManager* s_pInstance;
};

#endif