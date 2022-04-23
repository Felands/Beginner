#ifndef MENU_BOTTON_H
#define MENU_BOTTON_H

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

enum class ButtonState
{
    MOUSE_OUT,
    MOUSE_OVER,
    CLICKED
};

class MenuButton : public SDLGameObject
{
public:
    void SetCallback(void(*callback_)())
    {
        callback = callback_;
    }

    ButtonState GetState()
    {
        return state;
    }

    virtual void Update();

    virtual void Draw();

private:
    void (*callback)();
    bool isReleased = true;
    ButtonState state;
};

class MenuButtonCreator : public BaseCreator
{
    GameObject* CreateGameObject() const
    {
        return new MenuButton();
    }
};

#endif
