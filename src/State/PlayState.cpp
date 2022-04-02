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

const std::string PlayState::s_playId = "PLAY";

PlayState::~PlayState()
{}

void PlayState::Render()
{
    for(int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->Draw();
    }
}

bool PlayState::OnExit()
{
    for(int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->Clean();
    }
    m_gameObjects.clear();
    std::cout << "Exiting PlayState\n";
    return true;
}

bool PlayState::OnEnter()
{
    LoaderParams *params = new LoaderParams(500, 100, "elf_f_idle_anim");
    GameObject* elf_f = new Player(params);
    delete params;
    params = new LoaderParams(500, 500, "elf_m_idle_anim");
    GameObject* elf_m = new Player(params);
    delete params;

    m_gameObjects.push_back(elf_f);
    m_gameObjects.push_back(elf_m);

    std::cout << "Entering PlayState\n";

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

    /*if(CheckCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[0]),
        dynamic_cast<SDLGameObject*>(m_gameObjects[1]))) {
        Game::Instance()->GetStateMachine()->PushState(new GameOverState());
    }*/
}