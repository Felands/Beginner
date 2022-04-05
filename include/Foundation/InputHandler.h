#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_

#include <vector>

#include "SDL.h"

#include "Vector2D.h"

enum MouseButtons
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputHandler
{
public:
    static InputHandler* Instance()
    {
        if(s_pInstance == nullptr) {
            s_pInstance = new InputHandler();
        }
        return s_pInstance;
    }

    Vector2D* GetMousePosition()
    {
        return m_mousePosition;
    }

    void Update();

    void Clean();

    bool IsKeyDown(SDL_Scancode key);

    bool GetMouseButtonState(int buttonNumber);

    void Reset();

private:
    void OnMouseMove(SDL_Event& event);

    void OnMouseButtonDown(SDL_Event& event);

    void OnMouseButtonUp(SDL_Event& event);

    InputHandler();

    static InputHandler* s_pInstance;
    std::vector<bool> m_mouseButtonStates;
    Vector2D *m_mousePosition;
    const Uint8 *m_keystates;
};

#endif