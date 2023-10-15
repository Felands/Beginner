#ifndef MENU_STATE_H
#define MENU_STATE_H

#include <vector>

#include "GameState.h"

class MenuState : public GameState
{
public:
    // 获取MenuState类的相关信息：状态Id
    virtual std::string GetStateId() const
    {
        return "MENU";
    }

protected:
    typedef void(*Callback)();
    // 实现MenuState类的功能：设置回调函数组
    virtual void SetCallbacks(const std::vector<Callback> &callbacks) = 0;

protected:
    // MenuState类回调函数组
    std::vector<Callback> callbacks;
};

#endif
