#ifndef _OBJECT_LAYER_H_
#define _OBJECT_LAYER_H_

#include <vector>

#include "Layer.h"
#include "GameObject.h"

class ObjectLayer : public Layer
{
public:
    virtual void Update();

    virtual void Render();

    std::vector<GameObject*> *GetGameObjects() 
    { 
        return &m_gameObjects; 
    }

private:
    std::vector<GameObject*> m_gameObjects;
};

#endif
