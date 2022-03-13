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
    static InputHandler* Instance();

    void Update();

    void Clean();

    bool IsKeyDown(SDL_Scancode key);

    bool GetMouseButtonState(MouseButtons buttonNumber);

    void Reset();

    Vector2D* GetMousePosition()
    {
        return m_mousePosition;
    }

private:
    InputHandler();
 
    ~InputHandler()
    {}

    void OnMouseMove(SDL_Event& event);

    void OnMouseButtonDown(SDL_Event& event);

    void OnMouseButtonUp(SDL_Event& event);

private:
    const Uint8 *m_keystates;

    std::vector<bool> m_mouseButtonStates;
    Vector2D *m_mousePosition;

    static InputHandler* s_pInstance;
};

#endif