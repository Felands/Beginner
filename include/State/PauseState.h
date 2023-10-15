#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include <string>
#include <vector>

#include "MenuState.h"
#include "GameObject.h"

class PauseState : public MenuState
{
public:
    PauseState()
    {}

    ~PauseState()
    {}

    // 获取MenuState类的相关信息：状态Id
    virtual std::string GetStateId() const
    {
        return "PAUSE";
    }

    // 实现PauseState类的功能：主流程
    virtual bool OnEnter();
    virtual void Update();
    virtual void Render();
    virtual bool OnExit();
private:
    // 实现PauseState类的功能：回调函数及设置回调函数组
    virtual void SetCallbacks(const std::vector<Callback>& callbacks);
    static void PauseToMain();
    static void ResumePlay();
};

#endif
