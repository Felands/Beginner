#include <iostream>

#include "SDL.h"

#include "InputHandler.h"
#include "Game.h"
#include "Vector2D.h"

InputHandler *InputHandler::instance = nullptr;

InputHandler::InputHandler() : keyStates(SDL_GetKeyboardState(nullptr)), mousePosition(0, 0)
{
    for(size_t i = (size_t)MouseButtons::LEFT; i <= (size_t)MouseButtons::RIGHT; ++i) {
        mouseButtonStates.push_back(false);
    }
}

void InputHandler::Update()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                Game::Instance()->Quit();
                break;
            case SDL_MOUSEMOTION:
                OnMouseMove(event);
                break;
            case SDL_MOUSEBUTTONDOWN:
                OnMouseButtonDown(event);
                break;
            case SDL_MOUSEBUTTONUP:
                OnMouseButtonUp(event);
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                SDL_PumpEvents();
                break;
            default:
                break;
        }
    }
}

void InputHandler::Reset()
{
    mouseButtonStates[(size_t)MouseButtons::LEFT] = false;
    mouseButtonStates[(size_t)MouseButtons::MIDDLE] = false;
    mouseButtonStates[(size_t)MouseButtons::RIGHT] = false;
}

void InputHandler::Clean()
{
    if (instance != nullptr) {
        delete instance;
    }
}

bool InputHandler::IsKeyDown(SDL_Scancode key)
{
    if(keyStates != nullptr) {
        if(keyStates[(size_t)key] == 1) {
            return true;
        }
    }
    return false;
}

void InputHandler::OnMouseMove(SDL_Event &event)
{
    mousePosition.SetX(event.motion.x);
    mousePosition.SetY(event.motion.y);
}

void InputHandler::OnMouseButtonDown(SDL_Event &event)
{
    if(event.button.button == SDL_BUTTON_LEFT) {
        mouseButtonStates[(size_t)MouseButtons::LEFT] = true;
    }
    if(event.button.button == SDL_BUTTON_MIDDLE) {
        mouseButtonStates[(size_t)MouseButtons::MIDDLE] = true;
    }
    if(event.button.button == SDL_BUTTON_RIGHT) {
        mouseButtonStates[(size_t)MouseButtons::RIGHT] = true;
    }
}

void InputHandler::OnMouseButtonUp(SDL_Event& event)
{
    if(event.button.button == SDL_BUTTON_LEFT) {
        mouseButtonStates[(size_t)MouseButtons::LEFT] = false;
    }
    if(event.button.button == SDL_BUTTON_MIDDLE) {
        mouseButtonStates[(size_t)MouseButtons::MIDDLE] = false;
    }
    if(event.button.button == SDL_BUTTON_RIGHT) {
        mouseButtonStates[(size_t)MouseButtons::RIGHT] = false;
    }
}
