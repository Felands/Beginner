#include "SDL.h"

#include "Player.h"
#include "InputHandler.h"
#include "log.h"
#include "Resource.h"
#include "Game.h"
#include "SoundManager.h"

void Player::HandleInput()
{
    LOG_DBG("[Player][HandleInput] Handling the input");

    bool wDown = InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_W);
    bool sDown = InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_S);
    bool aDown = InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_A);
    bool dDown = InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_D);
    if (wDown) {
        position += Vector2D(0, -1);
        velocity += Vector2D(0, -0.1);
        state = PlayerState::RUN;
    }
    if (sDown) {
        position += Vector2D(0, 1);
        velocity += Vector2D(0, 0.1);
        state = PlayerState::RUN;
    }
    if (aDown) {
        position += Vector2D(-1, 0);
        velocity += Vector2D(-0.1, 0);
        state = PlayerState::RUN;
    }
    if (dDown) {
        position += Vector2D(1, 0);
        velocity += Vector2D(0.1, 0);
        state = PlayerState::RUN;
    }
    if (!(wDown || sDown || aDown || dDown) && velocity.Length() < 1.0e-4) {
        state = PlayerState::IDLE;
    }

    if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_J)) {
        state = PlayerState::HIT;
    } else {
        state = PlayerState::IDLE;
    }

    LOG_DBG("[Player][HandleInput] Handled the input");
}

void Player::Update()
{
    LOG_DBG("[Player][Update] Updating the player");

    // if the level is complete then fly off the screen
    if (Game::Instance()->GetLevelComplete()) {
        if (position.GetX() >= Game::Instance()->GetGameScreenWidth()) {
            Game::Instance()->SetCurrentLevel(Game::Instance()->GetCurrentLevel() + 1);
        } else {
            velocity.SetY(0);
            velocity.SetX(3);
            SDLGameObject::Update();
            HandleAnimation();
        }
    } else {
        if (!dying) {
            velocity.SetX(0);
            velocity.SetY(0);

            HandleInput();
            SDLGameObject::Update();
            HandleAnimation();

            if (state == PlayerState::HIT) {
                SoundManager::Instance()->PlaySound("arrow_hit", 1);
            }
        } else {
            if (dyingCounter == dyingTime) {
                Ressurect();
            }
            dyingCounter++;
        }
    }

    LOG_DBG("[Player][Update] Updated the player");
}

void Player::Draw()
{
    LOG_DBG("[Player][Draw] Drawing the player");

    SDLGameObject::Draw();

    SDL_RendererFlip flip;
    if (velocity.GetX() >= 0) {
        flip = SDL_FLIP_NONE;
    } else {
        flip = SDL_FLIP_HORIZONTAL;
    }

    uint32_t ticks = SDL_GetTicks();
    uint32_t currentColumns = ticks / (1000 / GetAnimeSpeed());

    TextureManager::Instance()->Draw(GetTextureName(), position.GetX(), position.GetY(),
        currentColumns, 0, Game::Instance()->GetRenderer(), flip, alpha);

    LOG_DBG("[Player][Draw] Drew the player");
}

void Player::Ressurect()
{
    Game::Instance()->SetPlayerLives(Game::Instance()->GetPlayerLives() - 1);
    position.SetX(10);
    position.SetY(200);
    dying = false;
    dyingCounter = 0;
    invulnerable = true;
    state = PlayerState::IDLE;
}

void Player::HandleAnimation()
{
    // if the player is invulnerable we can flash its alpha to let people know
    if (invulnerable) {
        // invulnerability is finished, set values back
        if (invulnerableCounter == invulnerableTime) {
            invulnerable = false;
            invulnerableCounter = 0;
            alpha = 255;
        } else { // otherwise, flash the alpha on and off
            if (alpha == 255) {
                alpha = 0;
            } else {
                alpha = 255;
            }
            invulnerableCounter++;
        }
    }

    if (!dead) {
        // do nothing
    }
}
