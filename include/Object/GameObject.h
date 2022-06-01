#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <vector>
#include <string>

#include "Vector2D.h"

class GameObject
{
public:
    virtual ~GameObject() {}

    virtual void Load(int32_t x, int32_t y, int32_t callBackId, int32_t animeSpeed,
        std::vector<std::string> textureNames) = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void Clean() = 0;
    virtual void Collision() = 0;
    virtual std::string Type() = 0;

    Vector2D& GetPosition()
    {
        return position;
    }

    // scroll along with tile map
    void Scroll(float scrollSpeed)
    {
        position.SetX(position.GetX() - scrollSpeed);
    }

    bool Updating()
    {
        return updating;
    }

    bool Dead()
    {
        return dead;
    }

    bool Dying()
    {
        return dying;
    }

    void SetUpdating(bool updating)
    {
        this->updating = updating;
    }

protected:
    // constructor with default initialisation list
    GameObject() : position(0,0), velocity(0,0), acceleration(0,0), updating(false), dead(false), dying(false),
        angle(0), alpha(255)
    {}

    // movement variables
    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;

    // animation variables
    std::vector<std::string> textureNames;

    // common boolean variables
    bool updating;
    bool dead;
    bool dying;

    // rotation
    double angle;

    // blending
    uint32_t alpha;
};

#endif
