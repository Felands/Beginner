#ifndef _MENU_STATE_H_
#define _MENU_STATE_H_

#include <vector>

#include "GameState.h"

class MenuState : public GameState
{
protected:
    typedef void(*Callback)();
    virtual void SetCallbacks(const std::vector<Callback>& callbacks) = 0;
    std::vector<Callback> m_callbacks;
};

#endif
