#include <iostream>
#include <string>

#include "GameOverState.h"
#include "Game.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "StateParser.h"
#include "Resource.h"

const std::string GameOverState::s_gameOverId = "GAMEOVER";

GameOverState::~GameOverState()
{}

void GameOverState::s_GameOverToMain()
{
    Game::Instance()->GetStateMachine()->ChangeState(new MainMenuState());
}

void GameOverState::s_RestartPlay()
{
    Game::Instance()->GetStateMachine()->ChangeState(new PlayState());
}

bool GameOverState::OnEnter()
{
    // parse the state
    StateParser stateParser;
    stateParser.ParseState("test.xml", s_gameOverId, &m_gameObjects, &m_textureIDList);
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_GameOverToMain);
    m_callbacks.push_back(s_RestartPlay);
    // set the callbacks for menu items
    SetCallbacks(m_callbacks);
    std::cout << "entering PauseState\n";
    return true;
}

void GameOverState::Update()
{}

void GameOverState::Render()
{}

bool GameOverState::OnExit()
{
    for(int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->Clean();
    }
    m_gameObjects.clear();

    // clear the texture manager
    for(int i = 0; i < m_textureIDList.size(); i++) {
        TextureManager::Instance()->ClearFromTextureMap(m_textureIDList[i]);
    }

    std::cout << "Exiting PauseState\n";

    return true;
}
