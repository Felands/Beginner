#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <string>
#include <vector>

#include "GameState.h"
#include "SDLGameObject.h"
#include "Level.h"

class PlayState : public GameState
{
public:
    virtual std::string GetStateId() const
    {
        return playId;
    }

    virtual bool OnEnter();

    virtual bool OnExit();

    virtual void Update();

    virtual void Render();

    Level* GetLevel()
    {
        return level;
    }

    bool CheckCollision(SDLGameObject *object1, SDLGameObject *object2);

private:
    static const std::string playId;
    Level *level;
};

#endif
