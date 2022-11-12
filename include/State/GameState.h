#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <string>
#include <vector>

#include "GameObject.h"

enum class GameStates
{
    MENU,
    PLAY,
    GAMEOVER
};

class GameState
{
public:
    virtual void Update() = 0;

    virtual void Render() = 0;

    virtual bool OnEnter() = 0;

    virtual bool OnExit() = 0;

    virtual std::string GetStateId() const = 0;

protected:
    std::vector<GameObject*> gameObjects;
};

#endif
