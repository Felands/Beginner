#include <iostream>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"

#include "Game.h"
#include "Resource.h"
#include "LoaderParams.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "InputHandler.h"

Game* Game::s_pInstance = nullptr;

bool Game::Init(const char* title, int xpos, int ypos, int height, int width, bool fullScreen)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL init success\n";
        m_pWindow = SDL_CreateWindow(title, xpos, ypos, height, width,
            fullScreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN);
        if(m_pWindow != nullptr) {
            std::cout << "Window init success\n";
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
            if (m_pRenderer != nullptr) {
                std::cout << "Render init success\n";
            } else {
                std::cout << "Render init fail\n";
                return false;
            }
        } else {
            std::cout << "Window init fail\n";
            return false;
        }
    } else {
        std::cout << "SDL init fail\n";
        return false;
    }

    int flag = IMG_INIT_PNG;
    int initted = IMG_Init(flag);
    if ((flag & initted) != false) {
        std::cout << "IMG init success\n";
    } else {
        std::cout << "IMG init fail\n";
        return false;
    }

    TextureManager::Instance()->Load("assets/drawable/halo_explosion1.PNG", "halo_explosion1",
        Instance()->GetRenderer());
    TextureManager::Instance()->Load("assets/drawable/halo_explosion2.PNG", "halo_explosion2",
        Instance()->GetRenderer());

    LoaderParams *params = nullptr;
    params = new LoaderParams(100, 100, 48, 48, "halo_explosion1");
    m_gameObjects.push_back(new Player(params));
    delete params;
    params = new LoaderParams(100, 150, 16, 16, "halo_explosion2");
    m_gameObjects.push_back(new Enemy(params));
    delete params;

    return true;
}

void Game::Render()
{
    SDL_RenderClear(m_pRenderer);
    for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++) {
        m_gameObjects[i]->Draw();
    }
    SDL_RenderPresent(m_pRenderer);
}

void Game::HandleEvents()
{
    InputHandler::Instance()->Update();
}

void Game::Update()
{
    for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++) {
        m_gameObjects[i]->Update();
    }
}

void Game::Clean()
{
    std::cout << "Cleaning game\n";
    for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); ++i) {
        m_gameObjects[i]->Clean();
    }
    InputHandler::Instance()->Clean();
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    IMG_Quit();
    SDL_Quit();
}