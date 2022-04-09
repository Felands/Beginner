#include "ObjectLayer.h"

void ObjectLayer::Update()
{
    for(int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->Update();
    }
}
void ObjectLayer::Render()
{
    for(int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->Draw();
    }
}
