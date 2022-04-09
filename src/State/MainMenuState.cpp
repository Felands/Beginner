#include <iostream>
#include <string>

#include "MainMenuState.h"
#include "StateParser.h"
#include "Resource.h"
#include "Game.h"
#include "PlayState.h"

const std::string MainMenuState::s_menuId = "MENU";

void MainMenuState::Update()
{
    for(int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->Update();
    }
}

void MainMenuState::Render()
{
    for(int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->Draw();
    }
}

bool MainMenuState::OnEnter()
{
    // parse the state
    StateParser stateParser;
    stateParser.ParseState("test.xml", s_menuId, &m_gameObjects, &m_textureIDList);
    m_callbacks.push_back(0); //pushback 0 callbackID start from 1
    m_callbacks.push_back(s_MenuToPlay);
    m_callbacks.push_back(s_ExitFromMenu);
    // set the callbacks for menu items
    SetCallbacks(m_callbacks);
    std::cout << "entering MenuState\n";
    return true;
}

bool MainMenuState::OnExit()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->Clean();
    }
    m_gameObjects.clear();

    // clear the texture manager
    for(int i = 0; i < m_textureIDList.size(); i++) {
        TextureManager::Instance()->ClearFromTextureMap(m_textureIDList[i]);
    }

    std::cout << "Exiting MainMenuState\n";

    return true;
}

void MainMenuState::s_ExitFromMenu()
{
    Game::Instance()->Quit();
}

void MainMenuState::s_MenuToPlay()
{
    Game::Instance()->GetStateMachine()->ChangeState(new PlayState());
}

void MainMenuState::SetCallbacks(const std::vector<Callback>& callbacks)
{
    for(int i = 0; i < m_gameObjects.size(); i++) {
        if(dynamic_cast<MenuButton*>(m_gameObjects[i])) {
            MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
            pButton->SetCallback(callbacks[pButton->GetCallbackID()]);
        }
    }
}

