#ifndef _OBJECT_LAYER_H_
#define _OBJECT_LAYER_H_

#include <vector>

#include "Layer.h"
#include "GameObject.h"
#include "tinyxml.h"

class ObjectLayer : public Layer
{
public:
    virtual void update();
    virtual void render();
    std::vector<GameObject*>* getGameObjects() 
    { 
        return &m_gameObjects; 
    }
    void parseTextures(TiXmlElement* pTextureRoot);
    void parseObjectLayer(TiXmlElement* pObjectElement,std::vector<Layer*> *pLayers);


private:
    std::vector<GameObject*> m_gameObjects;
};

#endif
