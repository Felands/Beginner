#ifndef GAME_OVER_STATE_H
#define GAME_OVER_STATE_H

#include <string>
#include <vector>

#include "MenuState.h"
#include "GameObject.h"

class GameOverState : public MenuState
{
public:
    virtual std::string GetStateId() const
    {
        return gameOverId;
    } 

    virtual void Update();

    virtual void Render();

    virtual bool OnEnter();

    virtual bool OnExit();

    virtual void SetCallbacks(const std::vector<Callback> &callbacks);

private:
    static void GameOverToMain();

    static void RestartPlay();

    static const std::string gameOverId;
    std::vector<GameObject*> gameObjects;
};

#endif
