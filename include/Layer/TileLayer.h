#ifndef TILE_LAYER_H
#define TILE_LAYER_H

#include <vector>

#include "Level.h"
#include "Vector2D.h"

class TileLayer : public Layer
{
public:
    void SetTileIds(const std::vector<std::vector<uint32_t>> &data) 
    { 
        tileIds = data; 
    }

    TileLayer(const std::vector<Tileset> &tilesets_);

    virtual void Update();

    virtual void Render();

    virtual void Clean();

    Tileset GetTilesetById(uint32_t tileId);

    std::vector<std::vector<uint32_t>> GetTileIds()
    {
        return tileIds;
    }

    void SetTileWidth(uint32_t tileWidth)
    {
        this->tileWidth = tileWidth;
    }

    void SetTileHeight(uint32_t tileHeight)
    {
        this->tileHeight = tileHeight;
    }

    uint32_t GetTileWidth()
    {
        return tileWidth;
    }

    uint32_t GetTileHeight()
    {
        return tileHeight;
    }

private:
    uint32_t tileWidth;
    uint32_t tileHeight;
    const std::vector<Tileset> &tilesets;
    std::vector<std::vector<uint32_t>> tileIds;
};

#endif
