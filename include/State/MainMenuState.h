#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include <vector>
#include <string>

#include "GameObject.h"
#include "MenuState.h"

class MainMenuState : public MenuState
{
public:
    MainMenuState()
    {}

    ~MainMenuState()
    {}

    // 实现GameState类的功能：主流程
    virtual bool OnEnter();
    virtual void Update();
    virtual void Render();
    virtual bool OnExit();
private:
    // 实现MenuState类的功能：回调函数及设置回调函数组
    virtual void SetCallbacks(const std::vector<Callback> &callbacks);
    static void MenuToPlay();
    static void ExitFromMenu();
};

#endif
