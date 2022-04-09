#include <iostream>
#include <string>

#include "PlayState.h"
#include "Resource.h"
#include "LevelParser.h"
#include "InputHandler.h"
#include "Game.h"
#include "GameOverState.h"
#include "PauseState.h"

const std::string PlayState::s_playId = "PLAY";

PlayState::~PlayState()
{}

void PlayState::Render()
{
    m_pLevel->Render();
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
    m_pLevel = levelParser.ParseLevel("assets/map1.tmx");
    std::cout << "entering PlayState\n";
    return true;
}

bool PlayState::CheckCollision(SDLGameObject* p1, SDLGameObject* p2)
{
    uint32_t leftA, leftB;
    uint32_t rightA, rightB;
    uint32_t topA, topB;
    uint32_t bottomA, bottomB;

    leftA = p1->GetPosition().GetX();
    rightA = p1->GetPosition().GetX() + p1->GetWidth();
    topA = p1->GetPosition().GetY();
    bottomA = p1->GetPosition().GetY() + p1->GetHeight();

    leftB = p2->GetPosition().GetX();
    rightB = p2->GetPosition().GetX() + p2->GetWidth();
    topB = p2->GetPosition().GetY();
    bottomB = p2->GetPosition().GetY() + p2->GetHeight();

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

    m_pLevel->Update();

    if(CheckCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[0]),
        dynamic_cast<SDLGameObject*>(m_gameObjects[1]))) {
        Game::Instance()->GetStateMachine()->PushState(new GameOverState());
    }
}
