#include <stdint.h>

#include "SDL.h"

#include "Game.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char **args)
{
    uint32_t frameStart;
    uint32_t frameTime;

    if (!Game::Instance()->Init("Chapter 1", 100, 100, 640, 580, false)) {
        return 1;
    }

    while (Game::Instance()->Running()) {
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

    return 0;
}