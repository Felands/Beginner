#include <iostream>
#include <string>

#include "PauseState.h"
#include "Game.h"
#include "MainMenuState.h"
#include "StateParser.h"
#include "InputHandler.h"
#include "Resource.h"
#include "MenuButton.h"

bool PauseState::OnEnter()
{
    //StateParser stateParser;
    //stateParser.ParseState(pauseId, &gameObjects);  

    callbacks.push_back(0);
    callbacks.push_back(PauseToMain);
    callbacks.push_back(ResumePlay);
    SetCallbacks(callbacks);

    std::cout << "Entering PauseState.\n";
    return true;
}

bool PauseState::OnExit()
{
    InputHandler::Instance()->Reset();

    for(int i = 0; i < gameObjects.size(); i++) {
        gameObjects[i]->Clean();
    }
    Resource::Instance()->Clean();

    std::cout << "Exiting PauseState\n";
    return true;
}

void PauseState::PauseToMain()
{
    Game::Instance()->GetStateMachine()->ChangeState(new MainMenuState());
}

void PauseState::ResumePlay()
{
    Game::Instance()->GetStateMachine()->PopState();
}

void PauseState::Update()
{
    for(size_t i = 0; i < gameObjects.size(); i++) {
        gameObjects[i]->Update();
    }
}

void PauseState::Render()
{
    for(size_t i = 0; i < gameObjects.size(); i++) {
        gameObjects[i]->Draw();
    }
}

void PauseState::SetCallbacks(const std::vector<Callback>& callbacks)
{
    for(int i = 0; i < gameObjects.size(); i++) {
        if(dynamic_cast<MenuButton*>(gameObjects[i])) {
            MenuButton *button = dynamic_cast<MenuButton*>(gameObjects[i]);
            button->SetCallback(callbacks[button->GetCallbackId()]);
        }
    }
}
