#ifndef STATE_PARSER_H
#define STATE_PARSER_H

#include <vector>

#include "tinyxml.h"

class GameObject;
class StateParser
{
public:
    bool ParseState(const char *stateFile, std::string stateId, std::vector<GameObject*> *objects,
        std::vector<std::string> *textureIds);

    static const char *document;

private:
    void ParseObjects(TiXmlElement *stateRoot, std::vector<GameObject*> *objects);
    void ParseTextures(TiXmlElement *stateRoot, std::vector<std::string> *textureIds);
};

#endif
