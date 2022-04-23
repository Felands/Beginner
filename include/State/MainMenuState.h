#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include <vector>
#include <string>

#include "GameObject.h"
#include "MenuState.h"

class MainMenuState : public MenuState
{
public:
    virtual std::string GetStateId() const
    {
        return menuId;
    }

    virtual void Update();

    virtual void Render();

    virtual bool OnEnter();

    virtual bool OnExit();

private:
    virtual void SetCallbacks(const std::vector<Callback> &callbacks);

    static void MenuToPlay();

    static void ExitFromMenu();

    static const std::string menuId;
    std::vector<GameObject*> gameObjects;
};

#endif
