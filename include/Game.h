#ifndef _GAME_H_
#define _GAME_H_

#include <unordered_map>
#include <vector>

#include "SDL.h"

#include "GameObject.h"
#include "Ui.h"

class Game
{
public:
    ~Game()
    {}

    bool Init(const char* title, int xpos, int ypos, int height, int width, bool fullScreen);

    void Render();

    void HandleEvents();

    void Update();

    void Clean();
 
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

    static Game* Instance()
    {
        if(s_pInstance == nullptr)
        {
            s_pInstance = new Game();
        }
        return s_pInstance;
    }

private:
    Game():m_pWindow(nullptr), m_pRenderer(nullptr), m_bRunning(true)
    {}

private:
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    std::unordered_map<std::string, GameObject*> m_gameObjects;
    std::vector<Ui *> m_ui;

    static Game* s_pInstance;

    bool m_bRunning;
};

#endif