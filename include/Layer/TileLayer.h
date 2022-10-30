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

    Vector2D GetPosition()
    {
        return position;
    }

    Vector2D GetVelocity()
    {
        return velocity;
    }

private:
    Vector2D position;
    Vector2D velocity;
    const std::vector<Tileset> &tilesets;
    std::vector<std::vector<uint32_t>> tileIds;
};

#endif
