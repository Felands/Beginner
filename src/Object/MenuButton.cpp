#include "MenuButton.h"
#include "Resource.h"
#include "InputHandler.h"
#include "log.h"
#include "Resource.h"
#include "Game.h"

void MenuButton::Update()
{
    TextureInfo textureInfo = TextureManager::Instance()->GetTxetureInfo(textureNames[(size_t)state]);
    uint32_t width = textureInfo.width;
    uint32_t height = textureInfo.height;
    Vector2D mousePos = InputHandler::Instance()->GetMousePosition();
    if(mousePos.GetX() < (position.GetX() +  width) && mousePos.GetX() > position.GetX() &&
        mousePos.GetY() < (position.GetY() + height) && mousePos.GetY() > position.GetY()) {
        if ((state == ButtonState::CLICKED) && isReleased) {
            state = ButtonState::MOUSE_OVER;
            callback();
        } else if ((state == ButtonState::MOUSE_OVER) &&
            InputHandler::Instance()->GetMouseButtonState(MouseButtons::LEFT)) {
            state = ButtonState::CLICKED;
            isReleased = false;
        } else if((state != ButtonState::CLICKED) &&
            !InputHandler::Instance()->GetMouseButtonState(MouseButtons::LEFT)) {
            isReleased = true;
            state = ButtonState::MOUSE_OVER;
        } else if ((state == ButtonState::CLICKED) &&
            !InputHandler::Instance()->GetMouseButtonState(MouseButtons::LEFT)) {
                isReleased = true;
        }
    } else {
        state = ButtonState::MOUSE_OUT;
    }
}

void MenuButton::Draw()
{
    LOG_DBG("[MenuButton][Draw] Drawing the menu button");

    SDLGameObject::Draw();

    TextureManager::Instance()->Draw(textureNames[(size_t)state], position.GetX(), position.GetY(),
        0, 0, Game::Instance()->GetRenderer(), SDL_FLIP_NONE, 255);

    LOG_DBG("[MenuButton][Draw] Drew the menu button");
}
