#include <iostream>

#include "InputHandler.h"
#include "Game.h"

InputHandler* InputHandler::s_pInstance = nullptr;

InputHandler::InputHandler() : m_keystates(SDL_GetKeyboardState(nullptr)), m_mousePosition(new Vector2D(0, 0))
{
    for(size_t i = 0; i < 3; i++) {
        m_mouseButtonStates.push_back(false);
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

bool InputHandler::GetMouseButtonState(int32_t buttonNumber)
{
    if (buttonNumber >= m_mouseButtonStates.size()) {
        std::cout << "buttonNumber is out of array.\n";
    }
    return m_mouseButtonStates[buttonNumber];
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

void InputHandler::OnMouseMove(SDL_Event& event)
{
    m_mousePosition->SetX(event.motion.x);
    m_mousePosition->SetY(event.motion.y);
}

void InputHandler::OnMouseButtonDown(SDL_Event& event)
{
    if(event.button.button == SDL_BUTTON_LEFT) {
        m_mouseButtonStates[LEFT] = true;
    }
    if(event.button.button == SDL_BUTTON_MIDDLE) {
        m_mouseButtonStates[MIDDLE] = true;
    }
    if(event.button.button == SDL_BUTTON_RIGHT) {
        m_mouseButtonStates[RIGHT] = true;
    }
}

void InputHandler::OnMouseButtonUp(SDL_Event& event)
{
    if(event.button.button == SDL_BUTTON_LEFT) {
        m_mouseButtonStates[LEFT] = false;
    }
    if(event.button.button == SDL_BUTTON_MIDDLE) {
        m_mouseButtonStates[MIDDLE] = false;
    }
    if(event.button.button == SDL_BUTTON_RIGHT) {
        m_mouseButtonStates[RIGHT] = false;
    }
}

void InputHandler::Reset()
{
    m_mouseButtonStates[LEFT] = false;
    m_mouseButtonStates[MIDDLE] = false;
    m_mouseButtonStates[RIGHT] = false;
}
