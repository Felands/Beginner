#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <string>
#include <vector>

#include "GameState.h"
#include "SDLGameObject.h"
#include "Level.h"

class PlayState : public GameState
{
public:
    PlayState()
    {}

    ~PlayState()
    {}

    // 获取PlayState类的相关信息：状态Id
    virtual std::string GetStateId() const
    {
        return "PLAY";
    }
    // 获取PlayState类的成员：关卡
    Level* GetLevel()
    {
        return level;
    }

    // 实现PlayState类的功能：主流程
    virtual bool OnEnter();
    virtual void Update();
    virtual void Render();
    virtual bool OnExit();

    // 实现PlayState类的功能：碰撞检测
    bool CheckCollision(SDLGameObject *object1, SDLGameObject *object2);

private:
    // PlayState类管理的关卡
    Level *level;
};

#endif
