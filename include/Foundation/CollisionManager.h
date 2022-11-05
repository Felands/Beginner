#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <vector>

#include "Player.h"
#include "TileLayer.h"

class CollisionManager
{
public:
    void CheckPlayerEnemyBulletCollision(Player* player);
    void CheckPlayerEnemyCollision(Player* player, const std::vector<GameObject*> &objects);
    void CheckEnemyPlayerBulletCollision(const std::vector<GameObject*> &objects);
    static bool CheckPlayerTileCollision(Player* player, const std::vector<Layer*> &collisionLayers);
};

#endif