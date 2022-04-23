#ifndef OBJECT_LAYER_H
#define OBJECT_LAYER_H

#include <vector>

#include "Layer.h"
#include "GameObject.h"

class ObjectLayer : public Layer
{
public:
    std::vector<GameObject*> *GetGameObjects() 
    { 
        return &gameObjects; 
    }

    virtual void Update();

    virtual void Render();

    virtual void Clean();

private:
    std::vector<GameObject*> gameObjects;
};

#endif
