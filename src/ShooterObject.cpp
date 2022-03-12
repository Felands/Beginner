void ShooterObject::doDyingAnimation()
{
 // keep scrolling with the map
 scroll(TheGame::Instance()->getScrollSpeed());
 m_currentFrame = int(((SDL_GetTicks() / (1000 / 3)) % 
 m_numFrames));
 if(m_dyingCounter == m_dyingTime)
 {
 m_bDead = true;
 }
 m_dyingCounter++; //simple counter, fine with fixed frame rate
}