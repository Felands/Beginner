#include "Camera.h"
#include "Game.h"

const Vector2D Camera::GetPosition() const
{
    if(m_pTarget != 0)
    {
        Vector2D pos(m_pTarget->GetX() - (Game::Instance()->GetGameWidth() / 2), 0);
        if(pos.GetX()< 0)
        {
            pos.SetX(0);
        }
        return pos;
    }
    return m_position;
}
