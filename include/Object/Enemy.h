#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <unordered_map>

#include "GameObject.h"

enum class EnemyState
{
    IDLE,
    RUN
};

extern const char *enemies[];

class Enemy : public GameObject
{
public:
    Enemy(std::string name) :
        GameObject(Vector2D(300, 300), Vector2D(1, 0), name), m_state(EnemyState::IDLE)
    {}

    void Load();

    virtual void Draw();

    virtual void Update();

    virtual void Clean();

    virtual void HandleInput();

private:
    std::unordered_map<EnemyState, std::string> m_enemyTexture;
    EnemyState m_state;
};

#endif