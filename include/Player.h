#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "ShooterObject.h"

class Player : public ShooterObject
{
public:
    Player();

    virtual void Draw();

    virtual void Update();

    virtual void Clean();

    virtual void Player::Load(const LoaderParams *pParams);

    virtual void HandleInput();

private:
 // bring the player back if there are lives left
 void ressurect();
 // handle any input from the keyboard, mouse, or joystick
 void handleInput();
 // handle any animation for the player
 void handleAnimation();
 // player can be invulnerable for a time
 int m_invulnerable;
 int m_invulnerableTime;
 int m_invulnerableCounter;
};

#endif