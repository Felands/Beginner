#include "MenuBotton.h"
#include "Resource.h"
#include "InputHandler.h"

MenuButton::MenuButton(const LoaderParams* pParams, void (*callback)()) : SDLGameObject(pParams), m_callback(callback)
{
    m_currentFrame = MOUSE_OUT;
}

void MenuButton::load(const LoaderParams *pParams)
{
 SDLGameObject::load(pParams);
 m_callbackID = pParams->getCallbackID();
 m_currentFrame = MOUSE_OUT;
}

void MenuButton::Draw()
{
    SDLGameObject::Draw();
}

void MenuButton::Update()
{
    Vector2D* pMousePos = InputHandler::Instance()->GetMousePosition();
    if(pMousePos->GetX() < (m_position.GetX() + m_width) && pMousePos->GetX() > m_position.GetX() &&
       pMousePos->GetY() < (m_position.GetY() + m_height) && pMousePos->GetY() > m_position.GetY()) {
        if(InputHandler::Instance()->GetMouseButtonState(LEFT) && m_bReleased) {
            m_currentFrame = CLICKED;
            m_callback();
            m_bReleased = false;
        } else if(!InputHandler::Instance()->GetMouseButtonState(LEFT)) {
            m_bReleased = true;
            m_currentFrame = MOUSE_OVER;
        }
    } else {
        m_currentFrame = MOUSE_OUT;
    }
}

void MenuButton::Clean()
{
    SDLGameObject::Clean();
}
