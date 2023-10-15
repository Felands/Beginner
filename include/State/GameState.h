#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <string>
#include <vector>

#include "GameObject.h"

enum class GameStates
{
    MENU,
    PLAY,
    GAMEOVER
};

class GameState
{
public:
    // 获取GameState类的相关信息：状态Id
    virtual std::string GetStateId() const = 0;

    // 实现GameState类的功能：主流程
    virtual bool OnEnter() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual bool OnExit() = 0;

protected:
    // GameState类游戏对象组
    std::vector<GameObject*> gameObjects;
};

#endif
