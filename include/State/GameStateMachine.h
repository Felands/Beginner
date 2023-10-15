#ifndef GAME_STATE_MACHINE_H
#define GAME_STATE_MACHINE_H

#include <vector>

#include "GameState.h"

class GameStateMachine
{
public:
    GameStateMachine()
    {}

    ~GameStateMachine()
    {}

    // 获取GameStateMachine类的成员：当前游戏状态
    GameState* GetCurrentState()
    {
        return gameStates.back();
    }

    // 实现GameStateMachine类的功能：主流程
    void Update();
    void Render();
    void Clean();
    // 实现GameStateMachine类的功能：状态处理
    void PushState(GameState *state);
    void ChangeState(GameState *state);
    void PopState();

private:
    // GameStateMachine类状态组
    std::vector<GameState*> gameStates;
};

#endif
