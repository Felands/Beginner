#include <iostream>
#include <string>

#include "GameOverState.h"
#include "Game.h"
#include "Resource.h"
#include "InputHandler.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "StateParser.h"
#include "MenuButton.h"

const std::string GameOverState::gameOverId = "GAMEOVER";

void GameOverState::GameOverToMain()
{
    Game::Instance()->GetStateMachine()->ChangeState(new MainMenuState());
}

void GameOverState::RestartPlay()
{
    Game::Instance()->GetStateMachine()->ChangeState(new PlayState());
}

bool GameOverState::OnEnter()
{
    StateParser stateParser;
    stateParser.ParseState(gameOverId, &gameObjects);

    callbacks.push_back(0);
    callbacks.push_back(GameOverToMain);
    callbacks.push_back(RestartPlay);
    SetCallbacks(callbacks);

    std::cout << "Entering PauseState.\n";
    return true;
}

void GameOverState::Update()
{
    for(size_t i = 0; i < gameObjects.size(); i++) {
        gameObjects[i]->Update();
    }
}

void GameOverState::Render()
{
    for(size_t i = 0; i < gameObjects.size(); i++) {
        gameObjects[i]->Draw();
    }
}

bool GameOverState::OnExit()
{
    InputHandler::Instance()->Reset();

    for(int i = 0; i < gameObjects.size(); i++) {
        gameObjects[i]->Clean();
    }
    Resource::Instance()->Clean();

    std::cout << "Exiting PauseState\n";
    return true;
}

void GameOverState::SetCallbacks(const std::vector<Callback> &callbacks)
{
    for(int i = 0; i < gameObjects.size(); i++) {
        if(dynamic_cast<MenuButton*>(gameObjects[i])) {
            MenuButton *button = dynamic_cast<MenuButton*>(gameObjects[i]);
            button->SetCallback(callbacks[button->GetCallbackId()]);
        }
    }
}
