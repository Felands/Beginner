#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <iostream>
#include <unordered_map>
#include <string>

#include "SDL.h"

#include "Vector2D.h"

struct ResourceInfo
{
	Vector2D coordinate;
	Vector2D size;
	uint8_t numFrame;
};

class TextureManager
{
public:
    static TextureManager* Instance();

	bool Load(std::string fileName, SDL_Renderer* pRenderer);

	void LoadAllResource();

    void Draw(std::string id, int x, int y, int width, int height,
    	SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void DrawFrame(std::string id, int x, int y, int currentFrame, SDL_Renderer* pRenderer,
	    SDL_RendererFlip flip = SDL_FLIP_NONE);

    void ClearFromTextureMap(std::string id);

	void drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height,
        int currentRow, int currentFrame, SDL_Renderer *pRenderer);

	void Clean()
	{
		if (s_pInstance != nullptr) {
			delete s_pInstance;
		} 
	}

	SDL_Texture* GetTextureMap(std::string id)
	{
		if (m_textureMap.count(id) < 1) {
			std::cout << id << "is incorrect.\n";
		}
		return m_textureMap[id];
	}

	ResourceInfo* GetInfoMap(std::string id)
	{
		if (m_infoMap.count(id) < 1) {
			std::cout << id << "is incorrect.\n";
		}
		return m_infoMap[id];
	}

	uint8_t GetNumFrame(std::string id)
	{
		if (m_infoMap.count(id) < 1) {
			std::cout << id << "is incorrect.\n";
		}
		return m_infoMap[id]->numFrame;
	}

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
	std::unordered_map<std::string, ResourceInfo*> m_infoMap;
	static TextureManager* s_pInstance;
};

#endif