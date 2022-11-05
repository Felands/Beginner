#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"
#include "Vector2D.h"

class Camera
{
public:
    static Camera* Instance()
    {
        if(instance == nullptr) {
            instance = new Camera();
        }
        return instance;
    }

    void SetTarget(GameObject* target)
    {
        this->target = target;
    }

    void SetPosition(const Vector2D& position)
    {
        this->position = position;
    }

    const Vector2D GetPosition() const
    {
        return position;
    }

    void Update();

private:
    Camera() : position(0, 0), velocity(0, 0)
    {}

    ~Camera()
    {}

    GameObject* target;
    Vector2D position;
    Vector2D velocity;

    static Camera* instance;
};

#endif