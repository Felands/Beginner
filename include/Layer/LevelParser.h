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
    void ParseTileLayer(TiXmlElement *tileLayerRoot, std::vector<Layer*> *tileLayers,
        std::vector<Tileset> *tilesets);

    void ParseTilesets(TiXmlElement *tilesetsRoot, std::vector<Tileset> *tilesets);

    void ParseMapLayers(TiXmlElement *mapLayersRoot, std::vector<Layer*> *tileLayers,
        std::vector<Tileset> *tilesets);

    void ParseObjectLayer(TiXmlElement *objectLayerRoot, std::vector<Layer*> *objectLayers);

    void ParseObject(TiXmlElement *objectRoot, ObjectLayer *objectLayers);

    void ParseSound(TiXmlElement *soundRoot);

    void ParseMusic(TiXmlElement *MusicRoot);

    void ParseSfx(TiXmlElement *SfxRoot);
};

#endif
