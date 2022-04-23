#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include <string>
#include <vector>

#include "MenuState.h"
#include "GameObject.h"

class PauseState : public MenuState
{
public:
    virtual std::string GetStateId() const
    {
        return pauseId;
    }

    virtual bool OnEnter();

    virtual bool OnExit();

    virtual void Update();

    virtual void Render();

    virtual void SetCallbacks(const std::vector<Callback>& callbacks);

private:
    static void PauseToMain();

    static void ResumePlay();

    static const std::string pauseId;
    std::vector<GameObject*> gameObjects;
};

#endif
