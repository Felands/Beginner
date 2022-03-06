#include <iostream>
#include <string>

#include "GameObject.h"
#include "MenuState.h"
#include "Resource.h"
#include "Game.h"
#include "MenuBotton.h"
#include "PlayState.h"

const std::string MenuState::s_menuId = "MENU";

void MenuState::Update()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->Update();
    }
}

void MenuState::Render()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->Draw();
    }
}

bool MenuState::OnEnter()
{
    if(!TextureManager::Instance()->Load("assets/button.png", "playbutton", Game::Instance()->GetRenderer()))
    {
        return false;
    }
    if(!TextureManager::Instance()->Load("assets/exit.png", "exitbutton", Game::Instance()->GetRenderer()))
    {
        return false;
    }

    LoaderParams *params = new LoaderParams(100, 100, 400, 100, "playbutton");
    GameObject* button1 = new MenuButton(params, nullptr);
    delete params;
    params = new LoaderParams(100, 300, 400, 100, "exitbutton");
    GameObject* button2 = new MenuButton(params, nullptr);
    delete params;

    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);

    std::cout << "Entering MenuState\n";

    return true;
}

bool MenuState::OnExit()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->Clean();
    }
    m_gameObjects.clear();

    TextureManager::Instance()->ClearFromTextureMap("playbutton");
    TextureManager::Instance()->ClearFromTextureMap("exitbutton");

    std::cout << "Exiting MenuState\n";

    return true;
}

void MenuState::s_ExitFromMenu()
{
    Game::Instance()->Quit();
}

void MenuState::s_MenuToPlay()
{
    Game::Instance()->GetStateMachine()->ChangeState(new PlayState());
}