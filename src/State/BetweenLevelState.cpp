#include "BetweenLevelState.h"
#include "Log.h"

const std::string BetweenLevelState::betweenLevelId = "PAUSE";

bool BetweenLevelState::OnEnter()
{
    LOG_DBG("[BetweenLevelState][OnEnter] Entering the between level state");

    LOG_DBG("[BetweenLevelState][OnEnter] Entered the between level state");
    return true;
}

bool BetweenLevelState::OnExit()
{
    LOG_DBG("[BetweenLevelState][OnExit] Exitting the between level state");

    LOG_DBG("[BetweenLevelState][OnExit] Exitted the between level state");
    return true;
}

void BetweenLevelState::Update()
{
    LOG_DBG("[BetweenLevelState][Update] Updatting the between level state");

    LOG_DBG("[BetweenLevelState][Update] Updatted the between level state");
}

void BetweenLevelState::Render()
{
    LOG_DBG("[BetweenLevelState][Render] Rendering the between level state");

    LOG_DBG("[BetweenLevelState][Render] Rendered the between level state");
}
