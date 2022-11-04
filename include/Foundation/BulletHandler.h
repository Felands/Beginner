#ifndef BULLET_HANDLER_H
#define BULLET_HANDLER_H

#include <stdint.h>
#include <string>

#include "Bullet.h"
#include "Vector2D.h"

class BulletHandler {
public:
    static BulletHandler *Instance()
    {
        if(instance == nullptr) {
            instance = new BulletHandler();
        }
        return instance;
    }

    void AddPlayerBullet(int32_t x, int32_t y, std::vector<ObjectAnimeInfo> objectAnimeInfos,
        Vector2D heading);

    void AddEnemyBullet(int32_t x, int32_t y, std::vector<ObjectAnimeInfo> objectAnimeInfos,
        Vector2D heading);

    void Update();

private:
    static BulletHandler *instance;
    std::vector<PlayerBullet*> playerBullets;
    std::vector<EnemyBullet*> enemyBullets;
};

#endif