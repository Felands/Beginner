#ifndef _PLAY_STATE_H_
#define _PLAY_STATE_H_

#include <string>
#include <vector>

#include "GameState.h"
#include "SDLGameObject.h"

class PlayState : public GameState
{
public:
    virtual void Update();

    virtual void Render();

    virtual bool OnEnter();

    virtual bool OnExit();

    virtual std::string GetStateId() const
    {
        return s_playId;
    }

    bool CheckCollision(SDLGameObject* p1, SDLGameObject* p2);

private:
    static const std::string s_playId;
    std::vector<GameObject*> m_gameObjects;
};

#endif
