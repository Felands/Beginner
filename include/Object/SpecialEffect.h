#ifndef _SPECIAL_EFFECT_H_
#define _SPECIAL_EFFECT_H_

#include "SDL.h"

#include "GameObject.h"

class SpecialEffect : public GameObject
{
public:
    SpecialEffect(std::string name) :
        GameObject(Vector2D(0, 0), Vector2D(0, 0), name), m_duration(5), m_startTime(SDL_GetTicks())
    {}

    bool IsInvalidate();

    void SetPosition(Vector2D position);

    virtual void Load();

    virtual void Draw();

    virtual void Update();

    virtual void Clean();

    virtual void HandleInput();

private:
    uint32_t m_duration;
    uint32_t m_startTime;
};

#endif