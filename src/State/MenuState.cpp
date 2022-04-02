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
    LoaderParams *params = new LoaderParams(100, 100, "login_button");
    GameObject* login = new MenuButton(params, s_MenuToPlay);
    delete params;
    params = new LoaderParams(100, 300, "exit_button");
    GameObject* exit = new MenuButton(params, s_ExitFromMenu);
    delete params;

    m_gameObjects.push_back(login);
    m_gameObjects.push_back(exit);

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
