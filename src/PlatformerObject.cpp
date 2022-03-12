bool PlatformerObject::checkCollideTile(Vector2D newPos)
{
 if(newPos.m_y + m_height>= TheGame::Instance()->getGameHeight() 
 - 32)
 {
 return false;
 }
 else
 {
 for(std::vector<TileLayer*>::iterator it = m_pCollisionLayers
 ->begin(); it != m_pCollisionLayers->end(); ++it)
 {
 TileLayer* pTileLayer = (*it);
 std::vector<std::vector<int>> tiles = pTileLayer
 ->getTileIDs();
 Vector2D layerPos = pTileLayer->getPosition();
 int x, y, tileColumn, tileRow, tileid = 0;
 x = layerPos.getX() / pTileLayer->getTileSize();
 y = layerPos.getY() / pTileLayer->getTileSize();
 Vector2D startPos = newPos;
 startPos.m_x += 15;
 startPos.m_y += 20;
 Vector2D endPos(newPos.m_x + (m_width - 15), (newPos.m_y) + 
 m_height - 4);
 for(int i = startPos.m_x; i < endPos.m_x; i++)
 {
 for(int j = startPos.m_y; j < endPos.m_y; j++)
 {
 tileColumn = i / pTileLayer->getTileSize();
 tileRow = j / pTileLayer->getTileSize();
 tileid = tiles[tileRow + y][tileColumn + x];
 if(tileid != 0)
 {
 return true;
 }
 }
 }
 }
 return false; 
 }
}
