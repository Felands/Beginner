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

GameOverState::~GameOverState()
{}

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
    std::cout << "Entering PauseState\n";

    return true;
}

void GameOverState::Update()
{}

void GameOverState::Render()
{}

bool GameOverState::OnExit()
{return true;}
