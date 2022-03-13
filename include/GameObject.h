#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <stdint.h>
#include <string>
#include <memory>

#include "LoaderParams.h"
#include "Vector2D.h"

class GameObject
{
public:
    virtual void Load(std::unique_ptr<LoaderParams> pParams) = 0;

    virtual void Draw()= 0 ;

    virtual void Update() = 0;

    virtual void Clean() = 0;

    virtual void Collision() = 0;

    virtual std::string Type() = 0;

    /*void SetCollisionLayers(std::vector<TileLayer*>* layers) { m_pCollisionLayers = layers; }*/

    Vector2D& GetPosition()
    {
        return m_position;
    }

    uint32_t GetWidth()
    {
        return m_width;
    }

    uint32_t GetHeight()
    {
        return m_height;
    }

    // scroll along with tile map
    void Scroll(float scrollSpeed)
    {
        m_position.SetX(m_position.GetX() - scrollSpeed);
    }

    // is the object currently being updated?
    bool Updating()
    {
        return m_bUpdating;
    }

    // is the object dead?
    bool Dead()
    {
        return m_bDead;
    }

    // is the object doing a death animation?
    bool Dying()
    {
        return m_bDying;
    }

    // set whether to update the object or not
    void SetUpdating(bool updating)
    {
        m_bUpdating = updating;
    }

protected:
    GameObject() : m_position(0, 0), m_velocity(0, 0), m_acceleration(0, 0), m_width(0), m_height(0), m_currentRow(1),
        m_currentFrame(1), m_bUpdating(false), m_bDead(false), m_bDying(false), m_angle(0), m_alpha(255)
    {}

    virtual ~GameObject()
    {}

protected:
    // movement variables
    Vector2D m_position;
    Vector2D m_velocity;
    Vector2D m_acceleration;

    // size variables
    uint32_t m_width;
    uint32_t m_height;

    // animation variables
    uint32_t m_currentRow;
    uint32_t m_currentFrame;
    uint32_t m_numFrames;
    std::string m_textureID;

    // common boolean variables
    bool m_bUpdating;
    bool m_bDead;
    bool m_bDying;

    // rotation
    double m_angle;

    // blending
    uint32_t m_alpha;
    /*std::vector<TileLayer*>* m_pCollisionLayers;*/
};

#endif