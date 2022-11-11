#include <string>

#include "MainMenuState.h"
#include "StateParser.h"
#include "MenuButton.h"
#include "Game.h"
#include "Resource.h"
#include "InputHandler.h"
#include "PlayState.h"
#include "log.h"

const std::string MainMenuState::menuId = "MENU";

void MainMenuState::Update()
{
    LOG_DBG("[MainMenuState][Update] Updating the main menu state");

    for(size_t i = 0; i < gameObjects.size(); i++) {
        gameObjects[i]->Update();
    }

    LOG_DBG("[MainMenuState][Update] Updated the main menu state");
}

void MainMenuState::Render()
{
    LOG_DBG("[MainMenuState][Render] Rendering the main menu state");

    for(size_t i = 0; i < gameObjects.size(); i++) {
        gameObjects[i]->Draw();
    }

    LOG_DBG("[MainMenuState][Render] Rendered the main menu state");
}

bool MainMenuState::OnEnter()
{
    LOG_DBG("[MainMenuState][OnEnter] Entering the main menu state");

    StateParser stateParser;
    stateParser.ParseState(StateParser::document, menuId, &gameObjects, &textureIdList);

    callbacks.push_back(0);
    callbacks.push_back(MenuToPlay);
    callbacks.push_back(ExitFromMenu);
    SetCallbacks(callbacks);

    Resource::Instance()->Play("main_title", 1);

    LOG_DBG("[MainMenuState][OnEnter] Entered the main menu state");
    return true;
}

bool MainMenuState::OnExit()
{
    LOG_DBG("[MainMenuState][OnExit] Exiting the main menu state");

    InputHandler::Instance()->Reset();

    for(size_t i = 0; i < gameObjects.size(); i++) {
        gameObjects[i]->Clean();
        delete gameObjects[i];
    }

    for(int i = 0; i < textureIdList.size(); i++) {
        Resource::Instance()->ClearOneTexture(textureIdList[i]);
    }

    //Mix_FadeOutMusic(800);

    LOG_DBG("[MainMenuState][OnExit] Exited the main menu state");
    return true;
}

void MainMenuState::ExitFromMenu()
{
    LOG_DBG("[MainMenuState][ExitFromMenu] Exiting from the main menu state");

    Game::Instance()->Quit();

    LOG_DBG("[MainMenuState][ExitFromMenu] Exited from the main menu state");
}

void MainMenuState::MenuToPlay()
{
    LOG_DBG("[MainMenuState][ExitFromMenu] From the main menu to the play state");

    Game::Instance()->GetStateMachine()->PushState(new PlayState());

    LOG_DBG("[MainMenuState][ExitFromMenu] From the main menu to the play state");
}

void MainMenuState::SetCallbacks(const std::vector<Callback> &callbacks)
{
    LOG_DBG("[MainMenuState][SetCallbacks] Setting call-backs of menu butttons");

    for(int i = 0; i < gameObjects.size(); i++) {
        if(dynamic_cast<MenuButton*>(gameObjects[i])) {
            MenuButton *button = dynamic_cast<MenuButton*>(gameObjects[i]);
            button->SetCallback(callbacks[button->GetCallbackId()]);
        }
    }

    LOG_DBG("[MainMenuState][SetCallbacks] Set call-backs of menu butttons");
}
