#include "SDLGameObject.h"
#include "Game.h"
#include "Resource.h"
#include "log.h"
#include "TileLayer.h"

void SDLGameObject::Load(int32_t x, int32_t y, int32_t callBackId_, int32_t animeSpeed_,
    std::vector<std::string> textureNames_)
{
    position.SetX(x);
    position.SetY(y);
    velocity.SetX(0);
    velocity.SetY(0);
    callBackId = callBackId_;
    animeSpeed = animeSpeed_;
    textureNames = textureNames_;
}

void SDLGameObject::Update()
{
    LOG_DBG("[SDLGameObject][Update] Updating the SDL game object");

    position += velocity;

    LOG_DBG("[SDLGameObject][Update] Updating the SDL game object");
}

void SDLGameObject::Draw()
{
    LOG_DBG("[SDLGameObject][Draw] Drawing the SDL game object");

    LOG_DBG("[SDLGameObject][Draw] Drew the SDL game object");
}

void SDLGameObject::Clean()
{}

void SDLGameObject::Collision()
{}
    
std::string SDLGameObject::Type()
{
    return std::string("SDLGameObject");
}

void SDLGameObject::DoDyingAnimation()
{
    Scroll(Game::Instance()->GetScrollSpeed());
    if (dyingCounter == dyingTime) {
        dead = true;
        dyingCounter = 0;
    }
    dyingCounter++;
}

bool SDLGameObject::CheckCollideTile(Vector2D newPos)
{
    /*if(newPos.GetY() + height>= Game::Instance()->GetGameHeight() - 32) {
        return false;
    } else {
        for(std::vector<TileLayer*>::iterator it = m_pCollisionLayers->begin(); it != m_pCollisionLayers->end(); ++it) {
            TileLayer* pTileLayer = (*it);
            std::vector<std::vector<int>> tiles = pTileLayer->GetTileIDs();
            Vector2D layerPos = pTileLayer->GetPosition();
            int x, y, tileColumn, tileRow, tileid = 0;
            x = layerPos.getX() / pTileLayer->GetTileSize();
            y = layerPos.getY() / pTileLayer->GetTileSize();
            Vector2D startPos = newPos;
            startPos.m_x += 15;
            startPos.m_y += 20;
            Vector2D endPos(newPos.m_x + (m_width - 15), (newPos.m_y) + m_height - 4);
            for(int i = startPos.m_x; i < endPos.m_x; i++) {
                for(int j = startPos.m_y; j < endPos.m_y; j++) {
                    tileColumn = i / pTileLayer->GetTileSize();
                    tileRow = j / pTileLayer->GetTileSize();
                    tileid = tiles[tileRow + y][tileColumn + x];
                    if(tileid != 0) {
                        return true;
                    }
                }
            }
        }
        return false; 
    }*/
    return true;
}

