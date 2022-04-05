#ifndef _MENU_BOTTON_H_
#define _MENU_BOTTON_H_

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

enum button_state
{
    MOUSE_OUT,
    MOUSE_OVER,
    CLICKED
};

class MenuButton : public SDLGameObject
{
public:
    MenuButton();

    virtual void Draw();

    virtual void Update();

    virtual void Clean();

    void SetCallback(void(*callback)())
    {
        m_callback = callback;
    }

private:
    void (*m_callback)();
    bool m_bReleased;
};

class MenuButtonCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new MenuButton();
    }
};

#endif
