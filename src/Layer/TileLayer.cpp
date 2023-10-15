#include "TileLayer.h"
#include "Game.h"
#include "Resource.h"
#include "Log.h"
#include "Camera.h"

TileLayer::TileLayer(const std::vector<Tileset> &tilesets_) : tilesets(tilesets_)
{}

void TileLayer::Update()
{
    LOG_DBG("[TileLayer][Update] Updating the tile layer");

    LOG_DBG("[TileLayer][Update] Updated the tile layer");
}

void TileLayer::Render()
{
    LOG_DBG("[TileLayer][Render] Rendering the tile layer");

    Vector2D position = Camera::Instance()->GetPosition();
    uint32_t screenHeight = Game::Instance()->GetGameScreenHeight();
    uint32_t screenWidth = Game::Instance()->GetGameScreenWidth();
    uint32_t startI = position.GetY() / tileHeight;
    uint32_t endI = (screenHeight + position.GetY()) / tileHeight;
    if (endI >= tileIds.size()) {
        endI = tileIds.size() - 1;
    }
    uint32_t startJ = position.GetX() / tileWidth;
    uint32_t endJ = (screenWidth + position.GetX()) / tileWidth;
    if (endJ >= tileIds[0].size()) {
        endJ = tileIds[0].size() - 1;
    }
    int32_t startX = startJ * tileWidth - position.GetX();
    int32_t startY = startI * tileHeight - position.GetY();
    /* LOG_ERR("position.x", position.GetX(), "position.y", position.GetY(), "startX", startX,
        "startY", startY); */
    for(size_t i = startI; i <= endI; i++) {
        for(size_t j = startJ; j <= endJ; j++) {
            size_t id = tileIds[i][j];
            if(id == 0) {
                continue;
            }
            Tileset tileset = GetTilesetById(id);
            id -= tileset.firstGridId;
            Resource::Instance()->Draw(tileset.tileNames[id], startX + (j - startJ) * tileWidth,
                startY + (i - startI) * tileHeight, 0, 0, Game::Instance()->GetRenderer(), SDL_FLIP_NONE, 255);
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
