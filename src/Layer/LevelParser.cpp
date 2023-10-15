#include <sstream>

#include "LevelParser.h"
#include "Game.h"
#include "Resource.h"
#include "TileLayer.h"
#include "ObjectLayer.h"
#include "base64.h"
#include "zlib.h"
#include "GameObjectFactory.h"
#include "Log.h"

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

    uint32_t width;
    uint32_t height;
    root->Attribute("width", (int*)&width);
    root->Attribute("height", (int*)&height);
    Level *level = new Level();
    level->SetHeight(height);
    level->SetWidth(width);
    for (TiXmlElement *e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("materials")) {
            ParseMaterials(e, level);
        } else if (e->Value() == std::string("layers")) {
            ParseLayers(e, level);
        }
    }

    LOG_DBG("[LevelParser][ParseLevel] Parsed level from ", levelFile);
    return level;
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
            Resource::Instance()->LoadOneTexture(source, name, width, height, numColumns, numRows,
                Game::Instance()->GetRenderer());
        }
        tilesets->push_back(tileset);
    }

    LOG_DBG("[LevelParser][ParseTilesets] Parsed tilesets ");
}

void LevelParser::ParseMaterials(TiXmlElement *materialsRoot, Level* level)
{
    LOG_DBG("[LevelParser][ParseMaterials] Parsing materials");

    for (TiXmlElement *e = materialsRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if(e->Value() == std::string("tilesets")) {
            ParseTilesets(e, level->GetTilesets());
        } else if (e->Value() == std::string("sounds")) {
            ParseSounds(e);
        }
    }

    LOG_DBG("[LevelParser][ParseMaterials] Parsed materials");
}

void LevelParser::ParseLayers(TiXmlElement *layersRoot, Level* level)
{
    LOG_DBG("[LevelParser][ParseLayers] Parsing layers");

    for (TiXmlElement *e = layersRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if(e->Value() == std::string("tilelayers")) {
            ParseTileLayers(e, level);
        } else if (e->Value() == std::string("objectlayers")) {
            ParseObjectLayers(e, level);
        }
    }

    LOG_DBG("[LevelParser][ParseLayers] Parsed layers");
}

void LevelParser::ParseTileLayers(TiXmlElement *tileLayersRoot, Level* level)
{
    LOG_DBG("[LevelParser][ParseTileLayers] Parsing tile layers");

    for (TiXmlElement *tileLayerRoot = tileLayersRoot->FirstChildElement(); tileLayerRoot != nullptr;
        tileLayerRoot = tileLayerRoot->NextSiblingElement()) {
        std::string text = tileLayerRoot->FirstChildElement()->FirstChild()->ToText()->Value();
        std::string decodedIds = base64_decode(text);

        // uncompress zlib compression
        uint32_t width;
        tileLayerRoot->Attribute("width", (int*)&width);
        uint32_t height;
        tileLayerRoot->Attribute("height", (int*)&height);
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

        uint32_t collidable;
        tileLayerRoot->Attribute("collidable", (int*)&collidable);
        TileLayer *tileLayer = new TileLayer(*level->GetTilesets());
        tileLayer->SetTileIds(map);
        uint32_t tileWidth;
        uint32_t tileHeight;
        tileLayerRoot->Attribute("tileWidth", (int*)&tileWidth);
        tileLayerRoot->Attribute("tileHeight", (int*)&tileHeight);
        tileLayer->SetTileHeight(tileHeight);
        tileLayer->SetTileWidth(tileWidth);
        if(collidable) {
            level->GetCollisionLayers()->push_back(tileLayer);
        }
        level->GetTileLayers()->push_back(tileLayer);
    }

    LOG_DBG("[LevelParser][ParseTileLayers] Parsed tile layers");
}

void LevelParser::ParseObjectLayers(TiXmlElement *objectLayersRoot, Level* level)
{
    LOG_DBG("[LevelParser][ParseObjectLayers] Parsing object layers");

    for (TiXmlElement* objectLayerRoot = objectLayersRoot->FirstChildElement(); objectLayerRoot != nullptr;
        objectLayerRoot = objectLayerRoot->NextSiblingElement()) {
        ObjectLayer *objectLayer = new ObjectLayer();
        for (TiXmlElement *objectRoot = objectLayerRoot->FirstChildElement(); objectRoot != nullptr;
            objectRoot = objectRoot->NextSiblingElement()) {
            ParseObject(objectRoot, objectLayer, level);
        }
        level->GetObjectLayers()->push_back(objectLayer);

        int32_t collidable;
        objectLayersRoot->Attribute("collidable", (int*)&collidable);
        if (collidable) {
            level->GetCollisionLayers()->push_back(objectLayer);
        }
    }

    LOG_DBG("[LevelParser][ParseObjectLayers] Parsed object layers");
}

void LevelParser::ParseObject(TiXmlElement *objectRoot, ObjectLayer *objectLayer, Level* level)
{
    LOG_DBG("[LevelParser][ParseObject] Parsing the object ", objectRoot->Attribute("name"));

    uint32_t callbackId;
    uint32_t animSpeed;
    std::string textureName;
    ObjectAnimeInfo objectAnimeInfo = { 0 };
    std::vector<ObjectAnimeInfo> ObjectAnimeInfos;
    for (TiXmlElement *properties = objectRoot->FirstChildElement(); properties != nullptr;
        properties = properties->NextSiblingElement()) {
        for (TiXmlElement *property = properties->FirstChildElement(); property != nullptr;
            property = property->NextSiblingElement()) {
            if (property->Attribute("name") == std::string("textureName")) {
                textureName = property->Attribute("value");
                objectAnimeInfo.textureName = textureName;
            } else if (property->Attribute("name") == std::string("callbackId")) {
                property->Attribute("value", (int*)&callbackId);
                objectAnimeInfo.callBackId = callbackId;
            } else if (property->Attribute("name") == std::string("animSpeed")) {
                property->Attribute("value", (int*)&animSpeed);
                objectAnimeInfo.animeSpeed = animSpeed;
            }
        }
        ObjectAnimeInfos.push_back(objectAnimeInfo);
    }

    int32_t x;
    int32_t y;
    objectRoot->Attribute("x", (int*)&x);
    objectRoot->Attribute("y", (int*)&y);

    GameObject *gameObject = GameObjectFactory::Instance()->Create(objectRoot->Attribute("type"));
    gameObject->Load(x, y, ObjectAnimeInfos);
    if(gameObject->Type() == std::string("Player")) {
        level->SetPlayer(dynamic_cast<Player*>(gameObject));
    }
    objectLayer->GetGameObjects()->push_back(gameObject);
    gameObject->SetCollisionLayers(level->GetCollisionLayers());

    LOG_DBG("[LevelParser][ParseObject] Parsed the object ", objectRoot->Attribute("name"));
}

void LevelParser::ParseSounds(TiXmlElement* soundRoot)
{
    LOG_DBG("[LevelParse][ParseSounds] Parsing sound resource");

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

    LOG_DBG("[LevelParse][ParseSounds] Parsed sound resource");
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
    Resource::Instance()->LoadOneSound(source, musicRoot->Attribute("name"), SoundType::SOUND_MUSIC);

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
    Resource::Instance()->LoadOneSound(source, sfxRoot->Attribute("name"), SoundType::SOUND_SFX);

    LOG_DBG("[LevelParse][ParseSfx] Parsed the sfx ", sfxRoot->Attribute("name"));
}
