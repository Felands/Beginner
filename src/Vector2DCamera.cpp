const Vector2DCamera::getPosition() const
{
{
 if(m_pTarget != 0)
 {
 Vector2D pos(m_pTarget->m_x - (TheGame::Instance()
 ->getGameWidth() / 2), 0);
 if(pos.m_x< 0)
 {
 pos.m_x = 0;
 }
 return pos;
 }
 return m_position;
}
