#ifndef MENU_STATE_H
#define MENU_STATE_H

#include <vector>

#include "GameState.h"

class MenuState : public GameState
{
public:
    virtual std::string GetStateId() const
    {
        return "MENU";
    }

protected:
    typedef void(*Callback)();

    virtual void SetCallbacks(const std::vector<Callback> &callbacks) = 0;

    std::vector<Callback> callbacks;
};

#endif
