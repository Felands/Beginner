#include <stdint.h>

#include "SDL.h"

#include "InputHandler.h"
#include "Game.h"
#include "Vector2D.h"

InputHandler* InputHandler::s_pInstance = nullptr;

InputHandler* InputHandler::Instance()
{
    if(s_pInstance == nullptr) {
        s_pInstance = new InputHandler();
    }
    return s_pInstance;
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

void InputHandler::Clean()
{
    if (s_pInstance != nullptr) {
        if (m_mousePosition != nullptr) {
            delete m_mousePosition;
        }
        delete s_pInstance;
    }
}

bool InputHandler::IsKeyDown(SDL_Scancode key)
{
    if(m_keystates != nullptr) {
        if(m_keystates[key] == 1) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

bool InputHandler::GetMouseButtonState(MouseButtons buttonNumber)
{
    return m_mouseButtonStates[buttonNumber];
}

void InputHandler::Reset()
{
    m_mouseButtonStates[LEFT] = false;
    m_mouseButtonStates[MIDDLE] = false;
    m_mouseButtonStates[RIGHT] = false;
}

InputHandler::InputHandler() : m_keystates(SDL_GetKeyboardState(nullptr)), m_mousePosition(new Vector2D(0, 0))
{
    for(int i = 0; i < 3; i++) {
        m_mouseButtonStates.push_back(false);
    }
}

void InputHandler::OnMouseMove(SDL_Event &event)
{
    m_mousePosition->SetX(event.motion.x);
    m_mousePosition->SetY(event.motion.y);
}

void InputHandler::OnMouseButtonDown(SDL_Event &event)
{
    if (event.button.button == SDL_BUTTON_LEFT) {
        m_mouseButtonStates[LEFT] = true;
    } else if (event.button.button == SDL_BUTTON_MIDDLE) {
        m_mouseButtonStates[MIDDLE] = true;
    } else if (event.button.button == SDL_BUTTON_RIGHT) {
        m_mouseButtonStates[RIGHT] = true;
    }
}

void InputHandler::OnMouseButtonUp(SDL_Event& event)
{
    if(event.button.button == SDL_BUTTON_LEFT) {
        m_mouseButtonStates[LEFT] = false;
    } else if (event.button.button == SDL_BUTTON_MIDDLE) {
        m_mouseButtonStates[MIDDLE] = false;
    } else if (event.button.button == SDL_BUTTON_RIGHT) {
        m_mouseButtonStates[RIGHT] = false;
    }
}
