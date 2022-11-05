#ifndef GAME_STATE_MACHINE_H
#define GAME_STATE_MACHINE_H

#include <vector>

#include "GameState.h"

class GameStateMachine
{
public:
    void Update();

    void Render();

    void Clean();

    void PushState(GameState *state);

    void ChangeState(GameState *state);

    void PopState();

    GameState* GetCurrentState()
    {
        return gameStates.back();
    }

private:
    std::vector<GameState*> gameStates;
};

#endif
