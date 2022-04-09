#ifndef _TILE_LAYER_H_
#define _TILE_LAYER_H_

#include <vector>

#include "Level.h"
#include "Vector2D.h"

class TileLayer : public Layer
{
public:
    TileLayer(uint32_t tileSize, const std::vector<Tileset> &tilesets);

    virtual void Update();

    virtual void Render();

    void SetTileIDs(const std::vector<std::vector<uint32_t>> &data) 
    { 
        m_tileIDs = data; 
    }

    void SetTileSize(uint32_t tileSize) 
    { 
        m_tileSize = tileSize; 
    }

    Tileset GetTilesetByID(uint32_t tileID);

private:
    uint32_t m_numColumns;
    uint32_t m_numRows;
    uint32_t m_tileSize;
    Vector2D m_position;
    Vector2D m_velocity;
    const std::vector<Tileset> &m_tilesets;
    std::vector<std::vector<uint32_t>> m_tileIDs;
};

#endif
