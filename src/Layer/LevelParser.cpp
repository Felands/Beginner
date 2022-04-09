#include "LevelParser.h"
#include "Resource.h"
#include "Game.h"
#include "TileLayer.h"
#include "ObjectLayer.h"

Level* LevelParser::ParseLevel(const char *levelFile)
{
    // create a TinyXML document and load the map XML
    TiXmlDocument levelDocument;
    levelDocument.LoadFile(levelFile);
    // create the level object
    Level* pLevel = new Level();
    // get the root node 
    TiXmlElement* pRoot = levelDocument.RootElement();
    pRoot->Attribute("tilewidth", (int*)&m_tileSize);
    pRoot->Attribute("width", (int*)&m_width);
    pRoot->Attribute("height", (int*)&m_height);
    // parse the tilesets
    for(TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if(e->Value() == std::string("tileset")) {
            ParseTilesets(e, pLevel->GetTilesets());
        }
    }
    // parse any object layers
    for(TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if(e->Value() == std::string("objectgroup") || e->Value() == std::string("layer")) {
            if(e->FirstChildElement()->Value() == std::string("object")) {
                ParseObjectLayer(e, pLevel->GetLayers());
            } else if (e->FirstChildElement()->Value() == std::string("data")) {
                ParseTileLayer(e, pLevel->GetLayers(), pLevel->GetTilesets());
            }
        }
    }
    return pLevel;
}

void LevelParser::ParseTextures(TiXmlElement* pTextureRoot)
{
    TextureManager::Instance()->Load(pTextureRoot->Attribute("value"),  pTextureRoot->Attribute("name"),
        Game::Instance()->GetRenderer());
}

void LevelParser::ParseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets)
{
    // first add the tileset to texture manager
    TextureManager::Instance()->Load(pTilesetRoot->FirstChildElement()->Attribute("source"),
        pTilesetRoot->Attribute("name"), Game::Instance()->GetRenderer());
    // create a tileset object
    Tileset tileset;
    pTilesetRoot->FirstChildElement()->Attribute("width", (int*)&tileset.width);
    pTilesetRoot->FirstChildElement()->Attribute("height", (int*)&tileset.height);
    pTilesetRoot->Attribute("firstgid", (int*)&tileset.firstGridID);
    pTilesetRoot->Attribute("tilewidth", (int*)&tileset.tileWidth);
    pTilesetRoot->Attribute("tileheight", (int*)&tileset.tileHeight);
    pTilesetRoot->Attribute("spacing", (int*)&tileset.spacing);
    pTilesetRoot->Attribute("margin", (int*)&tileset.margin);
    tileset.name = pTilesetRoot->Attribute("name");
    tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);
    pTilesets->push_back(tileset);
}

void LevelParser::ParseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*> *pLayers,
    const std::vector<Tileset>* pTilesets)
{
    TileLayer* pTileLayer = new TileLayer(m_tileSize, *pTilesets);
    // tile data
    std::vector<std::vector<uint32_t>> data;
    std::string decodedIDs;
    TiXmlElement* pDataNode;
    for(TiXmlElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if(e->Value() == std::string("data")) {
            pDataNode = e;
        }
    }
    for(TiXmlNode* e = pDataNode->FirstChild(); e != NULL; e = e->NextSibling()) {
        TiXmlText* text = e->ToText();
        std::string t = text->Value();
        decodedIDs = base64_decode(t);
    }
    // uncompress zlib compression
    uLongf numGids = m_width * m_height * sizeof(int);
    std::vector<unsigned> gids(numGids);
    uncompress((Bytef*)&gids[0], &numGids,(const Bytef*)decodedIDs.c_str(), decodedIDs.size());
    std::vector<uint32_t> layerRow(m_width);
    for(size_t j = 0; j < m_height; j++) {
        data.push_back(layerRow);
    }
    for(size_t rows = 0; rows < m_height; rows++) {
        for(size_t cols = 0; cols < m_width; cols++) {
            data[rows][cols] = gids[rows * m_width + cols];
        }
    }
    pTileLayer->SetTileIDs(data);
    pLayers->push_back(pTileLayer);
}

void LevelParser::ParseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*> *pLayers)
{
    // create an object layer
    ObjectLayer* pObjectLayer = new ObjectLayer();
    std::cout << pObjectElement->FirstChildElement()->Value();
    for(TiXmlElement* e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        std::cout << e->Value();
        if(e->Value() == std::string("object")) {
            uint32_t x, y, width, height, numFrames, callbackID, animSpeed;
            std::string textureID;
            // get the initial node values type, x and y
            e->Attribute("x", (int*)&x);
            e->Attribute("y", (int*)&y);
            GameObject* pGameObject = GameObjectFactory::Instance()->Create(e->Attribute("type"));
            // get the property values
            for(TiXmlElement* properties = e->FirstChildElement(); properties != NULL;
                properties = properties->NextSiblingElement()) {
                if(properties->Value() == std::string("properties")) {
                    for(TiXmlElement* property = properties->FirstChildElement(); property != NULL;
                        property = property->NextSiblingElement()) {
                        if(property->Value() == std::string("property")) {
                            ParseTextures(e);
                            if(property->Attribute("name") == std::string("numFrames")) {
                                property->Attribute("value", (int*)&numFrames);
                            }
                            else if(property->Attribute("name") == std::string("textureHeight")) {
                                property->Attribute("value", (int*)&height);
                            }
                            else if(property->Attribute("name") == std::string("textureID")) {
                                textureID = property->Attribute("value");
                            }
                            else if(property->Attribute("name") == std::string("textureWidth")) {
                                property->Attribute("value", (int*)&width);
                            }
                            else if(property->Attribute("name") == std::string("callbackID")) {
                                property->Attribute("value", (int*)&callbackID);
                            }
                            else if(e->Attribute("name") == std::string("animSpeed")) {
                                property->Attribute("value", (int*)&animSpeed);
                            }
                        }
                    }
                }
            }
            pGameObject->Load(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed));
            pObjectLayer->GetGameObjects()->push_back(pGameObject);
        }
    }
    pLayers->push_back(pObjectLayer);
}
