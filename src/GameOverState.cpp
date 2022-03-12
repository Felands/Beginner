#include <iostream>
#include <string>

#include "GameOverState.h"
#include "Game.h"
#include "MenuState.h"
#include "GameObject.h"
#include "Resource.h"
#include "PlayState.h"
#include "LoaderParams.h"
#include "MenuBotton.h"
#include "AnimatedGraphic.h"

const std::string GameOverState::s_gameOverId = "GAMEOVER";

void GameOverState::s_GameOverToMain()
{
    Game::Instance()->GetStateMachine()->ChangeState(new MenuState());
}

void GameOverState::s_RestartPlay()
{
    Game::Instance()->GetStateMachine()->ChangeState(new PlayState());
}

bool GameOverState::OnEnter()
{
    if(!TextureManager::Instance()->Load("assets/gameover.png", "gameovertext", Game::Instance()->GetRenderer())) {
        return false;
    }
    if(!TextureManager::Instance()->Load("assets/main.png", "mainbutton", Game::Instance()->GetRenderer())) {
        return false;
    }
    if(!TextureManager::Instance()->Load("assets/restart.png", "restartbutton", Game::Instance()->GetRenderer())) {
        return false;
    }

    LoaderParams *params = new LoaderParams(200, 100, 190, 30, "gameovertext");
    GameObject* gameOverText = new AnimatedGraphic(params, 2);
    delete params;
    params = new LoaderParams(200, 200, 200, 80, "mainbutton");
    GameObject* button1 = new MenuButton(params, s_GameOverToMain);
    delete params;
    params = new LoaderParams(200, 300, 200, 80, "restartbutton");
    GameObject* button2 = new MenuButton(params, s_RestartPlay);
    delete params;

    m_gameObjects.push_back(gameOverText);
    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);

    std::cout << "Entering PauseState\n";

    return true;
}

bool GameOverState::onEnter()
{
 // parse the state
 StateParser stateParser;
 stateParser.parseState("test.xml", s_gameOverID, &m_gameObjects, 
 &m_textureIDList);
 m_callbacks.push_back(0);
 m_callbacks.push_back(s_gameOverToMain);
 m_callbacks.push_back(s_restartPlay);
 // set the callbacks for menu items
 setCallbacks(m_callbacks);
 std::cout << "entering PauseState\n";
 return true;
}