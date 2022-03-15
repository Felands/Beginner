#ifndef _GAME_OVER_STATE_H_
#define _GAME_OVER_STATE_H_

#include <string>
#include <vector>

#include "GameState.h"
#include "GameObject.h"

class GameOverState : public GameState
{
public:
    virtual ~GameOverState(); 

    virtual void Update();

    virtual void Render();

    virtual bool OnEnter();

    virtual bool OnExit();

    virtual std::string GetStateId() const
    {
        return s_gameOverId;
    }

private:
    static void s_GameOverToMain();

    static void s_RestartPlay();

private:
    static const std::string s_gameOverId;
    std::vector<GameObject*> m_gameObjects;
};

#endif
