#include "ObjectLayer.h"
#include "Log.h"

void ObjectLayer::Update()
{
    LOG_DBG("[ObjectLayer][Update] Updating the object layer");

    for(int i = 0; i < gameObjects.size(); i++) {
        gameObjects[i]->Update();
    }

    LOG_DBG("[ObjectLayer][Update] Updated the object layer");
}

void ObjectLayer::Render()
{
    LOG_DBG("[ObjectLayer][Render] Rendering the object layer");

    for(int i = 0; i < gameObjects.size(); i++) {
        gameObjects[i]->Draw();
    }

    LOG_DBG("[ObjectLayer][Render] Rendered the object layer");
}

void ObjectLayer::Clean()
{
    LOG_DBG("[ObjectLayer][Clean] Cleaning the object layer");

    for(int i = 0; i < gameObjects.size(); i++) {
        gameObjects[i]->Clean();
        delete gameObjects[i];
    }

    LOG_DBG("[ObjectLayer][Clean] Cleaned the object layer");
}
