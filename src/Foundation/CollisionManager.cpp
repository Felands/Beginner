#include "CollisionManager.h"

#include <stdint.h>

#include "Player.h"

void CollisionManager::CheckPlayerTileCollision(Player* player, const std::vector<TileLayer*> &collisionLayers)
{
    // iterate through collision layers
    for(std::vector<TileLayer*>::const_iterator it = collisionLayers.begin(); it != collisionLayers.end(); ++it)
    {
        /*TileLayer* tileLayer = (*it);
        std::vector<std::vector<uint32_t>> tiles = tileLayer->GetTileIds();
        Vector2D layerPos = tileLayer->GetPosition();
        int x, y, tileColumn, tileRow, tileid = 0;
        // calculate position on tile map
        x = layerPos.GetX() / tileLayer->GetTileSize();
        y = layerPos.GetY() / tileLayer->GetTileSize();
        // if moving forward or upwards
        if(player->GetVelocity().GetX() >= 0 || player->GetVelocity().GetY() >= 0) {
            tileColumn = ((player->GetPosition().GetX() + player->GetWidth()) / tileLayer->GetTileSize());
            tileRow = ((player->GetPosition().GetY() + player->GetHeight()) / tileLayer->GetTileSize());
            tileid = tiles[tileRow + y][tileColumn + x];
        } else if(player->GetVelocity().GetX() < 0 || player->GetVelocity().GetY() < 0) {
            tileColumn = player->GetPosition().GetX() / tileLayer->GetTileSize();
            tileRow = player->GetPosition().GetY() / tileLayer->GetTileSize();
            tileid = tiles[tileRow + y][tileColumn + x];
        }

        if(tileid != 0) {
            player->Collision();
        }*/
    }
}
