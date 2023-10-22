#include "GameStateMachine.h"
#include "Log.h"

void GameStateMachine::Update()
{
    LOG_DBG("[GameStateMachine][Update] Updating the game state machine");

    if(!gameStates.empty()) {
        LOG_DBG("[GameStateMachine][Update] The state is ", gameStates.back()->GetStateId(), ".");
        gameStates.back()->Update();
    }

    LOG_DBG("[GameStateMachine][Update] Updatted the game state machine");
}

void GameStateMachine::Render()
{
    LOG_DBG("[GameStateMachine][Render] Rendering the game state machine");

    if(!gameStates.empty()) {
        LOG_DBG("[GameStateMachine][Render] The state is ", gameStates.back()->GetStateId());
        gameStates.back()->Render();
    }

    LOG_DBG("[GameStateMachine][Render] Rendered the game state machine");
}

void GameStateMachine::Clean()
{
    LOG_DBG("[GameStateMachine][Clean] Cleaning the game state machine");

    while (!gameStates.empty()) {
        PopState();
    }

    LOG_DBG("[GameStateMachine][Clean] Cleaning the game state machine");
}

void GameStateMachine::PushState(GameState *state)
{
    if (state == nullptr) {
        LOG_ERR("[GameStateMachine][PushState] The state passed in is null point");
        return;
    }

    LOG_DBG("[GameStateMachine][PushState] Pushing the game state machine a new state, the state is ",
        state->GetStateId());

    gameStates.push_back(state); 
    gameStates.back()->OnEnter();

    LOG_DBG("[GameStateMachine][PushState] Pushed the game state machine a new state");
}

void GameStateMachine::ChangeState(GameState *state)
{
    LOG_DBG("[GameStateMachine][ChangeState] Changing the game state machine");

    PopState();
    PushState(state);

    LOG_DBG("[GameStateMachine][ChangeState] Changed the game state machine");
}

void GameStateMachine::PopState()
{
    LOG_DBG("[GameStateMachine][PopState] Popping an old state on the back of the game state machine");

    if(!gameStates.empty()) {
        LOG_DBG("[GameStateMachine][PopState] The state is ", gameStates.back()->GetStateId());
        if(gameStates.back()->OnExit())
        {
            delete gameStates.back();
            gameStates.pop_back();
        }
    }

    LOG_DBG("[GameStateMachine][PopState] Popped an old state on the back of the game state machine");
}
