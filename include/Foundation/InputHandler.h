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
private:
    InputHandler();

    ~InputHandler()
    {}

public:
    // 获取Game类的成员：实例
    static InputHandler *Instance()
    {
        if(instance == nullptr) {
            instance = new InputHandler();
        }
        return instance;
    }
    // 获取InputHandler类的成员：鼠标信息
    Vector2D GetMousePosition()
    {
        return mousePosition;
    }
    bool GetMouseButtonState(MouseButtons mouseButton)
    {
        return mouseButtonStates[(size_t)mouseButton];
    }
    // 获取InputHandler类的成员：键盘信息
    bool IsKeyDown(SDL_Scancode key);

    // 实现InputHandler类功能：主流程
    void Update();
    void Reset();
    void Clean();
private:
    // 实现InputHandler类功能：鼠标事件处理
    void OnMouseMove(SDL_Event& event);
    void OnMouseButtonDown(SDL_Event& event);
    void OnMouseButtonUp(SDL_Event& event);

private:
    // InputHandler类实例
    static InputHandler *instance;
    // InputHandler类鼠标信息
    Vector2D mousePosition;
    std::vector<bool> mouseButtonStates;
    // InputHandler类键盘信息
    const Uint8 *keyStates;
};

#endif