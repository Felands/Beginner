#include <stdint.h>

#include "SDL.h"

#include "ErrorCode.h"
#include "Game.h"

// 窗口参数
const char* WINDOW_TITLE = "DungeonRush";
const uint32_t WINDOW_X_POS = 100;
const uint32_t WINDOW_Y_POS = 100;
const uint32_t WINDOW_HEIGHT = 480;
const uint32_t WINDOW_WIDTH = 600;
// 刷新频率
const uint32_t FPS = 30;
const uint32_t DELAY_TIME = 1000.0f / FPS;

int main(int argc, char **args)
{
    if (!Game::Instance()->Init(WINDOW_TITLE, WINDOW_X_POS, WINDOW_Y_POS, WINDOW_HEIGHT, WINDOW_WIDTH, false)) {
        return ERR;
    }

    uint32_t frameStart;
    uint32_t frameTime;
    while (Game::Instance()->IsGameRunning()) {
        frameStart = SDL_GetTicks();

        Game::Instance()->HandleEvents();
        Game::Instance()->Update();
        Game::Instance()->Render();

        frameTime = SDL_GetTicks() - frameStart;
        if(frameTime< DELAY_TIME) {
            SDL_Delay((uint32_t)(DELAY_TIME - frameTime));
        }
    }

    Game::Instance()->Clean();

    return OK;
}