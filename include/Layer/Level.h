#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <string>
#include <vector>

#include "Layer.h"

struct Tileset
{
    uint32_t firstGridID;
    uint32_t tileWidth;
    uint32_t tileHeight;
    uint32_t spacing;
    uint32_t margin;
    uint32_t width;
    uint32_t height;
    uint32_t numColumns;
    std::string name;
};

class Level
{
public:
    void Update();

    void Render();

    std::vector<Tileset> *GetTilesets() 
    { 
        return &m_tilesets; 
    }

    std::vector<Layer*> *GetLayers() 
    { 
        return &m_layers; 
    }

private:
    friend class LevelParser;

    Level()
    {}

    ~Level()
    {}

    std::vector<Tileset> m_tilesets;
    std::vector<Layer*> m_layers;
};

#endif
