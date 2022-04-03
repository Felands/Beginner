#ifndef _MAIN_MENU_STATE_H_
#define _MAIN_MENU_STATE_H_

#include <vector>
#include <string>

#include "GameObject.h"
#include"MenuState.h"

class MainMenuState : public MenuState
{
public:
    virtual void Update();

    virtual void Render();

    virtual bool OnEnter();

    virtual bool OnExit();

    virtual std::string GetStateId() const { return s_menuId; }

private:
    virtual void setCallbacks(const std::vector<Callback>& callbacks);

    static void s_MenuToPlay();

    static void s_ExitFromMenu();

    static const std::string s_menuId;
    std::vector<GameObject*> m_gameObjects;
};

#endif
