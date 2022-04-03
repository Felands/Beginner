#include "StateParser.h"
#include "Resource.h"
#include "Game.h"
#include "LoaderParams.h"
#include "GameObjectFactory.h"

bool StateParser::parseState(const char *stateFile, std::string stateID, std::vector<GameObject *> *pObjects,
    std::vector<std::string> *pTextureIDs)
{
    // create the XML document
    TiXmlDocument xmlDoc;
    // load the state file
    if(!xmlDoc.LoadFile(stateFile)) {
        std::cerr << xmlDoc.ErrorDesc() << "\n";
        return false;
    }
    // get the root element
    TiXmlElement* pRoot = xmlDoc.RootElement();
    // pre declare the states root node
    TiXmlElement* pStateRoot = 0;
    // get this states root node and assign it to pStateRoot
    for(TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if(e->Value() == stateID) {
            pStateRoot = e;
        }
    }
    // pre declare the texture root
    TiXmlElement* pTextureRoot = 0;
    // get the root of the texture elements
    for(TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if(e->Value() == std::string("TEXTURES")) {
            pTextureRoot = e;
        }
    }
    // now parse the textures
    parseTextures(pTextureRoot, pTextureIDs);
    // pre declare the object root node
    TiXmlElement* pObjectRoot = 0;
    // get the root node and assign it to pObjectRoot
    for(TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if(e->Value() == std::string("OBJECTS")) {
            pObjectRoot = e;
        }
    }
    // now parse the objects
    parseObjects(pObjectRoot, pObjects);
    return true;
}

void StateParser::parseTextures(TiXmlElement* pStateRoot, std::vector<std::string> *pTextureIDs)
{
    for(TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
        std::string filenameAttribute = e->Attribute("filename");
        std::string idAttribute = e->Attribute("ID");
        pTextureIDs->push_back(idAttribute); // push into list
        TextureManager::Instance()->Load(filenameAttribute, Game::Instance()->GetRenderer());
    }
}

void StateParser::parseObjects(TiXmlElement *pStateRoot, std::vector<GameObject *> *pObjects)
{
    for(TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        int x, y, callbackID, animSpeed;
        std::string textureID;
        e->Attribute("x", &x);
        e->Attribute("y", &y);
        e->Attribute("callbackID", &callbackID);
        e->Attribute("animSpeed", &animSpeed);
        textureID = e->Attribute("textureID");
        GameObject* pGameObject = GameObjectFactory::Instance()->create(e->Attribute("type"));
        pGameObject->Load(new LoaderParams(x, y, textureID, callbackID, animSpeed));
        pObjects->push_back(pGameObject);
    }
}
