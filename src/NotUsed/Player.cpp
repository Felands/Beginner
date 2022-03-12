#include <stdint.h>

#include "SDL.h"

#include "Player.h"
#include "LoaderParams.h"
#include "SDLGameObject.h"
#include "Vector2D.h"
#include "InputHandler.h"

Player::Player() : SDLGameObject()
{}

void Player::load(const LoaderParams *pParams)
{
 SDLGameObject::load(pParams);
}

void Player::Update()
{
    m_currentFrame = int32_t(((SDL_GetTicks() / 100) % 8));
    m_velocity.SetX(1);
    SDLGameObject::Update();
}

void Player::HandleInput()
{
    Vector2D* target = InputHandler::Instance()->GetMousePosition();
    m_velocity = *target - m_position;
    m_velocity /= 50;
}

void Player::ressurect()
{
 TheGame::Instance()->setPlayerLives(TheGame::Instance()
 ->getPlayerLives() - 1);
 m_position.setX(10);
 m_position.setY(200);
 m_bDying = false;
 m_textureID = "player";
 m_currentFrame = 0;
 m_numFrames = 5;
 m_width = 101;
 m_height = 46;
 m_dyingCounter = 0;
 m_invulnerable = true;
}

void Player::handleAnimation()
{
 // if the player is invulnerable we can flash its alpha to let 
 people know
 if(m_invulnerable)
 {
 // invulnerability is finished, set values back
 if(m_invulnerableCounter == m_invulnerableTime)
 {
 m_invulnerable = false;
 m_invulnerableCounter = 0;
 m_alpha = 255;
 }
 else// otherwise, flash the alpha on and off
 {
 if(m_alpha == 255)
 {
 m_alpha = 0;
 }
 else
 {
 m_alpha = 255;
 }
 }
 // increment our counter
 m_invulnerableCounter++;
 }
 // if the player is not dead then we can change the angle with 
 the velocity to give the impression of a moving helicopter
 if(!m_bDead)
 {
 if(m_velocity.getX() < 0)
 {
 m_angle = -10.0;
 }
 else if(m_velocity.getX() > 0)
 {
 m_angle = 10.0;
 }
 else
 {
 m_angle = 0.0;
 }
 }
 // our standard animation code - for helicopter propellors
 m_currentFrame = int(((SDL_GetTicks() / (100)) % m_numFrames));
}

void Player::update()
{
 // if the level is complete then fly off the screen
 if(TheGame::Instance()->getLevelComplete())
 {
 if(m_position.getX() >= TheGame::Instance()->getGameWidth())
 {
 TheGame::Instance()->setCurrentLevel(TheGame::Instance()
 ->getCurrentLevel() + 1);
 }
 else
 {
 m_velocity.setY(0);
 m_velocity.setX(3);
 ShooterObject::update();
 handleAnimation();
 }
 }
 else
 {
 // if the player is not doing its death animation then update 
 it normally
 if(!m_bDying)
 {
 // reset velocity
 m_velocity.setX(0);
 m_velocity.setY(0);
 // get input
 handleInput();
 // do normal position += velocity update
 ShooterObject::update();
 // update the animation
 handleAnimation();
 }
 else // if the player is doing the death animation
 {
 m_currentFrame = int(((SDL_GetTicks() / (100)) % 
 m_numFrames));
 // if the death animation has completed
 if(m_dyingCounter == m_dyingTime)
 {
 // ressurect the player
 ressurect();
 }
 m_dyingCounter++;
 }
 }
}

void Player::update()
{
 if(!m_bDying)
 {
 // fell off the edge
 if(m_position.m_y + m_height >= 470)
 {
 collision();
 }
 // get the player input
 handleInput();
 if(m_bMoveLeft)
 {
 if(m_bRunning)
 {
 m_velocity.m_x = -5;
 }
 else
 {
 m_velocity.m_x = -2;
 }
 }
 else if(m_bMoveRight)
 {
 if(m_bRunning)
 {
 m_velocity.m_x = 5;
 }
 else
 {
 m_velocity.m_x = 2;
 }
 }
 else
 {
 m_velocity.m_x = 0;
 }
 // if we are higher than the jump height set jumping to false
 if(m_position.m_y < m_lastSafePos.m_y - m_jumpHeight)
 {
 m_bJumping = false;
 }
 if(!m_bJumping)
 {
 m_velocity.m_y = 5;
 }
 else
 {
 m_velocity.m_y = -5;
 }
 handleMovement(m_velocity);
 }
 else
 {
 m_velocity.m_x = 0;
 if(m_dyingCounter == m_dyingTime)
 {
 ressurect();
 }
 m_dyingCounter++;
 m_velocity.m_y = 5;
 }
 handleAnimation();
}

void Player::handleMovement(Vector2D velocity)
{
 // get the current position
 Vector2D newPos = m_position;
 // add velocity to the x position
 newPos.m_x = m_position.m_x + velocity.m_x;
 // check if the new x position would collide with a tile
 if(!checkCollideTile(newPos))
 {
 // no collision, add to the actual x position
 m_position.m_x = newPos.m_x;
 }
 else
 {
 // collision, stop x movement
 m_velocity.m_x = 0;
 }
 // get the current position after x movement
 newPos = m_position;
 // add velocity to y position
 newPos.m_y += velocity.m_y;
 // check if new y position would collide with a tile
 if(!checkCollideTile(newPos))
 {
 // no collision, add to the actual x position
 m_position.m_y = newPos.m_y;
 }
 else
 {
 // collision, stop y movement
 m_velocity.m_y = 0;
 // we collided with the map which means we are safe on the 
 ground,
 // make this the last safe position
 m_lastSafePos = m_position;
 // move the safe pos slightly back or forward so when 
 resurrected we are safely on the ground after a fall
 if(velocity.m_x > 0)
 {
 m_lastSafePos.m_x -= 32;
 }
 else if(velocity.m_x < 0)
 {
 m_lastSafePos.m_x += 32;
 }
 // allow the player to jump again
 m_bCanJump = true;
 // jumping is now false
 m_bJumping = false;
 }

 void Player::handleInput()
{
 if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT) && 
 m_position.m_x < ((*m_pCollisionLayers->begin())->getMapWidth() 
 * 32))
 {
 if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_A))
 {
 m_bRunning = true;
 }
 else
 {
 m_bRunning = false;
 }
 m_bMoveRight = true;
 m_bMoveLeft = false;
 }
 else if(TheInputHandler::Instance()
 ->isKeyDown(SDL_SCANCODE_LEFT) && m_position.m_x > 32)
 {
 if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_A))
 {
 m_bRunning = true;
 }
 else
 {
 m_bRunning = false;
 }
 m_bMoveRight = false;
 m_bMoveLeft = true;
 }
 else
 {
 m_bMoveRight = false;
 m_bMoveLeft = false;
 }
 if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) 
 && m_bCanJump && !m_bPressedJump)
 {
 TheSoundManager::Instance()->playSound("jump", 0);
 if(!m_bPressedJump)
 {
 m_bJumping = true;
 m_bCanJump = false;
 m_lastSafePos = m_position;
 m_bPressedJump = true;
 }
 }
 if(!TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) 
 && m_bCanJump)
 {
 m_bPressedJump = false;
 }
}


