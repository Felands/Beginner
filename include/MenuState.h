#ifndef _MENU_STATE_H_
#define _MENU_STATE_H_

#include <vector>
#include <string>

#include "GameObject.h"
#include"GameState.h"

class MenuState : public GameState
{
public:
    virtual void Update();

    virtual void Render();

    virtual bool OnEnter();

    virtual bool OnExit();

    virtual std::string GetStateId() const
    {
        return s_menuId;
    }

    static void s_MenuToPlay();

    static void s_ExitFromMenu();

    protected:
 typedef void(*Callback)();
 virtual void setCallbacks(const std::vector<Callback>& callbacks) 
 = 0;
 std::vector<Callback> m_callbacks;

private:
    static const std::string s_menuId;
    std::vector<GameObject*> m_gameObjects;
};

#endif
