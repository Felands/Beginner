#include <iostream>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"

#include "Game.h"
#include "Resource.h"
#include "InputHandler.h"
#include "Player.h"
#include "Enemy.h"

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

    TextureManager::Instance()->LoadAllResource();

    for (uint32_t i = 0; players[i]; ++i) {
        m_gameObjects[players[i]] = new Player(players[i]);
        m_gameObjects[players[i]]->Load();
    }

    for (uint32_t i = 0; enemies[i]; ++i) {
        m_gameObjects[enemies[i]] = new Enemy(enemies[i]);
        m_gameObjects[enemies[i]]->Load();
    }

    m_ui.push_back(new Ui("title"));

    return true;
}

void Game::Render()
{
    SDL_RenderClear(m_pRenderer);
    for(auto object : m_gameObjects) {
        object.second->Draw();
    }
    for(auto ui : m_ui) {
        ui->Draw();
    }
    SDL_RenderPresent(m_pRenderer);
}

void Game::HandleEvents()
{
    InputHandler::Instance()->Update();
    for(auto object : m_gameObjects) {
        object.second->HandleInput();
    }
}

void Game::Update()
{
    for(auto object : m_gameObjects) {
        object.second->Update();
    }
    for(auto ui : m_ui) {
        ui->Update();
    }
}

void Game::Clean()
{
    std::cout << "Cleaning game\n";
    for(auto object : m_gameObjects) {
        object.second->Clean();
        delete object.second;
    }
    for(auto ui : m_ui) {
        delete ui;
    }
    TextureManager::Instance()->Clean();
    InputHandler::Instance()->Clean();
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    IMG_Quit();
    SDL_Quit();
}
