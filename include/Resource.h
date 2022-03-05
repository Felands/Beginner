#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <unordered_map>
#include <string>

#include "SDL.h"

class TextureManager
{
public:
	bool Load(std::string fileName,std::string id, SDL_Renderer* pRenderer);

    void Draw(std::string id, int x, int y, int width, int height,
    	SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void DrawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame,
    	SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    static TextureManager* Instance();

private:
    TextureManager()
	{}

	~TextureManager()
	{
		for (auto it : m_textureMap) {
			SDL_DestroyTexture(it.second);
		}
	}

private:
	std::unordered_map<std::string, SDL_Texture*> m_textureMap;
	static TextureManager* s_pInstance;
};

#endif