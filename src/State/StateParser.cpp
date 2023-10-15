#include "StateParser.h"
#include "Game.h"
#include "Resource.h"
#include "GameObjectFactory.h"
#include "Log.h"

const char* StateParser::document = "./assets/state.xml";

void StateParser::ParseState(std::string stateId, std::vector<GameObject*>* objects)
{
    LOG_DBG("[StateParser][ParseState] Parsing the state");

    TiXmlDocument xmlDoc;
    if(!xmlDoc.LoadFile(document)) {
        std::cerr << xmlDoc.ErrorDesc() << "\n";
    }

    TiXmlElement *root = xmlDoc.RootElement();
    TiXmlElement *stateRoot = nullptr;
    for(TiXmlElement *e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if(e->Value() == stateId) {
            stateRoot = e;
            break;
        }
    }

    if (stateId == std::string("PLAY")) {
        return;
    } else {
        ParseOtherState(stateRoot->Attribute("source"), objects);
    }

    LOG_DBG("[StateParser][ParseState] Parsed the state");
}

void StateParser::ParseOtherState(std::string source, std::vector<GameObject*>* objects)
{
    LOG_DBG("[StateParser][ParseOtherState] Parsing the state ");

    TiXmlDocument xmlDoc;
    if(!xmlDoc.LoadFile(source.c_str())) {
        std::cerr << xmlDoc.ErrorDesc() << "\n";
    }

    TiXmlElement *root = xmlDoc.RootElement();
    for(TiXmlElement *e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if(e->Value() == std::string("materials")) {
            ParseMaterials(e);
        } else if (e->Value() == std::string("objects")) {
            ParseObjects(e, objects);
        } else if (e->Value() == std::string("backgrouds")) {
            //ParseBackgrounds(e);
        }
    }

    LOG_DBG("[StateParser][ParseOtherState] Parsed the state");
}

void StateParser::ParseMaterials(TiXmlElement* materialsRoot)
{
    LOG_DBG("[StateParser][ParseMaterials] Parsing materials");

    for(TiXmlElement* e = materialsRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if(e->Value() == std::string("sounds")) {
            ParseSounds(e);
        } else if (e->Value() == std::string("textures")) {
            ParseTextures(e);
        }
    }

    LOG_DBG("[StateParser][ParseMaterials] Parsing materials");
}

void StateParser::ParseSounds(TiXmlElement* soundsRoot)
{
    LOG_DBG("[StateParser][ParseSounds] Parsing sound resource");

    for (TiXmlElement *e = soundsRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("musics")) {
            for (TiXmlElement *musicRoot = e->FirstChildElement(); musicRoot != nullptr;
                musicRoot = musicRoot->NextSiblingElement()) {
                    ParseMusic(musicRoot);
            }
        } else if (e->Value() == std::string("sfxs")) {
            for (TiXmlElement *sfxRoot = e->FirstChildElement(); sfxRoot != nullptr;
                sfxRoot = sfxRoot->NextSiblingElement()) {
                ParseSfx(sfxRoot);
            }
        }
    }

    LOG_DBG("[StateParser][ParseSounds] Parsed sound resource");
}

void StateParser::ParseMusic(TiXmlElement* musicRoot)
{
    LOG_DBG("[StateParser][ParseMusic] Parsing the music ", musicRoot->Attribute("name"));

    std::string source;
    for (TiXmlElement *e = musicRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("source")) {
            source = e->Attribute("value");
        }
    }
    bool ret = Resource::Instance()->LoadOneSound(source, musicRoot->Attribute("name"), SoundType::SOUND_MUSIC);
    if (!ret) {
        LOG_ERR("[StateParser][ParseMusic] Failed to parsed the music ", musicRoot->Attribute("name"));
    } else {
        LOG_DBG("[StateParser][ParseMusic] Parsed the music ", musicRoot->Attribute("name"));
    }
}

void StateParser::ParseSfx(TiXmlElement* sfxRoot)
{
    LOG_DBG("[StateParser][ParseSfx] Parsing the sfx ", sfxRoot->Attribute("name"));

    std::string source;
    for (TiXmlElement *e = sfxRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("source")) {
            source = e->Attribute("value");
        }
    }
    bool ret = Resource::Instance()->LoadOneSound(source, sfxRoot->Attribute("name"), SoundType::SOUND_SFX);
    if (!ret) {
        LOG_ERR("[StateParser][ParseSfx] Failed to parsed the sfx ", sfxRoot->Attribute("name"));
    } else {
        LOG_DBG("[StateParser][ParseSfx] Parsed the sfx ", sfxRoot->Attribute("name"));
    }
}

void StateParser::ParseTextures(TiXmlElement *texturesRoot)
{
    LOG_DBG("[StateParser][ParseTextures] Parsing the textures");

    for (TiXmlElement *textureRoot = texturesRoot->FirstChildElement(); textureRoot != nullptr;
        textureRoot = textureRoot->NextSiblingElement()) {
        ParseTexture(textureRoot);
    }

    LOG_DBG("[StateParser][ParseTextures] Parsed the textures");
}

void StateParser::ParseTexture(TiXmlElement* textureRoot)
{
    LOG_DBG("[StateParser][ParseTexture] Parsing the texture ", textureRoot->Attribute("name"));

    for (TiXmlElement* tileRoot = textureRoot->FirstChildElement(); tileRoot != nullptr;
        tileRoot = tileRoot->NextSiblingElement()) {
        ParseTile(tileRoot);
    }

    LOG_DBG("[StateParser][ParseTexture] Parsed the texture ", textureRoot->Attribute("name"));
}

void StateParser::ParseTile(TiXmlElement* tileRoot)
{
    LOG_DBG("[StateParser][ParseTile] Parsing the tile");

    uint32_t width;
    uint32_t height;
    uint32_t numColumns;
    uint32_t numRows;
    std::string name;
    std::string source;
    for (TiXmlElement *e = tileRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("name")) {
            name = e->Attribute("value");
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

    bool ret = Resource::Instance()->LoadOneTexture(source, name, width, height, numColumns, numRows,
        Game::Instance()->GetRenderer());
    if (!ret) {
        LOG_ERR("[StateParser][ParseTile] Failed to parse the tile");
    } else {
        LOG_DBG("[StateParser][ParseTile] Parsed the tile");
    }
}

void StateParser::ParseObjects(TiXmlElement* objectsRoot, std::vector<GameObject*>* objects)
{
    LOG_DBG("[StateParser][ParseObjects] Parsing the objects");

    for(TiXmlElement* objectRoot = objectsRoot->FirstChildElement(); objectRoot != nullptr;
        objectRoot = objectRoot->NextSiblingElement()) {
        ParseObject(objectRoot, objects);
    }

    LOG_DBG("[StateParser][ParseObjects] Parsed the objects");
}

void StateParser::ParseObject(TiXmlElement *objectRoot, std::vector<GameObject*>* objects)
{
    LOG_DBG("[StateParser][ParseObject] Parsing the object ", objectRoot->Attribute("name"));

    int32_t x;
    int32_t y;
    std::string type;
    std::vector<ObjectAnimeInfo> objectAnimeInfos;
    for (TiXmlElement* e = objectRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("type")) {
            type = e->Attribute("value");
        } else if (e->Value() == std::string("x")) {
            e->Attribute("value", &x);
        } else if (e->Value() == std::string("y")) {
            e->Attribute("value", &y);
        } else if (e->Value() == std::string("textures")) {
            ParseObjectTextures(e, &objectAnimeInfos);
        }
    }

    GameObject* gameObject = GameObjectFactory::Instance()->Create(type);
    gameObject->Load(x, y, objectAnimeInfos);
    objects->push_back(gameObject);

    LOG_DBG("[StateParser][ParseObject] Parsed the objects ", objectRoot->Attribute("name"));
}

/*void StateParser::ParseBackgrounds(TiXmlElement* backgroundsRoot)
{
    LOG_DBG("[StateParser][ParseBackgrounds] Parsing the objects");

    for(TiXmlElement* backgroundRoot = backgroundsRoot->FirstChildElement(); backgroundRoot != nullptr;
        backgroundRoot = backgroundRoot->NextSiblingElement()) {
        ParseBackgrounds(backgroundRoot);
    }

    LOG_DBG("[StateParser][ParseBackgrounds] Parsed the objects");
}*/

/*void StateParser::ParseBackgrounds(TiXmlElement* backgroundRoot)
{
    LOG_DBG("[StateParser][ParseBackgrounds] Parsing the object ", backgroundRoot->Attribute("name"));

    int32_t x;
    int32_t y;
    std::string textureName;
    for (TiXmlElement* e = backgroundRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("x")) {
            e->Attribute("value", &x);
        } else if (e->Value() == std::string("y")) {
            e->Attribute("value", &y);
        } else if (e->Value() == std::string("texture")) {
            textureName = e->Attribute("value");
        }
    }

    

    LOG_DBG("[StateParser][ParseBackgrounds] Parsed the objects ", backgroundRoot->Attribute("name"));
}*/

void StateParser::ParseObjectTextures(TiXmlElement *texturesRoot,
    std::vector<ObjectAnimeInfo>* objectAnimeInfos)
{
    LOG_DBG("[StateParser][ParseObjectTextures] Parsing object textures");
    
    for (TiXmlElement* textureRoot = texturesRoot->FirstChildElement(); textureRoot != nullptr;
        textureRoot = textureRoot->NextSiblingElement()) {
        ObjectAnimeInfo objectAnimeInfo;
        for (TiXmlElement* e = textureRoot->FirstChildElement(); e != nullptr;
            e = e->NextSiblingElement()) {
            if (e->Value() == std::string("name")) {
                objectAnimeInfo.textureName = e->Attribute("value");
            } else if (e->Value() == std::string("callbackId")) {
                e->Attribute("value", &objectAnimeInfo.callBackId);
            } else if (e->Value() == std::string("animeSpeed")) {
                e->Attribute("value", &objectAnimeInfo.animeSpeed);
            }
        }
        objectAnimeInfos->push_back(objectAnimeInfo);
    }

    LOG_DBG("[StateParser][ParseObjectTextures] Parsed object textures");
}
