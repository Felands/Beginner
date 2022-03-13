#include <iostream>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"

#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
/*#include "LoaderParams.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"*/
/*#include "MenuState.h"
#include "PlayState.h"
#include "MenuBotton.h"*/

Game* Game::s_pInstance = nullptr;

bool Game::Init(const char* title, int32_t xpos, int32_t ypos, uint32_t height, uint32_t width, bool fullScreen)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL init success.\n";
        m_pWindow = SDL_CreateWindow(title, xpos, ypos, height, width,
            fullScreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN);
        if(m_pWindow != nullptr) {
            std::cout << "Window init success.\n";
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
            if (m_pRenderer != nullptr) {
                std::cout << "Render init success.\n";
            } else {
                std::cout << "Render init fail.\n";
                return false;
            }
        } else {
            std::cout << "Window init fail.\n";
            return false;
        }
    } else {
        std::cout << "SDL init fail.\n";
        return false;
    }

    uint32_t flag = IMG_INIT_PNG;
    int32_t initted = IMG_Init(flag);
    if ((flag & initted) != false) {
        std::cout << "SDL IMG init success.\n";
    } else {
        std::cout << "SDL IMG init fail.\n";
        return false;
    }

    TextureManager::Instance()->Load("assets/drawable/halo_explosion1.PNG", "halo_explosion1",
        Instance()->GetRenderer());
    TextureManager::Instance()->Load("assets/drawable/halo_explosion2.PNG", "halo_explosion2",
        Instance()->GetRenderer());

    /*m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->ChangeState(new MenuState());*/

    /*LoaderParams *params = nullptr;*/
    /*params = new LoaderParams(100, 100, 400, 100, "playbutton");
    m_menuObj1 = new MenuButton(params, MenuState::s_MenuToPlay);
    delete params;
    params = new LoaderParams(100, 300, 400, 100, "exitbutton");
    m_menuObj2 = new MenuButton(params, MenuState::s_ExitFromMenu);
    delete params;*/

    /*params = new LoaderParams(100, 100, 48, 48, "halo_explosion1");
    m_gameObjects.push_back(new Player(params));
    delete params;
    params = new LoaderParams(100, 150, 16, 16, "halo_explosion2");
    m_gameObjects.push_back(new Enemy(params));
    delete params;*/

    /*GameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());

    GameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
    GameObjectFactory::Instance()->registerType("Enemy", new EnemyCreator());

    GameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());*/

    return true;
}

void Game::Render()
{
    SDL_RenderClear(m_pRenderer);
    /*for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++) {
        m_gameObjects[i]->Draw();
    }*/
    /*m_pGameStateMachine->Render();*/
    SDL_RenderPresent(m_pRenderer);
}

void Game::HandleEvents()
{
    InputHandler::Instance()->Update();

    if(InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_RETURN)) {
        /*m_pGameStateMachine->ChangeState(new PlayState());*/
    }
}

void Game::Update()
{
    /*for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++) {
        m_gameObjects[i]->Update();
    }*/

    /*m_pGameStateMachine->Update();*/

    /*for (std::vector<PlayerBullet*>::iterator p_it = m_playerBullets.begin(); p_it != m_playerBullets.end();)
    {
        if((*p_it)->getPosition().getX() < 0 || (*p_it)->getPosition().getX() >TheGame::Instance()->getGameWidth() ||
            (*p_it)->getPosition().getY() < 0 || (*p_it)->getPosition().getY() >TheGame::Instance()->getGameHeight() || 
            (*p_it)->dead())// if off screen or dead
        {
            delete * p_it; // delete the bullet
            p_it = m_playerBullets.erase(p_it); //remove
        } else// continue to update and loop
        {
            (*p_it)->update();
            ++p_it;
        }
    }*/
}

void Game::Clean()
{
    std::cout << "Cleaning game...\n";
    /*for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); ++i) {
        m_gameObjects[i]->Clean();
    }*/
    /*m_pGameStateMachine->Clean();*/

    TextureManager::Instance()->Clean();
    /*InputHandler::Instance()->Clean();*/

    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    IMG_Quit();
    SDL_Quit();
}

void Game::SetCurrentLevel(uint32_t currentLevel)
{
    /*m_currentLevel = currentLevel;
    m_pGameStateMachine->ChangeState(new BetweenLevelState());
    m_bLevelComplete = false;*/
}
