#ifndef _GAME_STATE_MACHINE_H_
#define _GAME_STATE_MACHINE_H_

#include <vector>

#include "GameState.h"

class GameStateMachine
{
public:
    void PushState(GameState* pState);

    void ChangeState(GameState* pState);

    void PopState();

    void Update();

    void Render();

private:
    std::vector<GameState*> m_gameStates;
};

#endif