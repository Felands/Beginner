#include "TileLayer.h"
#include "Game.h"
#include "Resource.h"

TileLayer::TileLayer(uint32_t tileSize, const std::vector<Tileset> &tilesets) :
    m_tileSize(tileSize), m_tilesets(tilesets), m_position(0,0), m_velocity(0,0)
{
    m_numColumns = (Game::Instance()->GetGameWidth() / m_tileSize);
    m_numRows = (Game::Instance()->GetGameHeight() / m_tileSize);
}

void TileLayer::Update()
{
    m_position += m_velocity;
    m_velocity.SetX(1);
}

void TileLayer::Render()
{
    uint32_t x, y, x2, y2;
    x = m_position.GetX() / m_tileSize;
    y = m_position.GetY() / m_tileSize;
    x2 = uint32_t(m_position.GetX()) % m_tileSize;
    y2 = uint32_t(m_position.GetY()) % m_tileSize;
    for(size_t i = 0; i < m_numRows; i++) {
        for(size_t j = 0; j < m_numColumns; j++) {
            size_t id = m_tileIDs[i][j + x];
            if(id == 0) {
                continue;
            }
            Tileset tileset = GetTilesetByID(id);
            id--;
            TextureManager::Instance()->DrawTile(tileset.name, tileset.margin, tileset.spacing, (j * m_tileSize) - x2, (i * m_tileSize) - y2,
                m_tileSize, m_tileSize, (id - (tileset.firstGridID - 1)) / tileset.numColumns,
                (id - (tileset.firstGridID - 1)) % tileset.numColumns, Game::Instance()->GetRenderer());
        }
    }
}

Tileset TileLayer::GetTilesetByID(uint32_t tileID)
{
    for(size_t i = 0; i < m_tilesets.size(); i++) {
        if( i + 1 <= m_tilesets.size() - 1) {
            if(tileID >= m_tilesets[i].firstGridID && tileID < m_tilesets[i + 1].firstGridID) {
                return m_tilesets[i];
            }
        }
        else {
            return m_tilesets[i];
        }
    }
    std::cout << "did not find tileset, returning empty tileset\n";
    Tileset t = { 0 };
    return t;
}
