#include <iostream>
#include <string>

#include "PlayState.h"
#include "Resource.h"
#include "Game.h"
#include "LoaderParams.h"
#include "GameObject.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "Player.h"
#include "Enemy.h"
#include "SDLGameObject.h"
#include "GameOverState.h"
#include "StateParser.h"
#include "LevelParser.h"

const std::string PlayState::s_playId = "PLAY";

PlayState::~PlayState()
{}

void PlayState::Render()
{
    m_pLevel->render();
}

bool PlayState::OnExit()
{
    for(int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->Clean();
    }
    m_gameObjects.clear();
    // clear the texture manager
    for(int i = 0; i < m_textureIDList.size(); i++) {
        TextureManager::Instance()->ClearFromTextureMap(m_textureIDList[i]);
    }
    std::cout << "Exiting PlayState\n";
    return true;
}

bool PlayState::OnEnter()
{
    LevelParser levelParser;
    m_pLevel = levelParser.parseLevel("assets/map1.tmx");
    std::cout << "entering PlayState\n";
    return true;
}


bool PlayState::CheckCollision(SDLGameObject* p1, SDLGameObject* p2)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = p1->GetPosition().GetX();
    rightA = p1->GetPosition().GetX() + TextureManager::Instance()->GetInfoMap(p1->GetName())->size.GetX();
    topA = p1->GetPosition().GetY();
    bottomA = p1->GetPosition().GetY() + TextureManager::Instance()->GetInfoMap(p1->GetName())->size.GetY();

    leftB = p2->GetPosition().GetX();
    rightB = p2->GetPosition().GetX() + TextureManager::Instance()->GetInfoMap(p2->GetName())->size.GetX();
    topB = p2->GetPosition().GetY();
    bottomB = p2->GetPosition().GetY() + TextureManager::Instance()->GetInfoMap(p2->GetName())->size.GetY();

    if( bottomA <= topB ) {
        return false;
    } 

    if( topA >= bottomB ) {
        return false;
    }

    if( rightA <= leftB ) {
        return false;
    }

    if( leftA >= rightB ) {
        return false;
    }

    return true;
}

void PlayState::Update()
{
    if(InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_ESCAPE)) {
        Game::Instance()->GetStateMachine()->PushState(new PauseState());
    }

    for(int i = 0; i < m_gameObjects.size(); i++){
        m_gameObjects[i]->Update();
    }

    m_pLevel->update();

    /*if(CheckCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[0]),
        dynamic_cast<SDLGameObject*>(m_gameObjects[1]))) {
        Game::Instance()->GetStateMachine()->PushState(new GameOverState());
    }*/
}