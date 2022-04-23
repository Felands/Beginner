#include "TileLayer.h"
#include "Game.h"
#include "Resource.h"
#include "log.h"

TileLayer::TileLayer(const std::vector<Tileset> &tilesets_) :
    tilesets(tilesets_), position(0,0), velocity(0,0)
{}

void TileLayer::Update()
{
    LOG_DBG("[TileLayer][Update] Updating the tile layer");

    position += velocity;

    LOG_DBG("[TileLayer][Update] Updated the tile layer");
}

void TileLayer::Render()
{
    LOG_DBG("[TileLayer][Render] Rendering the tile layer");

    
    for(size_t i = 0; i < tileIds.size(); i++) {
        for(size_t j = 0; j < tileIds[0].size(); j++) {
            size_t id = tileIds[i][j];
            if(id == 0) {
                continue;
            }
            Tileset tileset = GetTilesetById(id);
            id -= tileset.firstGridId;
            TextureInfo textureInfo = TextureManager::Instance()->GetTxetureInfo(tileset.tileNames[id]);
            uint32_t tileWidth = textureInfo.width;
            uint32_t tileHeight = textureInfo.height;
            TextureManager::Instance()->Draw(tileset.tileNames[id], j * tileWidth, i * tileHeight,
                0, 0, Game::Instance()->GetRenderer(), SDL_FLIP_NONE);
        }
    }

    LOG_DBG("[TileLayer][Render] Rendered the tile layer");
}

void TileLayer::Clean()
{}

Tileset TileLayer::GetTilesetById(uint32_t tileId)
{
    LOG_DBG("[TileLayer][GetTilesetById] Getting tilesets by the tile id: ", tileId);

    for (size_t i = 0; i < tilesets.size(); i++) {
        if ( i + 1 <= tilesets.size() - 1) {
            if (tileId >= tilesets[i].firstGridId && tileId < tilesets[i + 1].firstGridId) {
                LOG_DBG("[TileLayer][GetTilesetById] Got tilesets by the tile id: ", tileId);
                return tilesets[i];
            }
        } else {
            LOG_DBG("[TileLayer][GetTilesetById] Got tilesets by the tile id: ", tileId);
            return tilesets[i];
        }
    }

    Tileset t = { 0 };
    LOG_DBG("[TileLayer][GetTilesetById] Did not find the tileset, returning empty tileset");
    return t;
}
