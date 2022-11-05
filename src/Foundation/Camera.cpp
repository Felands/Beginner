#include "Camera.h"

#include <math.h>
#include <stdint.h>

#include "Game.h"
#include "log.h"
#include "PlayState.h"

Camera* Camera::instance = nullptr;

void Camera::Update()
{
    if (target == nullptr) {
        return;
    }
    velocity.SetX(0);
    velocity.SetY(0);
    int32_t distanceX = target->GetPosition().GetX() - position.GetX() - Game::Instance()->GetGameScreenWidth() / 2;
    int32_t distanceY = target->GetPosition().GetY() - position.GetY() - Game::Instance()->GetGameScreenHeight() / 2;
    Vector2D velocity(distanceX / 10, distanceY / 10);
    if (distanceX < 0) {
        velocity.SetX(-1);
    } else if (distanceX > 0) {
        velocity.SetX(1);
    }
    if (distanceY < 0) {
        velocity.SetY(-1);
    } else if (distanceY > 0) {
        velocity.SetY(1);
    }
    Vector2D pos(position + velocity);
    GameStateMachine* gameStateMachine = Game::Instance()->GetStateMachine();
    PlayState* playState = dynamic_cast<PlayState*>(gameStateMachine->GetCurrentState());
    Level* level = playState->GetLevel();
    if (pos.GetX() > level->GetWidth() - Game::Instance()->GetGameScreenWidth()) {
        pos.SetX(level->GetWidth() - Game::Instance()->GetGameScreenWidth());
    }
    if (pos.GetX() < 0) {
        pos.SetX(0);
    }
    if (pos.GetY() > level->GetHeight() - Game::Instance()->GetGameScreenHeight()) {
        pos.SetY(level->GetHeight() - Game::Instance()->GetGameScreenHeight());
    }
    if (pos.GetY() < 0) {
        pos.SetY(0);
    }
    SetPosition(pos);
}
