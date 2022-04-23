#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <vector>

#include "SDL.h"

#include "Vector2D.h"

enum class MouseButtons
{
    LEFT,
    MIDDLE,
    RIGHT
};

class InputHandler
{
public:
    static InputHandler *Instance()
    {
        if(instance == nullptr) {
            instance = new InputHandler();
        }
        return instance;
    }

    Vector2D GetMousePosition()
    {
        return mousePosition;
    }

    bool GetMouseButtonState(MouseButtons mouseButton)
    {
        return mouseButtonStates[(size_t)mouseButton];
    }

    void Update();

    void Clean();

    bool IsKeyDown(SDL_Scancode key);

    void Reset();

private:
    InputHandler();

    ~InputHandler()
    {}

    void OnMouseMove(SDL_Event& event);

    void OnMouseButtonDown(SDL_Event& event);

    void OnMouseButtonUp(SDL_Event& event);

    static InputHandler *instance;
    Vector2D mousePosition;
    std::vector<bool> mouseButtonStates;
    const Uint8 *keyStates;
};

#endif