#include "Camera.h"

#include "Game.h"

const Vector2D Camera::GetPosition() const
{
    if(target != 0) {
        Vector2D pos(target->GetX() - (Game::Instance()->GetGameScreenWidth() / 2), 0);
        if(pos.GetX()< 0) {
            pos.SetX(0);
        }
        return pos;
    }
    return position;
}
