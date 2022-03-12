#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Vector2D.h"

class Camera
{
public:
    static Camera* Instance()
    {
        if(s_pCamera == 0) {
            s_pCamera = new Camera();
        }
        return s_pCamera;
    }

    void Update(Vector2D velocity);
 
    void SetTarget(Vector2D* target)
    {
        m_pTarget = target; 
    }

    void SetPosition(const Vector2D& position)
    {
        m_position = position;
    }

    const Vector2D GetPosition() const;

private:
    Camera();

    ~Camera();

private:
    // the camera's target
    Vector2D* m_pTarget;
    // the camera's position
    Vector2D m_position;
    static Camera* s_pCamera;
};

#endif