#include "CollisionManager.h"

#include <stdint.h>

#include "Player.h"

bool CollisionManager::CheckPlayerTileCollision(Player* player, const std::vector<Layer*> &collisionLayers)
{
    for(std::vector<Layer*>::const_iterator it = collisionLayers.begin(); it != collisionLayers.end(); ++it)
    {
        TileLayer* tileLayer;
        if (dynamic_cast<TileLayer*>(*it)) {
            tileLayer = dynamic_cast<TileLayer*>(*it);
        } else {
            continue;
        }
        std::vector<std::vector<uint32_t>> tileIds = tileLayer->GetTileIds();

        uint32_t xPosition = player->GetPosition().GetX() + player->GetWidth() / 4;
        uint32_t yPosition = player->GetPosition().GetY() + player->GetHeight() / 4;
        uint32_t tileWidth = tileLayer->GetTileWidth();
        uint32_t tileHeight = tileLayer->GetTileHeight();
        uint32_t tileColumn;
        uint32_t tileRow;
        if(player->GetVelocity().GetX() >= 0) {
            tileColumn = (xPosition + player->GetWidth() / 2) / tileWidth;
        } else {
            tileColumn = xPosition / tileWidth;
        }
        if(player->GetVelocity().GetY() >= 0) {
            tileRow = (yPosition + player->GetHeight() / 2) / tileHeight;
        } else {
            tileRow = yPosition / tileHeight;
        }
        uint32_t tileId = tileIds[tileRow][tileColumn];

        if(tileId != 0) {
            return true;
        }
    }
    return false;
}
