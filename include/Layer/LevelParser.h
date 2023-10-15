#ifndef LEVEL_PARSER_H
#define LEVEL_PARSER_H

#include <vector>

#include "tinyxml.h"
#include "Level.h"
#include "ObjectLayer.h"

class LevelParser
{
public:
    Level *ParseLevel(const char *levelFile);

    static const char *level;

private:
    void ParseTilesets(TiXmlElement *tilesetsRoot, std::vector<Tileset> *tilesets);

    void ParseMaterials(TiXmlElement *materialsRoot, Level* level);
    void ParseLayers(TiXmlElement *layersRoot, Level* level);

    void ParseTileLayers(TiXmlElement *tileLayersRoot, Level* level);

    void ParseObjectLayers(TiXmlElement *objectLayersRoot, Level* level);

    void ParseObject(TiXmlElement *objectRoot, ObjectLayer *objectLayer, Level* level);

    void ParseSounds(TiXmlElement *soundRoot);

    void ParseMusic(TiXmlElement *MusicRoot);

    void ParseSfx(TiXmlElement *SfxRoot);
};

#endif
