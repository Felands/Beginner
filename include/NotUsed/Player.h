#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "ShooterObject.h"

class Player : public SDLGameObject /*public ShooterObject*/
{
public:
    Player();

    virtual void Player::Load(std::unique_ptr<LoaderParams> pParams);

    virtual void Draw();

    virtual void Update();

    virtual void Clean();

    virtual std::string Type();

private:
    // handle any input from the keyboard, mouse, or joystick
    void HandleInput();

    // bring the player back if there are lives left
    void Ressurect();

    // handle any animation for the player
    void HandleAnimation();

private:
    // player can be invulnerable for a time
    int m_invulnerable;
    int m_invulnerableTime;
    int m_invulnerableCounter;
};

#endif