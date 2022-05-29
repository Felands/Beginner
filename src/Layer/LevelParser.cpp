#include <sstream>

#include "LevelParser.h"
#include "Game.h"
#include "Resource.h"
#include "TileLayer.h"
#include "ObjectLayer.h"
#include "base64.h"
#include "zlib.h"
#include "GameObjectFactory.h"
#include "log.h"
#include "SoundManager.h"

const char *LevelParser::level = "./assets/map.xml";

Level *LevelParser::ParseLevel(const char *levelFile)
{
    LOG_DBG("[LevelParser][ParseLevel] Parsing level from ", levelFile);

    TiXmlDocument levelDocument;
    if (levelDocument.LoadFile(levelFile)) {
        LOG_DBG("[LevelParser][ParseLevel] Succeed to load document from the file");
    } else {
        LOG_ERR("[LevelParser][ParseLevel] Failed to load document from the file");
        return nullptr;
    }

    TiXmlElement *root = levelDocument.RootElement();
    if (root != nullptr) {
        LOG_DBG("[LevelParser][ParseLevel] Succeed to load the root from the document");
    } else {
        LOG_ERR("[LevelParser][ParseLevel] Failed to load the root from the document");
        return nullptr;
    }

    Level *level = new Level();
    for (TiXmlElement *e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("tilelayer")) {
            ParseTileLayer(e, level->GetTileLayers(), level->GetTilesets());
        } else if (e->Value() == std::string("objectlayer")) {
            ParseObjectLayer(e, level->GetObjectLayers());
        } else if (e->Value() == std::string("sound")) {
            ParseSound(e);
        }
    }

    LOG_DBG("[LevelParser][ParseLevel] Parsed level from ", levelFile);
    return level;
}

void LevelParser::ParseTileLayer(TiXmlElement *tileLayerRoot, std::vector<Layer*> *tileLayers,
    std::vector<Tileset> *tilesets)
{
    LOG_DBG("[LevelParser][ParseTileLayer] Parsing the tile layer ", tileLayerRoot->Attribute("name"));

    for (TiXmlElement *e = tileLayerRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if(e->Value() == std::string("tilesets")) {
            ParseTilesets(e, tilesets);
        } else if (e->Value() == std::string("layers")) {
            ParseMapLayers(e, tileLayers, tilesets);
        }
    }

    LOG_DBG("[LevelParser][ParseTileLayer] Parsed a tile layer", tileLayerRoot->Attribute("name"));
}

void LevelParser::ParseTilesets(TiXmlElement *tilesetsRoot, std::vector<Tileset> *tilesets)
{
    LOG_DBG("[LevelParser][ParseTilesets] Parsing tilesets");

    for (TiXmlElement *tilesetRoot = tilesetsRoot->FirstChildElement(); tilesetRoot != nullptr;
        tilesetRoot = tilesetRoot->NextSiblingElement()) {
        Tileset tileset;
        tilesetRoot->Attribute("firstgid", (int*)&tileset.firstGridId);
        tileset.name = tilesetRoot->Attribute("name");
        for (TiXmlElement *tileRoot = tilesetRoot->FirstChildElement(); tileRoot != nullptr;
            tileRoot = tileRoot->NextSiblingElement()) {
            std::string name;
            std::string source;
            uint32_t width;
            uint32_t height;
            uint32_t numColumns;
            uint32_t numRows;
            for (TiXmlElement *e = tileRoot->FirstChildElement(); e != nullptr;
                e = e->NextSiblingElement()) {
                if (e->Value() == std::string("name")) {
                    name = e->Attribute("value");
                    tileset.tileNames.push_back(name);
                } else if (e->Value() == std::string("source")) {
                    source = e->Attribute("value");
                } else if (e->Value() == std::string("width")) {
                    e->Attribute("value", (int*)&width);
                } else if (e->Value() == std::string("height")) {
                    e->Attribute("value", (int*)&height);
                } else if (e->Value() == std::string("numColumns")) {
                    e->Attribute("value", (int*)&numColumns);
                } else if (e->Value() == std::string("numRows")) {
                    e->Attribute("value", (int*)&numRows);
                }
            }
            TextureManager::Instance()->Load(source, name, width, height, numColumns, numRows,
                Game::Instance()->GetRenderer());
        }
        tilesets->push_back(tileset);
    }

    LOG_DBG("[LevelParser][ParseTilesets] Parsed tilesets ");
}

void LevelParser::ParseMapLayers(TiXmlElement *mapLayersRoot, std::vector<Layer*> *tileLayers,
    std::vector<Tileset> *tilesets)
{
    LOG_DBG("[LevelParser][ParseMap] Parsing the map");

    for (TiXmlElement *layerRoot = mapLayersRoot->FirstChildElement(); layerRoot != nullptr;
        layerRoot = layerRoot->NextSiblingElement()) {
        std::string text = layerRoot->FirstChildElement()->FirstChild()->ToText()->Value();
        std::string decodedIds = base64_decode(text);

        // uncompress zlib compression
        uint32_t width;
        layerRoot->Attribute("width", (int*)&width);
        uint32_t height;
        layerRoot->Attribute("height", (int*)&height);
        uLongf numGids = width * height * sizeof(int);
        std::vector<unsigned> gids(numGids);
        uncompress((Bytef*)&gids[0], &numGids,(const Bytef*)decodedIds.c_str(), decodedIds.size());

        std::vector<std::vector<uint32_t>> map;
        std::vector<uint32_t> tileLayerRow(width);
        for (size_t j = 0; j < height; j++) {
            map.push_back(tileLayerRow);
        }

        size_t index = 0;
        for (size_t rows = 0; rows < height; rows++) {
            for(size_t cols = 0; cols < width; cols++) {
                map[rows][cols] = gids[rows * width + cols];
            }
        }

        TileLayer *tileLayer = new TileLayer(*tilesets);
        tileLayer->SetTileIds(map);
        tileLayers->push_back(tileLayer);
    }

    LOG_DBG("[LevelParser][ParseMap] Parsed the map");
}

void LevelParser::ParseObjectLayer(TiXmlElement *objectLayerRoot, std::vector<Layer*> *objectLayers)
{
    LOG_DBG("[LevelParser][ParseObjectLayer] Parsing the object layer ", objectLayerRoot->Attribute("name"));

    ObjectLayer *objectLayer = new ObjectLayer();
    for (TiXmlElement *e = objectLayerRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        ParseObject(e, objectLayer);
    }
    objectLayers->push_back(objectLayer);

    LOG_DBG("[LevelParser][ParseObjectLayer] Parsed the object layer", objectLayerRoot->Attribute("name"));
}

void LevelParser::ParseObject(TiXmlElement *objectRoot, ObjectLayer *objectLayer)
{
    LOG_DBG("[LevelParser][ParseObject] Parsing the object ", objectRoot->Attribute("name"));

    uint32_t width;
    uint32_t height;
    uint32_t numColumns;
    uint32_t numRows;
    uint32_t callbackId;
    uint32_t animSpeed;
    std::string textureName;
    std::vector<std::string> textureNames;
    std::string source;
    for (TiXmlElement *properties = objectRoot->FirstChildElement(); properties != nullptr;
        properties = properties->NextSiblingElement()) {
        for (TiXmlElement *property = properties->FirstChildElement(); property != nullptr;
            property = property->NextSiblingElement()) {
            if (property->Attribute("name") == std::string("source")) {
                source = property->Attribute("value");
            } else if (property->Attribute("name") == std::string("numColumns")) {
                property->Attribute("value", (int*)&numColumns);
            } else if (property->Attribute("name") == std::string("height")) {
                property->Attribute("value", (int*)&height);
            } else if (property->Attribute("name") == std::string("textureName")) {
                textureName = property->Attribute("value");
                textureNames.push_back(textureName);
            } else if (property->Attribute("name") == std::string("width")) {
                property->Attribute("value", (int*)&width);
            } else if (property->Attribute("name") == std::string("callbackId")) {
                property->Attribute("value", (int*)&callbackId);
            } else if (property->Attribute("name") == std::string("animSpeed")) {
                property->Attribute("value", (int*)&animSpeed);
            } else if (property->Attribute("name") == std::string("numRows")) {
                property->Attribute("value", (int*)&numRows);
            }
        }
        TextureManager::Instance()->Load(source, textureName, width, height, numColumns, numRows,
            Game::Instance()->GetRenderer());
    }

    int32_t x;
    int32_t y;
    objectRoot->Attribute("x", (int*)&x);
    objectRoot->Attribute("y", (int*)&y);

    GameObject *gameObject = GameObjectFactory::Instance()->Create(objectRoot->Attribute("type"));
    gameObject->Load(x, y, callbackId, animSpeed, textureNames);
    objectLayer->GetGameObjects()->push_back(gameObject);

    LOG_DBG("[LevelParser][ParseObject] Parsed the object ", objectRoot->Attribute("name"));
}

void LevelParser::ParseSound(TiXmlElement* soundRoot)
{
    LOG_DBG("[LevelParse][ParseSound] Parsing sound resource");

    for (TiXmlElement *e = soundRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("musics")) {
            for (TiXmlElement *music = e->FirstChildElement(); music != nullptr;
                music = music->NextSiblingElement()) {
                    ParseMusic(music);
            }
        } else if (e->Value() == std::string("sfxs")) {
            for (TiXmlElement *sfx = e->FirstChildElement(); sfx != nullptr; sfx = sfx->NextSiblingElement()) {
                ParseSfx(sfx);
            }
        }
    }

    LOG_DBG("[LevelParse][ParseSound] Parsed sound resource");
}

void LevelParser::ParseMusic(TiXmlElement* musicRoot)
{
    LOG_DBG("[LevelParse][ParseMusic] Parsing the music ", musicRoot->Attribute("name"));

    std::string source;
    for (TiXmlElement *e = musicRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("source")) {
            source = e->Attribute("value");
        }
    }
    SoundManager::Instance()->Load(source, musicRoot->Attribute("name"), SoundType::SOUND_MUSIC);

    LOG_DBG("[LevelParse][ParseMusic] Parsed the music ", musicRoot->Attribute("name"));
}

void LevelParser::ParseSfx(TiXmlElement* sfxRoot)
{
    LOG_DBG("[LevelParse][ParseSfx] Parsing the sfx ", sfxRoot->Attribute("name"));

    std::string source;
    for (TiXmlElement *e = sfxRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("source")) {
            source = e->Attribute("value");
        }
    }
    SoundManager::Instance()->Load(source, sfxRoot->Attribute("name"), SoundType::SOUND_SFX);

    LOG_DBG("[LevelParse][ParseSfx] Parsed the sfx ", sfxRoot->Attribute("name"));
}
