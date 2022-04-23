#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

#include "Layer.h"

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

    void Update();

    void Render();

    void Clean();

private:
    std::vector<Tileset> tilesets;
    std::vector<Layer*> tileLayers;
    std::vector<Layer*> objectLayers;
};

#endif
