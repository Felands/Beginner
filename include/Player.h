#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "SDLGameObject.h"
#include "LoaderParams.h"

class Player : public ShooterObject
{
public:
    Player();

    virtual void Update();

    virtual void HandleInput();

    virtual void Player::load(const LoaderParams *pParams);

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
};

#endif