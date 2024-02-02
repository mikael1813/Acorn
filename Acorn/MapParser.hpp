#pragma once

#include "Vendor/tinyxml-master/tinyxml.h"
#include <map>
#include <string>
#include "GameMap.hpp"
#include "TileLayer.hpp"
#include "SDL.h"

class MapParser
{
public:
	static MapParser* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new MapParser();
	}
	bool Load();
	void Clean();

	inline GameMap* GetMaps(std::string id) { return m_MapDict[id]; };

private:
	bool Parse(std::string id, std::string source);
	TileSet ParseTileSet(TiXmlElement* xmlTileSet);
	TileLayer* ParseTileLayer(TiXmlElement* xmlTileLayer, TileSetList tileSets, int tileSize, int rowCount, int colCount);

	MapParser() {};
	static MapParser* s_Instance;
	std::map<std::string, GameMap*> m_MapDict;
};