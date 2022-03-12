#ifndef _GAME_H_
#define _GAME_H_

#include <stdint.h>
#include <vector>

#include "SDL.h"

#include "GameObject.h"
/*#include "GameStateMachine.h"*/

class Game
{
public:
    static Game* Instance()
    {
        if (s_pInstance == nullptr) {
            s_pInstance = new Game();
        }
        return s_pInstance;
    }

    bool Init(const char* title, int32_t xpos, int32_t ypos, uint32_t height, uint32_t width, bool fullScreen);

    void Render();

    void HandleEvents();

    void Update();

    void Clean();

    void SetCurrentLevel(uint32_t currentLevel);
 
    bool Running()
    {
    	return m_bRunning;
    }

    SDL_Renderer* GetRenderer() const
    {
        return m_pRenderer;
    }

    void Quit()
    {
        m_bRunning = false;
    }

    /*GameStateMachine* GetStateMachine()
    {
        return m_pGameStateMachine;
    }*/

    uint32_t GetGameWidth() const 
    { 
        return m_gameWidth; 
    }

    uint32_t GetGameHeight() const 
    { 
        return m_gameHeight; 
    }

private:
    Game()
    {}

    ~Game()
    {}

private:
    uint32_t m_gameWidth;
    uint32_t m_gameHeight;
    /*uint32_t m_currentGameState = MENU;*/
    uint32_t m_currentLevel;
    bool m_bRunning = true;
    bool m_bLevelComplete; 

    SDL_Window* m_pWindow = nullptr;
    SDL_Renderer* m_pRenderer = nullptr;

    std::vector<GameObject*> m_gameObjects;
    /*GameStateMachine* m_pGameStateMachine = nullptr;*/

    static Game* s_pInstance;
};

#endif