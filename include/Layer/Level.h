#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

#include "Layer.h"
#include "Player.h"

struct Tileset
{
    std::string name;
    uint32_t firstGridId;
    std::vector<std::string> tileNames;
};

class Level
{
public:
    std::vector<Tileset> *GetTilesets()
    {
        return &tilesets;
    }

    std::vector<Layer*> *GetTileLayers() 
    { 
        return &tileLayers; 
    }

    std::vector<Layer*> *GetObjectLayers() 
    { 
        return &objectLayers; 
    }

    std::vector<Layer*> *GetCollisionLayers() 
    { 
        return &collisionLayers; 
    }

    uint32_t GetWidth()
    {
        return width;
    }

    void SetWidth(uint32_t width)
    {
        this->width = width;
    }

    uint32_t GetHeight()
    {
        return height;
    }

    void SetHeight(uint32_t height)
    {
        this->height = height;
    }

    void Update();

    void Render();

    void Clean();

    Player* GetPlayer() { return player; }

    void SetPlayer(Player* player) { this->player = player; }

private:
    uint32_t width;
    uint32_t height;
    std::vector<Tileset> tilesets;
    std::vector<Layer*> tileLayers;
    std::vector<Layer*> objectLayers;
    std::vector<Layer*> collisionLayers;
    Player* player; 
};

#endif
