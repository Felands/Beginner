#include <stdint.h>

#include "SDL.h"

#include "Game.h"

const uint32_t FPS = 30;  
const uint32_t DELAY_TIME = 1000.0f / FPS;
const char* WINDOW_TITLE = "DungeonRush";
const uint32_t WINDOW_X_POS = 100;
const uint32_t WINDOW_Y_POS = 100;
const uint32_t WINDOW_WIDTH = 640;
const uint32_t WINDOW_HEIGHT = 640;
const int32_t OK = 0;
const int32_t ERR = 1;

int main(int argc, char **args)
{
    if (!Game::Instance()->Init(WINDOW_TITLE, WINDOW_X_POS, WINDOW_Y_POS, WINDOW_WIDTH, WINDOW_HEIGHT, false)) {
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