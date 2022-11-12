#ifndef STATE_PARSER_H
#define STATE_PARSER_H

#include <vector>

#include "tinyxml.h"

#include "GameObject.h"

class GameObject;
class StateParser
{
public:
    void ParseState(std::string stateId, std::vector<GameObject*> *objects);

    static const char *document;

private:
    void ParseOtherState(std::string source, std::vector<GameObject*>* objects);
    void ParseMaterials(TiXmlElement* materialsRoot);
    void ParseSounds(TiXmlElement* soundsRoot);
    void ParseMusic(TiXmlElement* musicsRoot);
    void ParseSfx(TiXmlElement* sfxsRoot);
    void ParseTextures(TiXmlElement* texturesRoot);
    void ParseTexture(TiXmlElement* textureRoot);
    void ParseTile(TiXmlElement* tileRoot);
    void ParseObjects(TiXmlElement *stateRoot, std::vector<GameObject*> *objects);
    void ParseObject(TiXmlElement* objectRoot, std::vector<GameObject*>* objects);
    void ParseObjectTextures(TiXmlElement *texturesRoot,
        std::vector<ObjectAnimeInfo>* objectAnimeInfos);
};

#endif
