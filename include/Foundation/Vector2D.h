#ifndef _VECTOR2D_H_
#define _VECTOR2D_H_

#include<math.h>

class Vector2D
{
public:
    Vector2D(): x(0), y(0)
    {}

    Vector2D(float x_, float y_): x(x_), y(y_)
    {}

    float GetX()
    {
        return x;
    }

    float GetY()
    {
        return y;
    }

    void SetX(float x_)
    {
        x = x_;
    }

    void SetY(float y_)
    {
        y = y_;
    }

    float Length()
    {
        return sqrt(x * x + y * y);
    }

    Vector2D operator+(const Vector2D &v2) const
    {
        return Vector2D(x + v2.x, y + v2.y);
    }

    friend Vector2D& operator+=(Vector2D &v1, const Vector2D &v2)
    {
        v1.x += v2.x;
        v1.y += v2.y;
        return v1;
    }

    Vector2D operator*(float scalar)
    {
        return Vector2D(x * scalar, y * scalar);
    }

    Vector2D& operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2D operator-(const Vector2D &v2) const
    { 
        return Vector2D(x - v2.x, y - v2.y); 
    }

    friend Vector2D &operator-=(Vector2D &v1, const Vector2D &v2)
    {
        v1.x -= v2.x;
        v1.y -= v2.y;
        return v1;
    }

    Vector2D operator/(float scalar) 
    {
        return Vector2D(x / scalar, y / scalar);
    }

    Vector2D &operator/=(float scalar)
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    void Normalize()
    {
        float len = Length();
        if ( len > 0) {
            (*this) *= 1 / len;
        }
    }

private:
    float x;
    float y;
};

#endif
