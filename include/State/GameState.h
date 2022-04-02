#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include <string>

enum GameStates
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
};

#endif
