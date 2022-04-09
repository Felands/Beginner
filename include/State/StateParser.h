#ifndef _STATE_PARSER_H_
#define _STATE_PARSER_H_

#include <vector>

#include "tinyxml.h"

class GameObject;
class StateParser
{
public:
    bool ParseState(const char* stateFile, std::string stateID, std::vector<GameObject*> *pObjects,
        std::vector<std::string> *pTextureIDs);

private:
    void ParseObjects(TiXmlElement* pStateRoot, std::vector<GameObject*> *pObjects);
    void ParseTextures(TiXmlElement* pStateRoot, std::vector<std::string> *pTextureIDs);
};

#endif
