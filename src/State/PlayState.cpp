#include <string>

#include "PlayState.h"
#include "LevelParser.h"
#include "Resource.h"
#include "InputHandler.h"
#include "Game.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "log.h"
#include "SoundManager.h"

const std::string PlayState::playId = "PLAY";

bool PlayState::OnEnter()
{
    LOG_DBG("[PlayState][OnEnter] Entering the play state");

    LevelParser levelParser;
    level = levelParser.ParseLevel(LevelParser::level);
    SoundManager::Instance()->PlayMusic("bg1", 1);

    LOG_DBG("[PlayState][OnEnter] Entered the play state");
    return true;
}

bool PlayState::OnExit()
{
    LOG_DBG("[PlayState][OnExit] Exiting the play state");

    InputHandler::Instance()->Reset();

    for(int i = 0; i < textureIdList.size(); i++) {
        TextureManager::Instance()->ClearFromTextureMap(textureIdList[i]);
    }

    level->Clean();
    delete level;

    LOG_DBG("[PlayState][OnExit] Exited the play state");
    return true;
}

void PlayState::Render()
{
    LOG_DBG("[PlayState][Render] Rendering the play state");

    level->Render();

    LOG_DBG("[PlayState][Render] Rendered the play state");
}

void PlayState::Update()
{
    LOG_DBG("[PlayState][Update] Updating the play state");

    level->Update();

    /*if (CheckCollision(dynamic_cast<SDLGameObject*>(gameObjects[0]),
        dynamic_cast<SDLGameObject*>(gameObjects[1]))) {
        Game::Instance()->GetStateMachine()->PushState(new GameOverState());
    } else if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_ESCAPE)) {
        Game::Instance()->GetStateMachine()->PushState(new PauseState());
    }*/

    LOG_DBG("[PlayState][Update] Updated the play state");
}

/*bool PlayState::CheckCollision(SDLGameObject *object1, SDLGameObject *object2)
{
    LOG_DBG("[PlayState][CheckCollision] Checking the collision");

    uint32_t leftA, leftB;
    uint32_t rightA, rightB;
    uint32_t topA, topB;
    uint32_t bottomA, bottomB;

    leftA = object1->GetPosition().GetX();
    rightA = object1->GetPosition().GetX() + object1->GetWidth();
    topA = object1->GetPosition().GetY();
    bottomA = object1->GetPosition().GetY() + object1->GetHeight();

    leftB = object2->GetPosition().GetX();
    rightB = object2->GetPosition().GetX() + object2->GetWidth();
    topB = object2->GetPosition().GetY();
    bottomB = object2->GetPosition().GetY() + object2->GetHeight();

    if( bottomA <= topB ) {
        return false;
    } 
    if( topA >= bottomB ) {
        return false;
    }
    if( rightA <= leftB ) {
        return false;
    }
    if( leftA >= rightB ) {
        return false;
    }

    return true;
    LOG_DBG("[PlayState][CheckCollision] Checked the collision");
}*/
