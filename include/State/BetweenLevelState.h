#ifndef BETWEEN_LEVEL_STATE_H
#define BETWEEN_LEVEL_STATE_H

#include <string>

#include "GameState.h"

class BetweenLevelState : public GameState
{
public:
    virtual std::string GetStateId() const
    {
        return betweenLevelId;
    }

    virtual bool OnEnter();

    virtual bool OnExit();

    virtual void Update();

    virtual void Render();

private:
    static const std::string betweenLevelId;
};

#endif
