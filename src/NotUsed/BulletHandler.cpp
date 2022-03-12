void BulletHandler::addPlayerBullet(int x, int y, int width, int 
 height, std::string textureID, int numFrames, Vector2D heading)
{
 PlayerBullet* pPlayerBullet = newPlayerBullet();
 pPlayerBullet->load(std::unique_ptr<LoaderParams>(new 
 LoaderParams(x, y, width, height, textureID, numFrames)), 
 heading);
 m_playerBullets.push_back(pPlayerBullet);
}
void BulletHandler::addEnemyBullet(int x, int y, int width, int 
height, std::string textureID, int numFrames, Vector2D heading)
{
 EnemyBullet* pEnemyBullet = new EnemyBullet();
 pEnemyBullet->load(std::unique_ptr<LoaderParams>(new 
 LoaderParams(x, y, width, height, textureID, numFrames)), 
 heading);
 m_enemyBullets.push_back(pEnemyBullet);
}