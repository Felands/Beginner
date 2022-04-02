#ifndef _MENU_BOTTON_H_
#define _MENU_BOTTON_H_

#include "LoaderParams.h"
#include "SDLGameObject.h"

enum button_state
{
    MOUSE_OUT = 1,
    MOUSE_OVER,
    CLICKED
};

class MenuButton : public SDLGameObject
{
public:
    MenuButton(const LoaderParams* pParams, void (*callback)());

    virtual void Draw();

    virtual void Update();

    virtual void Clean();

private:
    void (*m_callback)();
    bool m_bReleased;
};

#endif
