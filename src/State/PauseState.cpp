#include <iostream>
#include <string>

#include "PauseState.h"
#include "Game.h"
#include "MenuState.h"
#include "LoaderParams.h"
#include "Resource.h"
#include "MenuBotton.h"
#include "InputHandler.h"

const std::string PauseState::s_pauseId = "PAUSE";

void PauseState::s_PauseToMain()
{
    Game::Instance()->GetStateMachine()->ChangeState(new MenuState());
}

void PauseState::s_ResumePlay()
{
    Game::Instance()->GetStateMachine()->PopState();
}

void PauseState::Update()
{
    for(int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->Update();
    }
}

void PauseState::Render()
{
    for(int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->Draw();
    }
}

bool PauseState::OnEnter()
{
    /*if(!TextureManager::Instance()->Load("assets/resume.png", "resumebutton", Game::Instance()->GetRenderer())) {
        return false;
    }
    if(!TextureManager::Instance()->Load("assets/main.png", "mainbutton", Game::Instance()->GetRenderer())) {
        return false;
    }

    LoaderParams *params = new LoaderParams(200, 100, 200, 80, "mainbutton");
    GameObject* button1 = new MenuButton(params, s_PauseToMain);
    delete params;
    params = new LoaderParams(200, 300, 200, 80, "resumebutton");
    GameObject* button2 = new MenuButton(params, s_ResumePlay);
    delete params;
    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);

    std::cout << "Entering PauseState\n";*/

    return true;
}

bool PauseState::OnExit()
{
    for(int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->Clean();
    }
    m_gameObjects.clear();

    TextureManager::Instance()->ClearFromTextureMap("resumebutton");
    TextureManager::Instance()->ClearFromTextureMap("mainbutton");

    InputHandler::Instance()->Reset();

    std::cout << "Exiting PauseState\n";

    return true;
}
