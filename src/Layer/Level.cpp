#include "Level.h"
#include "Log.h"

void Level::Update()
{
    LOG_DBG("[Level][Update] Updating the level");

    for(int i = 0; i < tileLayers.size(); i++) {
        tileLayers[i]->Update();
    }

    for(int i = 0; i < objectLayers.size(); i++) {
        objectLayers[i]->Update();
    }

    LOG_DBG("[Level][Update] Updated the level");
}

void Level::Render()
{
    LOG_DBG("[Level][Render] Rendering the level");

    for(int i = 0; i < tileLayers.size(); i++) {
        tileLayers[i]->Render();
    }

    for(int i = 0; i < objectLayers.size(); i++) {
        objectLayers[i]->Render();
    }

    LOG_DBG("[Level][Render] Rendered the level");
}

void Level::Clean()
{
    LOG_DBG("[Level][Clean] Cleaning the level");

    for(int i = 0; i < tileLayers.size(); i++) {
        tileLayers[i]->Clean();
        delete tileLayers[i];
    }

    for(int i = 0; i < objectLayers.size(); i++) {
        objectLayers[i]->Clean();
        delete objectLayers[i];
    }

    LOG_DBG("[Level][Clean] Cleaned the level");
}
