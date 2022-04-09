#ifndef _LEVEL_PARSER_H_
#define _LEVEL_PARSER_H_

#include <vector>

#include "tinyxml.h"
#include "Level.h"

class LevelParser
{
public:
    Level* ParseLevel(const char* levelFile);

private:
    void ParseTilesets(TiXmlElement* pTilesetRoot,std::vector<Tileset>* pTilesets);

    void ParseTileLayer(TiXmlElement* pTileElement,std::vector<Layer*> *pLayers, const std::vector<Tileset> *pTilesets);

    void ParseTextures(TiXmlElement* pTextureRoot);

    void ParseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*> *pLayers);

    uint32_t m_tileSize;
    uint32_t m_width;
    uint32_t m_height;
};

#endif
