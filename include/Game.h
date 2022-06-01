#ifndef GAME_H
#define GAME_H

#include <vector>

#include "SDL.h"

#include "GameStateMachine.h"

class Game
{
public:
    static Game *Instance()
    {
        if(instance == nullptr) {
            instance = new Game();
        }
        return instance;
    }

    uint32_t GetGameScreenWidth() const 
    { 
        return width; 
    }

    uint32_t GetGameScreenHeight() const 
    { 
        return height; 
    }

    float GetScrollSpeed() const
    {
        return scrollSpeed;
    }

    GameStateMachine *GetStateMachine() const
    {
        return gameStateMachine;
    }

    SDL_Renderer *GetRenderer() const
    {
        return renderer;
    }

    bool IsGameRunning()
    {
        return isRunning;
    }

    void Quit()
    {
        isRunning = false;
    }

    bool Init(const char *title, int32_t xPos, int32_t yPos, uint32_t width_, uint32_t height_, bool isFullScreen);

    void HandleEvents();

    void Update();

    void Render();

    void Clean();

private:
    Game()
    {}

    ~Game()
    {}

    static Game *instance;
    bool isRunning;
    uint32_t width;
    uint32_t height;
    float scrollSpeed;
    GameStateMachine *gameStateMachine;
    SDL_Window *window;
    SDL_Renderer *renderer;
};

#endif