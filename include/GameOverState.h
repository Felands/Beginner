#ifndef _GAME_OVER_STATE_H_
#define _GAME_OVER_STATE_H_

#include <string>

#include "GameState.h"
#include "GameState.h"

class GameOverState : public  MenuState
{
public:
    virtual void Update();

    virtual void Render();

    virtual bool OnEnter();

    virtual bool OnExit();

    virtual std::string GetStateId() const
    {
        return s_gameOverId;
    }

    virtual void setCallbacks(const std::vector<Callback>& callbacks);

private:
    static void s_GameOverToMain();

    static void s_RestartPlay();

private:
    static const std::string s_gameOverId;
    std::vector<GameObject*> m_gameObjects;
};

#endif
