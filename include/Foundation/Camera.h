#ifndef CAMERA_H
#define CAMERA_H

#include "Vector2D.h"

class Camera
{
public:
    static Camera* Instance()
    {
        if(instance == 0) {
            instance = new Camera();
        }
        return instance;
    }

    void Update(Vector2D velocity);

    void SetTarget(Vector2D* target) { this->target = target; }

    void SetPosition(const Vector2D& position) { this->position = position; }

    const Vector2D GetPosition() const;

private:
    Camera();

    ~Camera();

    // the camera's target
    Vector2D* target;

    // the camera's position
    Vector2D position;

    static Camera* instance;
};

#endif