#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <unordered_map>
#include <vector>

#include "GameObject.h"
#include "SpecialEffect.h"

enum class PlayerState
{
    IDLE,
    RUN,
    HIT
};

extern const char *players[];

class Player : public GameObject
{
public:
    Player(std::string name) :
        GameObject(Vector2D(100, 100), Vector2D(0, 0), name), m_state(PlayerState::IDLE)
    {}

    void Load();

    virtual void Draw();

    virtual void Update();

    virtual void Clean();

    virtual void HandleInput();

private:
    std::unordered_map<PlayerState, std::string> m_playerTexture;
    PlayerState m_state;
    std::vector<SpecialEffect *> m_specialEffects;
};

#endif