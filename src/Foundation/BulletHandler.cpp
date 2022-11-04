#include "BulletHandler.h"

#include "Bullet.h"
#include "Game.h"

void BulletHandler::AddPlayerBullet(int32_t x, int32_t y, std::vector<ObjectAnimeInfo> objectAnimeInfos,
    Vector2D heading)
{
    PlayerBullet* playerBullet = new PlayerBullet();
    playerBullet->Load(x, y, objectAnimeInfos, heading);
    playerBullets.push_back(playerBullet);
}

void BulletHandler::AddEnemyBullet(int32_t x, int32_t y, std::vector<ObjectAnimeInfo> objectAnimeInfos,
    Vector2D heading)
{
    EnemyBullet* enemyBullet = new EnemyBullet();
    enemyBullet->Load(x, y, objectAnimeInfos, heading);
    enemyBullets.push_back(enemyBullet);
}

void BulletHandler::Update()
{
    for (std::vector<PlayerBullet*>::iterator it = playerBullets.begin(); it != playerBullets.end();) {
        if((*it)->GetPosition().GetX() < 0 || (*it)->GetPosition().GetX() > Game::Instance()->GetGameScreenWidth() ||
            (*it)->GetPosition().GetY() < 0 || (*it)->GetPosition().GetY() > Game::Instance()->GetGameScreenHeight() || 
            (*it)->Dead()) {
            delete * it;
            it = playerBullets.erase(it);
        } else {
            (*it)->Update();
            ++it;
        }
    }
}
