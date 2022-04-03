#include <iostream>
#include <string>

#include "PauseState.h"
#include "Game.h"
#include "MainMenuState.h"
#include "LoaderParams.h"
#include "Resource.h"
#include "MenuBotton.h"
#include "InputHandler.h"
#include "StateParser.h"

const std::string PauseState::s_pauseId = "PAUSE";

void PauseState::s_PauseToMain()
{
    Game::Instance()->GetStateMachine()->ChangeState(new MainMenuState());
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
    StateParser stateParser;
    stateParser.parseState("test.xml", s_pauseId, &m_gameObjects, &m_textureIDList);
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_PauseToMain);
    m_callbacks.push_back(s_ResumePlay);
    setCallbacks(m_callbacks);
    std::cout << "entering PauseState\n";
    return true;
}

bool PauseState::OnExit()
{
    for(int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->Clean();
    }
    m_gameObjects.clear();

    InputHandler::Instance()->Reset();

    // clear the texture manager
    for(int i = 0; i < m_textureIDList.size(); i++) {
        TextureManager::Instance()->ClearFromTextureMap(m_textureIDList[i]);
    }

    std::cout << "Exiting PauseState\n";

    return true;
}

void PauseState::setCallbacks(const std::vector<Callback>& callbacks)
{
    for(int i = 0; i < m_gameObjects.size(); i++) {
        if(dynamic_cast<MenuButton*>(m_gameObjects[i])) {
            MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}

