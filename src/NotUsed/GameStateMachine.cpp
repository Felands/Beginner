#include "GameStateMachine.h"
#include "GameState.h"

void GameStateMachine::PushState(GameState *pState)
{
    m_gameStates.push_back(pState); 
    m_gameStates.back()->OnEnter();
}

void GameStateMachine::PopState()
{
    if(!m_gameStates.empty())
    {
        if(m_gameStates.back()->OnExit())
        {
            delete m_gameStates.back();
            m_gameStates.pop_back();
        }
    }
}

void GameStateMachine::ChangeState(GameState *pState)
{
    if(!m_gameStates.empty())
    {
        if(m_gameStates.back()->GetStateId() == pState->GetStateId())
        {
            return;
        }
        if(m_gameStates.back()->OnExit())
        {
            delete m_gameStates.back();
            m_gameStates.pop_back();
        }
    }
    m_gameStates.push_back(pState);
    m_gameStates.back()->OnEnter();
}

void GameStateMachine::Update()
{
    if(!m_gameStates.empty())
    {
        m_gameStates.back()->Update();
    }
}

void GameStateMachine::Render()
{
    if(!m_gameStates.empty())
    {
        m_gameStates.back()->Render();
    }
}
