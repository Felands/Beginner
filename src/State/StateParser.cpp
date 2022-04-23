#include "StateParser.h"
#include "Game.h"
#include "Resource.h"
#include "GameObjectFactory.h"
#include "log.h"

const char *StateParser::document = "./assets/state.xml";

bool StateParser::ParseState(const char *stateFile, std::string stateId, std::vector<GameObject*> *objects,
    std::vector<std::string> *textureIds)
{
    LOG_DBG("[StateParser][ParseState] Parsing the state");

    TiXmlDocument xmlDoc;
    if(!xmlDoc.LoadFile(stateFile)) {
        std::cerr << xmlDoc.ErrorDesc() << "\n";
        return false;
    }

    TiXmlElement *root = xmlDoc.RootElement();
    TiXmlElement *stateRoot = nullptr;
    for(TiXmlElement *e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if(e->Value() == stateId) {
            stateRoot = e;
            break;
        }
    }

    TiXmlElement *textureRoot = nullptr;
    for(TiXmlElement *e = stateRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if(e->Value() == std::string("TEXTURES")) {
            textureRoot = e;
            break;
        }
    }
    ParseTextures(textureRoot, textureIds);

    TiXmlElement *objectRoot = nullptr;
    for(TiXmlElement *e = stateRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if(e->Value() == std::string("OBJECTS")) {
            objectRoot = e;
        }
    }
    ParseObjects(objectRoot, objects);

    LOG_DBG("[StateParser][ParseState] Parsed the state");
    return true;
}

void StateParser::ParseTextures(TiXmlElement *textureRoot, std::vector<std::string> *textureIds)
{
    LOG_DBG("[StateParser][ParseTextures] Parsing the textures");

    for (TiXmlElement *texture = textureRoot->FirstChildElement(); texture != nullptr;
        texture = texture->NextSiblingElement()) {
        uint32_t width;
        uint32_t height;
        uint32_t numColumns;
        uint32_t numRows;
        std::string name;
        std::string source;
        for (TiXmlElement *e = texture->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
            if (e->Value() == std::string("name")) {
                name = e->Attribute("value");
                textureIds->push_back(name);
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

    LOG_DBG("[StateParser][ParseTextures] Parsed the textures");
}

void StateParser::ParseObjects(TiXmlElement *objectsRoot, std::vector<GameObject *> *objects)
{
    LOG_DBG("[StateParser][ParseObjects] Parsing the objects");

    for(TiXmlElement* objectRoot = objectsRoot->FirstChildElement(); objectRoot != nullptr;
        objectRoot = objectRoot->NextSiblingElement()) {
        int32_t x;
        int32_t y;
        uint32_t callbackId;
        int32_t animeSpeed;
        std::vector<std::string> textureNames;
        std::string type;
        for (TiXmlElement* e = objectRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
            if (e->Value() == std::string("type")) {
                type = e->Attribute("value");
            } else if (e->Value() == std::string("x")) {
                e->Attribute("value", &x);
            } else if (e->Value() == std::string("y")) {
                e->Attribute("value", &y);
            } else if (e->Value() == std::string("callbackId")) {
                e->Attribute("value", (int*)&callbackId);
            } else if (e->Value() == std::string("animeSpeed")) {
                e->Attribute("value", (int*)&animeSpeed);
            } else if (e->Value() == std::string("textureNames")) {
                for (TiXmlElement* textureName = e->FirstChildElement(); textureName != nullptr;
                    textureName = textureName->NextSiblingElement()) {
                    textureNames.push_back(textureName->Attribute("value"));
                }
            }
        }

        GameObject* gameObject = GameObjectFactory::Instance()->Create(type);
        gameObject->Load(x, y, callbackId, animeSpeed, textureNames);
        objects->push_back(gameObject);
    }

    LOG_DBG("[StateParser][ParseObjects] Parsed the objects");
}
