#include <vector>

#include "SDL.h"
#include "SDL_image.h"

#include "Game.h"
#include "Resource.h"
#include "InputHandler.h"
#include "log.h"
#include "MainMenuState.h"
#include "GameObjectFactory.h"
#include "BetweenLevelState.h"

Game *Game::instance = nullptr;

bool Game::Init(const char *title, int32_t xpos, int32_t ypos, uint32_t height_, uint32_t width_, bool isFullScreen)
{
    LOG_DBG("[Game][Init] Initting the game");

    width = width_;
    height = height_;
    isRunning = true;
    scrollSpeed = 0;
    playerLives = 3;
    levelComplete = false;
    currentLevel = 1;

    // 初始化SDL系统，并创建窗口和渲染器
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        LOG_DBG("[Game][Init] The SDL system is initialized successfully");
        window = SDL_CreateWindow(title, xpos, ypos, width, height,
            isFullScreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN);
        if(window != nullptr) {
            LOG_DBG("[Game][Init] The window is created successfully");
            renderer = SDL_CreateRenderer(window, -1, 0);
            if (renderer != nullptr) {
                LOG_DBG("[Game][Init] The renderer is created successfully");
            } else {
                LOG_ERR("[Game][Init] The renderer creation failed");
                return false;
            }
        } else {
            LOG_ERR("[Game][Init] The window creation failed");
            return false;
        }
    } else {
        LOG_ERR("[Game][Init] The SDL system initialization failed");
        return false;
    }

    // 初始化SDL_IMG
    int flag = IMG_INIT_PNG;
    int initted = IMG_Init(flag);
    if ((flag & initted) != false) {
        LOG_DBG("[Game][Init] The IMG is initialized successfully");
    } else {
        LOG_ERR("[Game][Init] The IMG initialization failed");
        return false;
    }

    // object创建器初始化
    GameObjectFactory::Instance()-> RegisterType();

    // 进入主菜单界面
    gameStateMachine = new GameStateMachine();
    gameStateMachine->ChangeState(new MainMenuState());

    LOG_DBG("[Game][Init] Initted the game");
    return true;
}

void Game::HandleEvents()
{
    LOG_DBG("[Game][HandleEvents] Handling events of the game");

    InputHandler::Instance()->Update();

    LOG_DBG("[Game][HandleEvents] Handled events of the game");
}

void Game::Update()
{
    LOG_DBG("[Game][Update] Updating the game");

    gameStateMachine->Update();

    LOG_DBG("[Game][Update] Updated the game");
}

void Game::Render()
{
    LOG_DBG("[Game][Render] Rendering the game");

    SDL_RenderClear(renderer);
    gameStateMachine->Render();
    SDL_RenderPresent(renderer);

    LOG_DBG("[Game][Render] Rendered the game");
}

void Game::Clean()
{
    LOG_DBG("[Game][Clean] Cleaning the game");

    gameStateMachine->Clean();
    Resource::Instance()->Clean();
    InputHandler::Instance()->Clean();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    SDL_Quit();
    delete instance;

    LOG_DBG("[Game][Clean] Cleaned the game");
}

void Game::SetCurrentLevel(uint32_t currentLevel)
{
    this->currentLevel = currentLevel;
    // gameStateMachine->ChangeState(new BetweenLevelState());
    levelComplete = false;
}
