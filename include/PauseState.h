#ifndef _PAUSE_STATE_H_
#define _PAUSE_STATE_H_

#include <string>
#include <vector>

#include "GameState.h"
#include "GameObject.h"

class PauseState : public MenuState
{
public:
    virtual void Update();

    virtual void Render();

    virtual bool OnEnter();

    virtual bool OnExit();

    virtual std::string GetStateId() const
    {
        return s_pauseId;
    }

    virtual void setCallbacks(const std::vector<Callback>& callbacks);

private:
    static void s_PauseToMain();

    static void s_ResumePlay();

private:
    static const std::string s_pauseId;
    std::vector<GameObject*> m_gameObjects;
};

#endif
