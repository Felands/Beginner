void CollisionManager::checkPlayerTileCollision(Player* pPlayer, 
 const std::vector<TileLayer*> &collisionLayers)
{
 // iterate through collision layers
 for(std::vector<TileLayer*>::const_iterator it = 
 collisionLayers.begin(); it != collisionLayers.end(); ++it)
 {
 TileLayer* pTileLayer = (*it);
 std::vector<std::vector<int>> tiles = pTileLayer-
 >getTileIDs();
 // get this layers position
 Vector2D layerPos = pTileLayer->getPosition();
 int x, y, tileColumn, tileRow, tileid = 0;
 // calculate position on tile map
 x = layerPos.getX() / pTileLayer->getTileSize();
 y = layerPos.getY() / pTileLayer->getTileSize();
 // if moving forward or upwards
 if(pPlayer->getVelocity().getX() >= 0 || pPlayer-
 >getVelocity().getY() >= 0)
 {
 tileColumn = ((pPlayer->getPosition().getX() + pPlayer-
 >getWidth()) / pTileLayer->getTileSize());
 tileRow = ((pPlayer->getPosition().getY() + pPlayer-
 >getHeight()) 
 / pTileLayer->getTileSize());
 tileid = tiles[tileRow + y][tileColumn + x];
 }
 else if(pPlayer->getVelocity().getX() < 0 || pPlayer-
 >getVelocity().getY() < 0) // if moving backwards or downwards
 {
 tileColumn = pPlayer->getPosition().getX() / pTileLayer-
 >getTileSize();
 tileRow = pPlayer->getPosition().getY() / pTileLayer-
 >getTileSize();
 tileid = tiles[tileRow + y][tileColumn + x];
 }
 if(tileid != 0) // if the tile id not blank then collide
 {
 pPlayer->collision();
 }
 }
}
