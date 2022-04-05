#include "ObjectLayer.h"
#include "Resource.h"
#include "Game.h"

void ObjectLayer::update()
{
    for(int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->Update();
    }
}
void ObjectLayer::render()
{
    for(int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->Draw();
    }
}
