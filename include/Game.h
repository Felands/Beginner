#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include <vector>

#include "SDL.h"

#include "GameStateMachine.h"

class Game
{
private:
    Game()
    {}

    ~Game()
    {}

public:
    // 获取Game类的成员：实例
    static Game *Instance()
    {
        if(instance == nullptr) {
            instance = new Game();
        }
        return instance;
    }
    // 获取Game类的成员：窗口的参数
    uint32_t GetGameScreenWidth() const
    {
        return width;
    }
    uint32_t GetGameScreenHeight() const
    { 
        return height;
    }
    // 获取Game类的成员：渲染器
    SDL_Renderer *GetRenderer() const
    {
        return renderer;
    }
    // 获取Game类的成员：状态机及状态参数
    bool IsGameRunning() const
    {
        return isRunning;
    }
    GameStateMachine *GetStateMachine() const
    {
        return gameStateMachine;
    }

    // 实现Game类的功能：主流程
    bool Init(const char *title, int32_t xPos, int32_t yPos, uint32_t width_, uint32_t height_, bool isFullScreen);
    void HandleEvents();
    void Update();
    void Render();
    void Quit()
    {
        isRunning = false;
    }
    void Clean();

    /*float GetScrollSpeed() const
    {
        return scrollSpeed;
    }

    void SetPlayerLives(uint32_t playerLives)
    {
        this->playerLives = playerLives;
    }

    uint32_t GetPlayerLives()
    {
        return playerLives;
    }

    bool GetLevelComplete()
    {
        return levelComplete;
    }

    uint32_t GetCurrentLevel()
    {
        return currentLevel;
    }

    void SetCurrentLevel(uint32_t currentLevel);*/

private:
    // Game类实例
    static Game *instance;
    // Game类窗口及相关参数
    SDL_Window *window;
    uint32_t width;
    uint32_t height;
    // Game类渲染器
    SDL_Renderer *renderer;
    // Game类状态参数
    GameStateMachine *gameStateMachine;
    bool isRunning;
    //bool levelComplete;
    //uint32_t playerLives;
    //uint32_t currentLevel;
    //float scrollSpeed;
};

#endif