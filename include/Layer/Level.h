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

    void Update();

    void Render();

    void Clean();

    Player* GetPlayer() { return player; }

    void SetPlayer(Player* player) { this->player = player; }

private:
    std::vector<Tileset> tilesets;
    std::vector<Layer*> tileLayers;
    std::vector<Layer*> objectLayers;
    std::vector<Layer*> collisionLayers;
    Player* player; 
};

#endif
